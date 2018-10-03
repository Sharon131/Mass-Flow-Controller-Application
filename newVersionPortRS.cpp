#include "newVersionPortRS.hpp"

string NewPort::SetParameter(string PortNumber, string ParameterIndex, string value)
{
	string MessageToSend = "AZ." + PortNumber + "P" + ParameterIndex + value;
	
	WriteOnPort(MessageToSend.c_str());
	string response = ReadFromPort();
	string setValue = GetValueFromResponse(response);

	return setValue;
}

bool NewPort::SetGlobalValue(string ParameterIndex, string value)
{
	string MessageToSend = "AZ.09P" + ParameterIndex + value;

	WriteOnPort(MessageToSend.c_str());
	string response = ReadFromPort();
	string setValue = GetValueFromResponse(response);

	return (setValue=="1");
}

string NewPort::GetValueFromResponse(string response)
{
	int countCommas = 0;
	int indx = 0;

	string value = "";

	while (countCommas < 4) {
		if (response[indx]==',') {
			countCommas += 1;
		}
		indx++;
	}

	while (response[indx] != ',') {
		value += response[indx];
	}

	return value;
}

void NewPort::WriteOnPort(const char* messageToSend){
	PreparePortToWrite();
	
	DWORD Bytes;
	bool written = false;
	
	written = WriteFile(Port, &messageToSend, strlen(messageToSend), &Bytes, 0);
	
	if (!written) {
		throw Exception("Error while sending data. Try again.\n");
	}
}

char* NewPort::ReadFromPort(){
	char* MessageFromPort = new char[1000];
	int BytesRead = -1;
	DWORD Bytes;
	do {
		BytesRead++;
		ReadFile(Port, (MessageFromPort + BytesRead), 1, &Bytes, 0);
		if ((int)MessageFromPort[BytesRead] == 10 && (int)MessageFromPort[BytesRead - 1] == 10)	BytesRead--;
	} while (Bytes == 1 && BytesRead<999);
	return MessageFromPort;
}

void NewPort::PreparePortToWrite()
{
	PurgeComm(Port, PURGE_RXCLEAR);

	DWORD dwEvent;
	DWORD dwStatus;
	GetCommModemStatus(Port, &dwStatus);

	if (!(MS_CTS_ON & dwStatus)) {
		SetCommMask(Port, EV_CTS | EV_BREAK);
		WaitCommEvent(Port, &dwEvent, 0);
		if (dwEvent & EV_BREAK) {
			throw Exception("Connection with port has been broken. Try again.\n");
		}
	}
}

void NewPort::PrepareToRead()
{
	DWORD dwEvent;
	SetCommMask(Port, EV_RXCHAR | EV_BREAK | EV_CTS | EV_RING | EV_DSR | EV_ERR | EV_RLSD | EV_RXFLAG);
	WaitCommEvent(Port, &dwEvent, 0);

	if (dwEvent & EV_RXCHAR) {
		return;
	}
	if (dwEvent & EV_BREAK) {
		throw Exception("Connection with port has been broken. Try again.\n");
	}
	
	throw Exception("Unknown reading from port error.\n");
}

