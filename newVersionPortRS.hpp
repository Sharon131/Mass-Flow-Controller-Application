#ifndef NEW_PORT_RS
#define NEW_PORT_RS
#include<string>
#include<Windows.h>
#include"Exceptions.hpp"

using namespace std;

enum Channel {
	Channel1 = 0,
	Channel2,
	Channel3,
	Channel4,
	AllChannels
};

class NewPort {
	HANDLE Port;
	string PortName;

	Channel CurrentChannelSelection;

	string SetParameter(string PortNumber, string ParameterIndex, string value);
	bool SetGlobalValue(string ParameterIndex, string value);

	string GetValueFromResponse(string response);

	void WriteOnPort(const char* messageToSend);
	char* ReadFromPort();

	void PreparePortToWrite();
	void PrepareToRead();

	void OpenPort();
	void ClosePort();

	void SetDCBParameters();
	void SetTimeouts();

	bool IsThatTextANumber(const char text[]);

public:

	NewPort();
	NewPort(string ComNumber);
	~NewPort();

	string GetGlobalInfo();
	string GetChannelInfo();
	string GetAllChannelsInfo();

	void SetCurrentChannelSelection(Channel NextChannelSelection);

	string SetAudioBeep(bool set);
	string SetZeroSupress(bool set);
	string SetPwrSP_Clear(bool set);
	string SetFactorySettings();

	string SetPortTypeIn(int option);
	string SetDecimalPoint(int option);
	string SetMeasureUnit(int option);
	string SetTimeBase(int option);

	string SetPVFullScale(const char* value);
	string SetGasFactor(const char* value);

	string SetPortTypeOut(int option);
	string SetSPFunction(int option);
	string SetSPValve(int option);
	string SetProgrammingSource(int option);

	string SetRateValue(char* value);
	string SetSPFullScale(char* value);
	string SetBatchValue(char* value);

	string ResetTotalizer();

	string SetBlendValue(char* value);

	void SetOnBlendingMode(int MasterChannel);

	void StopAllBatching();
	void StopAllBlending();
	
};


string int2str(int number);


#endif