void NewPort::OpenPort()
{
	Port = CreateFile(PortName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if (Port == INVALID_HANDLE_VALUE)  throw Exception("Error accured while connecting with port. Try again.\n");
}

void NewPort::ClosePort()
{
	CloseHandle(Port);
}

void NewPort::SetDCBParameters()
{
	DCB PortParameters;

	PortParameters.DCBlength = sizeof(DCB);
	GetCommState(Port, &PortParameters);

	PortParameters.BaudRate = CBR_9600;
	PortParameters.ByteSize = 8;
	PortParameters.fParity = FALSE;
	PortParameters.Parity = NOPARITY;
	PortParameters.StopBits = ONESTOPBIT;

	PortParameters.fOutxCtsFlow = FALSE;
	PortParameters.fOutxDsrFlow = FALSE;
	PortParameters.fDsrSensitivity = FALSE;
	PortParameters.fRtsControl = RTS_CONTROL_ENABLE;
	PortParameters.fDtrControl = DTR_CONTROL_ENABLE;
	PortParameters.fDsrSensitivity = FALSE;

	PortParameters.fOutX = FALSE;
	PortParameters.fInX = FALSE;
	PortParameters.fTXContinueOnXoff = TRUE;

	PortParameters.fErrorChar = FALSE;
	PortParameters.fNull = FALSE;
	PortParameters.fAbortOnError = FALSE;

	if (!SetCommState(Port, &PortParameters)) {
		CloseHandle(Port);
		throw Exception("Error accured while connecting with port. Try again.\n");
	}
}

void NewPort::SetTimeouts()
{
	COMMTIMEOUTS TimeOuts;

	GetCommTimeouts(Port, &TimeOuts);

	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 20;
	TimeOuts.ReadTotalTimeoutConstant = 20;
	TimeOuts.WriteTotalTimeoutMultiplier = 10;
	TimeOuts.WriteTotalTimeoutConstant = 1000;

	if (!SetCommTimeouts(Port, &TimeOuts)) {
		CloseHandle(Port);
		throw Exception("Error accured while connecting with port. Try again.\n");
	}
}

bool NewPort::IsThatTextANumber(const char text[])
{
	if ((strlen(text) == 0)) {
		return false;
	}
	char* bufor;
	double example = strtod(text, &bufor);

	return ((strlen(bufor) == 0));	//bufor==NULL || 
}

NewPort::NewPort():
	CurrentChannelSelection(Channel1),
	PortName("COM1")
{
	OpenPort();
	SetDCBParameters();
	SetTimeouts();
}

NewPort::NewPort(string ComNumber):
	CurrentChannelSelection(Channel1),
	PortName(ComNumber)
{
	OpenPort();
	SetDCBParameters();
	SetTimeouts();
}

string NewPort::GetGlobalInfo()
{
	WriteOnPort("AZ.9V");
	char* response = ReadFromPort();
	string responseInString(response);
	return responseInString;
}

string NewPort::GetChannelInfo()
{
	string ChannelToSend = int2str(2*(CurrentChannelSelection+1)-1);
	string messageToSend = "AZ." + ChannelToSend + "V";
	WriteOnPort(messageToSend.c_str());
	char* Input = ReadFromPort();
	string InputResponse(Input);
	
	ChannelToSend = int2str(2 * (CurrentChannelSelection + 1));
	messageToSend = "AZ." + ChannelToSend + "V";
	WriteOnPort(messageToSend.c_str());
	char* Output = ReadFromPort();
	string OutputResponse(Output);

	string Response=InputResponse+"\n"+OutputResponse;

	return Response;
}

string NewPort::GetAllChannelsInfo()
{
	Channel temporaryChannel = CurrentChannelSelection;

	CurrentChannelSelection = Channel1;
	string Channel1Info = "Channel1:\n" + GetChannelInfo()+"\n";

	CurrentChannelSelection = Channel2;
	string Channel2Info = "Channel2:\n"+GetChannelInfo()+"\n";

	CurrentChannelSelection = Channel3;
	string Channel3Info = "Channel3:\n"+GetChannelInfo()+"\n";

	CurrentChannelSelection = Channel4;
	string Channel4Info = "Channel4:\n" + GetChannelInfo() + "\n";;

	CurrentChannelSelection = temporaryChannel;

	return Channel1Info + Channel2Info + Channel3Info + Channel4Info;
}

void NewPort::SetCurrentChannelSelection(Channel NextChannelSelection)
{
	CurrentChannelSelection = NextChannelSelection;
}

string NewPort::SetAudioBeep(bool set)
{
	string ParameterIndex = "39";
	string value = int2str(set);

	bool SetValue=SetGlobalValue(ParameterIndex,value);

	if (SetValue) {
		return "Beep turned on.\n";
	}

	return "Beep turned off.\n";
}

string NewPort::SetZeroSupress(bool set)
{
	string ParameterIndex = "32";
	string value = int2str(set);

	bool SetValue = SetGlobalValue(ParameterIndex, value);

	if (SetValue) {
		return "Zero Supress turned on.\n";
	}

	return "Zero Supress turned off.\n";
}

string NewPort::SetPwrSP_Clear(bool set)
{
	string ParameterIndex = "33";
	string value = int2str(set);

	bool SetValue = SetGlobalValue(ParameterIndex, value);

	if (SetValue) {
		return "Power SP Clear turned on, captain.\n";
	}

	return "Power SP Clear turned off.\n";
}

string NewPort::SetFactorySettings()
{
	string MessageToSend = "AZz4";
	WriteOnPort(MessageToSend.c_str());

	return "Factory settings are set.\n";
}

string NewPort::SetPortTypeIn(int option)
{
	string PortNumber = int2str(CurrentChannelSelection*2-1);
	string ParameterIndex = "0";
	string optionInString = int2str(option);

	string SetValue=SetParameter(PortNumber, ParameterIndex, optionInString);

	return ("Port Type In set to: " + SetValue+ "\n");
}

string NewPort::SetDecimalPoint(int option)
{
	string PortNumber = int2str(CurrentChannelSelection * 2 - 1);
	string ParameterIndex = "3";
	string optionInString = int2str(option);
	
	string SetValue = SetParameter(PortNumber, ParameterIndex, optionInString);

	return ("Decimal Point set to: " + SetValue + "\n");
}

string NewPort::SetMeasureUnit(int option)
{
	string PortNumber = int2str(CurrentChannelSelection * 2 - 1);
	string ParameterIndex = "4";
	string optionInString = int2str(option);
	
	string SetValue = SetParameter(PortNumber, ParameterIndex, optionInString);

	return ("Measure unit set to: " + SetValue + "\n");
}

string NewPort::SetTimeBase(int option)
{
	string PortNumber = int2str(CurrentChannelSelection * 2 - 1);
	string ParameterIndex = "10";
	string optionInString = int2str(option);
	
	string SetValue = SetParameter(PortNumber, ParameterIndex, optionInString);

	return ("Time base set to: " + SetValue + "\n");
}

string NewPort::SetPVFullScale(const char* value)
{
	string PortNumber = int2str(CurrentChannelSelection * 2 - 1);
	string ParameterIndex = "9";

	string SetValue = SetParameter(PortNumber, ParameterIndex, value);

	return ("PV Full Scale is set to: " + SetValue + "\n");

}

string NewPort::SetGasFactor(const char * value)
{
	string PortNumber = int2str(CurrentChannelSelection * 2 - 1);
	string ParameterIndex = "27";

	string SetValue = SetParameter(PortNumber, ParameterIndex, value);

	return ("Gas Factor is set to: " + SetValue + "\n");
}

string NewPort::SetPortTypeOut(int option)
{
	string PortNumber = int2str(CurrentChannelSelection * 2);
	string ParameterIndex = "0";
	string optionInString = int2str(option);

	string SetValue = SetParameter(PortNumber, ParameterIndex, optionInString);

	return ("Port Type Out is set to: " + SetValue + "\n");
}

string NewPort::SetSPFunction(int option)
{
	string PortNumber = int2str(CurrentChannelSelection * 2);
	string ParameterIndex = "2";
	string optionInString = int2str(option);

	string SetValue = SetParameter(PortNumber, ParameterIndex, optionInString);

	return ("SP function is set to: " + SetValue + "\n");
}

string NewPort::SetSPValve(int option)
{
	string PortNumber = int2str(CurrentChannelSelection * 2);
	string ParameterIndex = "29";
	string optionInString = int2str(option);

	string SetValue = SetParameter(PortNumber, ParameterIndex, optionInString);

	return ("SP Valve is set to: " + SetValue + "\n");
}

string NewPort::SetProgrammingSource(int option)
{
	string PortNumber = int2str(CurrentChannelSelection * 2);
	string ParameterIndex = "46";
	string optionInString = int2str(option);

	string SetValue = SetParameter(PortNumber, ParameterIndex, optionInString);

	return ("Programming source is set to: " + SetValue + "\n");
}

string NewPort::SetRateValue(char * value)
{
	string PortNumber = int2str(CurrentChannelSelection * 2);
	string ParameterIndex = "1";
	
	string SetValue = SetParameter(PortNumber, ParameterIndex, value);

	return ("New Rate value is: " + SetValue + "\n");
}

string NewPort::SetSPFullScale(char * value)
{
	string PortNumber = int2str(CurrentChannelSelection * 2);
	string ParameterIndex = "9";

	string SetValue = SetParameter(PortNumber, ParameterIndex, value);

	return ("New SP Full Scale is: " + SetValue + "\n");
}

string NewPort::SetBatchValue(char * value)
{
	string PortNumber = int2str(CurrentChannelSelection * 2);
	string ParameterIndex = "44";

	string SetValue = SetParameter(PortNumber, ParameterIndex, value);

	WriteOnPort("AZ F*");
	
	return ("New Batch Value is: " + SetValue + "\n");
}

string NewPort::ResetTotalizer()
{
	string PortNumber = int2str(CurrentChannelSelection * 2-1);
	string MessageToSend = "AZ." + PortNumber +"z1";
	WriteOnPort(MessageToSend.c_str());

	return "Totalizer was reseted\n";
}

string NewPort::SetBlendValue(char * value)
{
	string PortNumber = int2str(CurrentChannelSelection * 2);
	string ParameterIndex = "45";
	
	string SetValue = SetParameter(PortNumber, ParameterIndex, value);

	return ("New Blend Value is: " + SetValue + "\n");
}

void NewPort::SetOnBlendingMode(int MasterChannel)
{
	string adress = int2str(2 * MasterChannel - 1);

	string message = "AZ." + adress + "B";
}

void NewPort::StopAllBatching()
{
	WriteOnPort("AZ F");
}

void NewPort::StopAllBlending()
{
	WriteOnPort("AZ F");
}

string int2str(int number)
{
	string solution = "";
	
	while (number != 0) {
		int digit_int = number % 10;
		char digit_char = (char)(digit_int+48);
		solution = digit_char + solution;
		number /= 10;
	}
	
	return solution;
}
