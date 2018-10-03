#include "Controls.h"

SetOfControls::SetOfControls(WindowInformation * WindowInfo):
	parentInfo(WindowInfo),
	CurrentChannelChoice(Channel1)
{
	SetHandlesToNULL();
	
	CreatePortSelection();
	CreateResponseWindow();
}

SetOfControls::~SetOfControls()
{
	delete parentInfo;
	
	//Buttons:
	delete ConnectWithPort;
	
	//PortSelection
	delete PortSettings;
	delete ComboPortSelection;

	//ChannelSelection
	delete ChooseChannel;
	delete ChannelSelection;

	//Response Box:
	delete Response;
	delete ResponseTextBox;
	delete ClearTextWindow;

	//Global Settings:
	delete GlobalSettings; 
	delete BeepOn;
	delete BeepOff;
	delete ZeroSupressOn;
	delete ZeroSupressOff;
	delete PwrClearOn;
	delete PwrClearOff;
	delete FactorySetOn;
	delete SendGlobalSettings;
	delete GetGlobalSettings;

	//ChannelSettings
	delete ChannelSettings;
	delete PortTypeSignalIn;
	delete DecimalPoint;
	delete MeasureUnits;
	delete TimeBase;
	delete PV_FullScale;
	delete GasFactor;
	//Output Values:
	delete PortTypeSignalOut;
	delete SP_Function;
	delete SP_VOR;
	delete ProgrammingSource;
	delete SP_Rate;
	delete SP_FullScale;
	delete BatchValue;
	delete Reset_PV_Totalizer;
	delete SendChannelSettings;
	delete GetChannelSettings;
	//AllChannelsSettings:
	delete AllChannelsSettings;
	delete Master1;
	delete Master2;
	delete Master3;
	delete Master4;
	delete Slave1;
	delete Slave2;
	delete Slave3;
	delete Slave4;
	delete BlendValueChannel1;
	delete BlendValueChannel2;
	delete BlendValueChannel3;
	delete BlendValueChannel4;
	delete StopBlendingsAndBatches;
	delete SendAllChannelsSettings;
	delete GetAllChannelsSettings;
}

void SetOfControls::SetHandlesToNULL()
{
	Port_RS = NULL;
	//Buttons:
	ConnectWithPort = NULL;
	
	//PortSelection
	PortSettings = NULL;
	ComboPortSelection = NULL;

	//ChannelSelection
	ChooseChannel = NULL;
	ChannelSelection = NULL;

	//Response:
	Response = NULL;
	ResponseTextBox = NULL;
	ClearTextWindow = NULL;

	//GlobalSettings:
	GlobalSettings = NULL;
	BeepOn = NULL;
	BeepOff = NULL;
	ZeroSupressOn = NULL;
	ZeroSupressOff = NULL;
	PwrClearOn = NULL;
	PwrClearOff=NULL;
	FactorySetOn=NULL;
	SendGlobalSettings = NULL;
	GetGlobalSettings=NULL;

	//ChannelSettings:
	ChannelSettings = NULL;
	PortTypeSignalIn = NULL;
	DecimalPoint = NULL;
	MeasureUnits = NULL;
	TimeBase=NULL;
	PV_FullScale = NULL;
	GasFactor=NULL;
	//Output Values:
	PortTypeSignalOut = NULL;
	SP_Function = NULL;
	SP_VOR = NULL;
	ProgrammingSource=NULL;
	SP_Rate = NULL;
	SP_FullScale = NULL;
	BatchValue=NULL;
	Reset_PV_Totalizer=NULL;
	SendChannelSettings=NULL;
	GetChannelSettings=NULL;
	//AllChannelsSettings:
	AllChannelsSettings=NULL;
	Master1 = NULL;
	Master2 = NULL;
	Master3 = NULL;
	Master4=NULL;
	Slave1 = NULL;
	Slave2=NULL;
	Slave3 = NULL;
	Slave4=NULL;
	BlendValueChannel1 = NULL;
	BlendValueChannel2 = NULL;
	BlendValueChannel3 = NULL;
	BlendValueChannel4 = NULL;
	StopBlendingsAndBatches = NULL;
	SendAllChannelsSettings = NULL;
	GetAllChannelsSettings = NULL;
}

void SetOfControls::CreatePortSelection()
{
	int motherPositionx = 20;
	int motherPositiony = 10;
	PortSettings = new Frame(new Size(90, 100, new Point(motherPositionx, motherPositiony)), parentInfo, "Port Settings");
	ComboPortSelection = new ComboBox(new Size(200, 60, new Point(motherPositionx+20, motherPositiony+25)), parentInfo, ID_COMBOBOX1);
	ComboPortSelection->SetComboPortSelection();
	ConnectWithPort = new Button(new Size(20,80,new Point(motherPositionx+10,motherPositiony+55)),parentInfo,new BoxInfo(ID_BUTTON1,"Connect"));
	ConnectWithPort->SetFontToNormal();
}

void SetOfControls::CreateChannelSelection()
{
	int motherPositionx = 20;
	int motherPositiony = 110;
	ChooseChannel = new Frame(new Size(80,100,new Point(motherPositionx,motherPositiony)),parentInfo,"Channel");
	ChannelSelection = new ComboBox(new Size(120, 80, new Point(motherPositionx+10, motherPositiony+25)), parentInfo, ID_COMBOBOX2);

	ChannelSelection->SetComboChannelSelection();
	ChannelSelection->SetOption(1);
}

void SetOfControls::CreateResponseWindow()
{
	Response = new Frame(new Size(520, 300, new Point(370, 10)), parentInfo, "Response");
	ClearTextWindow = new Button(new Size(20, 200, new Point(420, 40)), parentInfo, new BoxInfo(ID_BUTTON2, "Clear TextWindow"));
	ResponseTextBox = new TextBox(new Size(430, 300, new Point(372, 70)), parentInfo, TextBoxWithScroll);

	ClearTextWindow->SetFontToNormal();

	ResponseTextBox->AddText("Hi.\n");
	ResponseTextBox->AddText("Welcome to program designed to operate on Instrumental Brooks.\n");
	ResponseTextBox->AddText("Choose COM port of your device and press connect.\n");
	ResponseTextBox->AddText("If you decide correctly, further settings will be shown.\n");
}

void SetOfControls::CreatePortAndOtherControls()
{
	try {
		Port_RS = new NewPort;

		CreateChannelSelection();
		CreateGlobalSetting();
		CreateChannelSettings();
		CreateAllChannelsSettings();

		HideAllChannelsSettings();

		ResponseTextBox->AddText("Connected with port.\n");
	}
	catch (Exception e) {
		ResponseTextBox->AddText(e.getMessage());
	}
}

string SetOfControls::getComOption(int option)
{
	return string("COM"+int2str(option+1));
}

void SetOfControls::CreateGlobalSetting()
{
	int heightOfOnOffs = 20;
	int widthOfOnOffs = 40;
	int motherPositionx = 130;
	int motherPositiony = 10;
	
	GlobalSettings = new Frame(new Size(180, 230, new Point(motherPositionx, motherPositiony)), parentInfo, "Global Settings");
	

	StaticText* Beep = new StaticText(new Size(20, 100, new Point(motherPositionx + 10, motherPositiony + 30)),parentInfo,"Audio Beep");
	BeepOn = new RadioButton(new Size(heightOfOnOffs, widthOfOnOffs, new Point(motherPositionx+130, motherPositiony + 30)), parentInfo, new BoxInfo(ID_RADIO1, "On"));
	BeepOff = new RadioButton(new Size(heightOfOnOffs, widthOfOnOffs, new Point(motherPositionx + 180, motherPositiony + 30)), parentInfo, new BoxInfo(ID_RADIO2, "Off"));


	StaticText* ZeroSupress = new StaticText(new Point(motherPositionx + 10, motherPositiony+50),parentInfo,"Zero Supress");	
	ZeroSupressOn = new RadioButton(new Size(heightOfOnOffs, widthOfOnOffs, new Point(motherPositionx + 130, motherPositiony + 50)), parentInfo, new BoxInfo(ID_RADIO3, "On"));
	ZeroSupressOff = new RadioButton(new Size(heightOfOnOffs, widthOfOnOffs, new Point(motherPositionx + 180, motherPositiony + 50)), parentInfo, new BoxInfo(ID_RADIO4, "Off"));

	
	StaticText* PwrClear = new StaticText(new Point(motherPositionx + 10, motherPositiony + 70),parentInfo,"Pwr SP Clear");
	PwrClearOn = new RadioButton(new Size(heightOfOnOffs,widthOfOnOffs,new Point(motherPositionx + 130, motherPositiony + 70)), parentInfo, new BoxInfo(ID_RADIO5, "On"));
	PwrClearOff = new RadioButton(new Size(heightOfOnOffs, widthOfOnOffs, new Point(motherPositionx + 180, motherPositiony + 70)), parentInfo, new BoxInfo(ID_RADIO6, "Off"));
	
	FactorySetOn = new CheckBox(new Size(20, 100, new Point(motherPositionx + 20, motherPositiony + 95)), parentInfo, new BoxInfo(ID_CHECKBOX1, "Factory Set"));

	SendGlobalSettings = new Button(new Size(20, 190, new Point(motherPositionx + 20, motherPositiony + 125)), parentInfo, new BoxInfo(ID_BUTTON3, "Send"));
	GetGlobalSettings=new Button(new Size(20, 190, new Point(motherPositionx + 20, motherPositiony + 150)), parentInfo, new BoxInfo(ID_BUTTON4, "Get Information"));
	
}

void SetOfControls::CreateChannelSettings()
{
	int motherPositionx = 20;
	int motherPositiony = 200;

	ChannelSettings = new Frame(new Size(275, 300, new Point(motherPositionx, motherPositiony)), parentInfo, "Channel1");
	
	//Input values
	SignalInText = new StaticText(new Size(20,80,new Point(motherPositionx+10,motherPositiony+30)),parentInfo,"Port Type In");
	DecimalPointStatic = new StaticText(new Size(20,80,new Point(motherPositionx + 10, motherPositiony + 60)), parentInfo, "Decimal Point");
	MeasureUnitsStatic = new StaticText(new Size(20,80,new Point(motherPositionx + 10, motherPositiony + 90)), parentInfo, "Measure Units");
	TimeBaseStatic = new StaticText(new Size(20,80,new Point(motherPositionx + 10, motherPositiony + 120)), parentInfo, "Time Base");
	
	PortTypeSignalIn = new ComboBox(new Size(120,50,new Point(motherPositionx + 90, motherPositiony + 25)),parentInfo,ID_COMBOBOX3);
	DecimalPoint = new ComboBox(new Size(80, 50, new Point(motherPositionx + 90, motherPositiony + 55)), parentInfo, ID_COMBOBOX4);
	MeasureUnits= new ComboBox(new Size(550, 50, new Point(motherPositionx + 90, motherPositiony + 85)), parentInfo, ID_COMBOBOX5);
	TimeBase= new ComboBox(new Size(80, 50, new Point(motherPositionx + 90, motherPositiony + 115)), parentInfo, ID_COMBOBOX6);

	PortTypeSignalIn->SetComboPortType();
	DecimalPoint->SetComboDecimalPoint();
	MeasureUnits->SetComboMeasureUnits();
	TimeBase->SetComboTimeBase();

	PV_FullScaleStatic= new StaticText(new Size(20, 80,new Point(motherPositionx + 10, motherPositiony + 150)), parentInfo, "PV Full Scale");
	GasFactorStatic = new StaticText(new Size(20, 80,new Point(motherPositionx + 10, motherPositiony + 180)), parentInfo, "Gas Factor");

	PV_FullScale = new TextBox(new Size(20,50,new Point(motherPositionx + 90, motherPositiony + 145)),parentInfo, TextBoxNoScroll);
	GasFactor = new TextBox(new Size(20, 50, new Point(motherPositionx + 90, motherPositiony + 175)), parentInfo, TextBoxNoScroll);
	
	//Output values

	SignalOutText = new StaticText(new Size(20, 80, new Point(motherPositionx + 150, motherPositiony + 30)), parentInfo, "Port Type Out");
	SP_FunctionStatic = new StaticText(new Size(20, 80, new Point(motherPositionx + 150, motherPositiony + 60)), parentInfo, "SP Function");
	SP_VOR_Static = new StaticText(new Size(20, 80, new Point(motherPositionx + 150, motherPositiony + 90)), parentInfo, "SP Valve");
	ProgrammingSourceStatic = new StaticText(new Size(20, 80, new Point(motherPositionx + 150, motherPositiony + 120)), parentInfo, "Keypad Source");

	PortTypeSignalOut= new ComboBox(new Size(120, 50, new Point(motherPositionx + 230, motherPositiony + 25)), parentInfo, ID_COMBOBOX7);
	SP_Function= new ComboBox(new Size(80, 50, new Point(motherPositionx + 230, motherPositiony + 55)), parentInfo, ID_COMBOBOX8);
	SP_VOR= new ComboBox(new Size(80, 50, new Point(motherPositionx + 230, motherPositiony + 85)), parentInfo, ID_COMBOBOX9);
	ProgrammingSource= new ComboBox(new Size(60, 50, new Point(motherPositionx + 230, motherPositiony + 115)), parentInfo, ID_COMBOBOX10);

	PortTypeSignalOut->SetComboPortType();
	SP_Function->SetComboSP_Function();
	SP_VOR->SetComboSP_VOR();
	ProgrammingSource->SetComboProgrammingSource();
	
	Reset_PV_Totalizer = new CheckBox(new Size(20,100,new Point(motherPositionx+35, motherPositiony + 210)),parentInfo,new BoxInfo(ID_CHECKBOX2,"Reset Totalizer"));

	SP_RateStatic = new StaticText(new Size(20, 80, new Point(motherPositionx + 150, motherPositiony + 150)), parentInfo, "Rate Value");
	SP_FullScaleStatic = new StaticText(new Size(20, 80, new Point(motherPositionx + 150, motherPositiony + 180)), parentInfo, "SP Full Scale");
	BatchValueStatic = new StaticText(new Size(20, 80, new Point(motherPositionx + 150, motherPositiony + 210)), parentInfo, "Batch Value");

	SP_Rate = new TextBox(new Size(20, 50, new Point(motherPositionx + 230, motherPositiony + 150)), parentInfo, TextBoxNoScroll);
	SP_FullScale = new TextBox(new Size(20, 50, new Point(motherPositionx + 230, motherPositiony + 180)), parentInfo, TextBoxNoScroll);
	BatchValue = new TextBox(new Size(20, 50, new Point(motherPositionx + 230, motherPositiony + 210)), parentInfo, TextBoxNoScroll);
	
	SendChannelSettings = new Button(new Size(20, 125, new Point(motherPositionx + 20, motherPositiony + 240)), parentInfo, new BoxInfo(ID_BUTTON5, "Send"));
	GetChannelSettings = new Button(new Size(20, 125, new Point(motherPositionx + 155, motherPositiony + 240)), parentInfo, new BoxInfo(ID_BUTTON6, "Get Information"));
}

void SetOfControls::CreateAllChannelsSettings()
{
	int motherPositionx = 20;
	int motherPositiony = 200;

	AllChannelsSettings = new Frame(new Size(270,230,new Point(motherPositionx,motherPositiony)),parentInfo,"All Channels");

	MasterChoice = new StaticText(new Point(motherPositionx+20,motherPositiony+30),parentInfo,"Master");
	
	Master1 = new RadioButton(new Size(20, 30, new Point(motherPositionx + 90, motherPositiony + 30)),parentInfo,new BoxInfo(ID_RADIO7,"1"));
	Master2 = new RadioButton(new Size(20, 30, new Point(motherPositionx + 120, motherPositiony + 30)), parentInfo, new BoxInfo(ID_RADIO8, "2"));
	Master3 = new RadioButton(new Size(20, 30, new Point(motherPositionx + 150, motherPositiony + 30)), parentInfo, new BoxInfo(ID_RADIO9, "3"));
	Master4 = new RadioButton(new Size(20, 30, new Point(motherPositionx + 180, motherPositiony + 30)), parentInfo, new BoxInfo(ID_RADIO10, "4"));
	
	Slave1 = new CheckBox(new Size(20, 100, new Point(motherPositionx + 30, motherPositiony + 60)), parentInfo, new BoxInfo(ID_CHECKBOX3,"Channel1"));
	Slave2 = new CheckBox(new Size(20, 100, new Point(motherPositionx + 30, motherPositiony + 90)), parentInfo, new BoxInfo(ID_CHECKBOX4, "Channel2"));
	Slave3 = new CheckBox(new Size(20, 100, new Point(motherPositionx + 30, motherPositiony + 120)), parentInfo, new BoxInfo(ID_CHECKBOX5, "Channel3"));
	Slave4 = new CheckBox(new Size(20, 100, new Point(motherPositionx + 30, motherPositiony + 150)), parentInfo, new BoxInfo(ID_CHECKBOX6, "Channel4"));
	
	//StaticText* Value = new StaticText(new Point(motherPositionx+1300,motherPositiony+40),parentInfo,"Value");
	
	BlendValueChannel1 = new TextBox(new Size(20,50,new Point(motherPositionx + 130, motherPositiony + 60)),parentInfo, TextBoxNoScroll);
	BlendValueChannel2 = new TextBox(new Size(20, 50, new Point(motherPositionx + 130, motherPositiony + 90)), parentInfo, TextBoxNoScroll);
	BlendValueChannel3 = new TextBox(new Size(20, 50, new Point(motherPositionx + 130, motherPositiony + 120)), parentInfo, TextBoxNoScroll);
	BlendValueChannel4 = new TextBox(new Size(20, 50, new Point(motherPositionx + 130, motherPositiony + 150)), parentInfo, TextBoxNoScroll);

	BlendValueChannel1->SetToReadOnly();
	BlendValueChannel2->SetToReadOnly();
	BlendValueChannel3->SetToReadOnly();
	BlendValueChannel4->SetToReadOnly();

	StopBlendingsAndBatches = new CheckBox(new Size(20, 170, new Point(motherPositionx + 30, motherPositiony + 185)), parentInfo, new BoxInfo(ID_CHECKBOX7, "Stop All Blends And Batches"));
	
	SendAllChannelsSettings = new Button(new Size(20,190,new Point(motherPositionx+20,motherPositiony+215)),parentInfo,new BoxInfo(ID_BUTTON7,"Send"));
	GetAllChannelsSettings = new Button(new Size(20, 190, new Point(motherPositionx + 20, motherPositiony + 240)), parentInfo, new BoxInfo(ID_BUTTON8, "Get Information"));
}

void SetOfControls::HideChannelSettings()
{
	HideOrShowChannelSettings(hide);
}

void SetOfControls::ShowChannelSettings()
{
	HideOrShowChannelSettings(show);
}

void SetOfControls::HideOrShowChannelSettings(HideOrShow choice)
{
	SignalInText->HideOrShowControl(choice);
	DecimalPointStatic->HideOrShowControl(choice);
	MeasureUnitsStatic->HideOrShowControl(choice);
	TimeBaseStatic->HideOrShowControl(choice);
	PV_FullScaleStatic->HideOrShowControl(choice);
	GasFactorStatic->HideOrShowControl(choice);

	ChannelSettings->HideOrShowControl(choice);
	PortTypeSignalIn->HideOrShowControl(choice);
	DecimalPoint->HideOrShowControl(choice);
	MeasureUnits->HideOrShowControl(choice);
	TimeBase->HideOrShowControl(choice);
	PV_FullScale->HideOrShowControl(choice);
	GasFactor->HideOrShowControl(choice);

	SignalOutText->HideOrShowControl(choice);
	SP_FunctionStatic->HideOrShowControl(choice);
	SP_VOR_Static->HideOrShowControl(choice);
	ProgrammingSourceStatic->HideOrShowControl(choice);
	SP_RateStatic->HideOrShowControl(choice);
	SP_FullScaleStatic->HideOrShowControl(choice);
	BatchValueStatic->HideOrShowControl(choice);

	PortTypeSignalOut->HideOrShowControl(choice);
	SP_Function->HideOrShowControl(choice);
	SP_VOR->HideOrShowControl(choice);
	ProgrammingSource->HideOrShowControl(choice);
	SP_Rate->HideOrShowControl(choice);
	SP_FullScale->HideOrShowControl(choice);
	BatchValue->HideOrShowControl(choice);
	Reset_PV_Totalizer->HideOrShowControl(choice);
	SendChannelSettings->HideOrShowControl(choice);
	GetChannelSettings->HideOrShowControl(choice);
}

void SetOfControls::HideAllChannelsSettings()
{
	HideOrShowAllChannelsSettings(hide);
}

void SetOfControls::ShowAllChannelsSettings()
{
	HideOrShowAllChannelsSettings(show);
}

void SetOfControls::HideOrShowAllChannelsSettings(HideOrShow choice)
{
	AllChannelsSettings->HideOrShowControl(choice);
	MasterChoice->HideOrShowControl(choice);
	Master1->HideOrShowControl(choice); 
	Master2->HideOrShowControl(choice); 
	Master3->HideOrShowControl(choice); 
	Master4->HideOrShowControl(choice);
	Slave1->HideOrShowControl(choice); 
	Slave2->HideOrShowControl(choice); 
	Slave3->HideOrShowControl(choice); 
	Slave4->HideOrShowControl(choice);
	BlendValueChannel1->HideOrShowControl(choice); 
	BlendValueChannel2->HideOrShowControl(choice); 
	BlendValueChannel3->HideOrShowControl(choice); 
	BlendValueChannel4->HideOrShowControl(choice);
	StopBlendingsAndBatches->HideOrShowControl(choice);
	SendAllChannelsSettings->HideOrShowControl(choice); 
	GetAllChannelsSettings->HideOrShowControl(choice);
}

void SetOfControls::DealWithChannelChange()
{
	Channel NextChannel = (Channel)ChannelSelection->WhichOptionIsChosen();

	if (CurrentChannelChoice != AllChannels && NextChannel == AllChannels) {
		HideChannelSettings();
		ShowAllChannelsSettings();
	}

	if (CurrentChannelChoice == AllChannels && NextChannel != AllChannels) {
		HideAllChannelsSettings();
		ShowChannelSettings();
	}

	switch (NextChannel) {
	case Channel1:
	{
		ChannelSettings->ChangeName("Channel1");
		break;
	}
	case Channel2:
	{
		ChannelSettings->ChangeName("Channel2");
		break;
	}
	case Channel3:
	{
		ChannelSettings->ChangeName("Channel3");
		break;
	}
	case Channel4:
	{
		ChannelSettings->ChangeName("Channel4");
		break;
	}
	}
	CurrentChannelChoice = NextChannel;

	Port_RS->SetCurrentChannelSelection(NextChannel);
}

void SetOfControls::LoadAndSendGlobalSettings()
{
	ResponseTextBox->AddText("Loading data...\n");
	bool SetBeep= BeepOn->IsChecked();
	bool SetZero= ZeroSupressOn->IsChecked();
	bool SetSP_Clear = PwrClearOn->IsChecked();
	bool SetFactorySettings = FactorySetOn->IsChecked();

	ResponseTextBox->AddText("Sending...\n");
	
	if (SetFactorySettings) {
		string FactorysetResponse=Port_RS->SetFactorySettings();
		ResponseTextBox->AddText("Factory settings are set.\n");
		return;
	}

	string BeepResponse = Port_RS->SetAudioBeep(SetBeep);
	ResponseTextBox->AddText(BeepResponse);
	
	string ZeroSupressResponse = Port_RS->SetZeroSupress(SetZero);
	ResponseTextBox->AddText(ZeroSupressResponse);
	
	string SP_ClearResponse = Port_RS->SetPwrSP_Clear(SetSP_Clear);
	ResponseTextBox->AddText(SP_ClearResponse);

	ResponseTextBox->AddText("All done.\n");
}

void SetOfControls::LoadAndSendChannelSettings()
{
	
	ResponseTextBox->AddText("Loading data...\n");
	//Input values:
	int PortTypeInSelection = PortTypeSignalIn->WhichOptionIsChosen();
	int DecimalPointSelection = DecimalPoint->WhichOptionIsChosen();
	int MeasureUnitSelection = MeasureUnits->WhichOptionIsChosen();
	int TimeBaseSelection = TimeBase->WhichOptionIsChosen();
	
	char* PV_FullScaleValue = PV_FullScale->GetText();
	char* GasFactorValue = GasFactor->GetText();

	//Output values:
	int PortTypeOutSelection = PortTypeSignalOut->WhichOptionIsChosen();
	int SP_FunctionSelection = SP_Function->WhichOptionIsChosen()+1;
	int SP_ValveSelection=SP_VOR->WhichOptionIsChosen();
	int ProgrammingSourceChoice = ProgrammingSource->WhichOptionIsChosen();

	char* SP_RateValue = SP_Rate->GetText();
	char* SP_FullScaleValue = SP_FullScale->GetText();
	char* NewBatchValue = BatchValue->GetText();

	bool SetResetTotalizer=Reset_PV_Totalizer->IsChecked();

	ResponseTextBox->AddText("Sending...\n");
	
	//Input values:
	if (PortTypeInSelection >= 0) {
		string PortTypeInResponse = Port_RS->SetPortTypeIn(PortTypeInSelection);
		ResponseTextBox->AddText(PortTypeInResponse);
	}
	if (DecimalPointSelection>=0) {
		string DecimalPointResponse = Port_RS->SetDecimalPoint(DecimalPointSelection);
		ResponseTextBox->AddText(DecimalPointResponse);
	}
	if (MeasureUnitSelection >= 0) {
		string MeasureUnitsResponse = Port_RS->SetMeasureUnit(MeasureUnitSelection);
		ResponseTextBox->AddText(MeasureUnitsResponse);
	}
	if (TimeBaseSelection >= 0) {
		string TimeBaseResponse = Port_RS->SetTimeBase(TimeBaseSelection);
		ResponseTextBox->AddText(TimeBaseResponse);
	}
	
	if (IsThatTextANumber(PV_FullScaleValue)) {
		string PVFullScaleValueResponse = Port_RS->SetPVFullScale(PV_FullScaleValue);
		ResponseTextBox->AddText(PVFullScaleValueResponse);
	}
	
	if (IsThatTextANumber(GasFactorValue)) {
		string GasFactorResponse = Port_RS->SetGasFactor(GasFactorValue);
		ResponseTextBox->AddText(GasFactorResponse);
	}
	
	//Output Values:
	if (PortTypeOutSelection >= 0) {
		string PortTypeOutResponse = Port_RS->SetPortTypeOut(PortTypeOutSelection);
		ResponseTextBox->AddText(PortTypeOutResponse);
	}
	if (SP_FunctionSelection >= 0) {
		string SP_FunctionResponse = Port_RS->SetSPFunction(SP_FunctionSelection);
		ResponseTextBox->AddText(SP_FunctionResponse);
	}
	if (SP_ValveSelection >= 0) {
		string SP_ValveResponse = Port_RS->SetSPValve(SP_ValveSelection);
		ResponseTextBox->AddText(SP_ValveResponse);
	}
	if (ProgrammingSourceChoice>=0) {
		string ProgrammingSourceResponse = Port_RS->SetProgrammingSource(ProgrammingSourceChoice);
		ResponseTextBox->AddText(ProgrammingSourceResponse);
	}
	
	if (IsThatTextANumber(SP_FullScaleValue)) {
		string SP_FullScaleResponse = Port_RS->SetSPFullScale(SP_FullScaleValue);
		ResponseTextBox->AddText(SP_FullScaleResponse);
	}
	
	if (SetResetTotalizer) {
		string ResetTotalizerResponse = Port_RS->ResetTotalizer();
		ResponseTextBox->AddText(ResetTotalizerResponse);
	}
	
	if (SP_ValveSelection != 0) {
		ResponseTextBox->AddText("All done.\n");
		return;
	}

	if (SP_FunctionSelection==1 && IsThatTextANumber(SP_RateValue)) {
		string RateValueResponse = Port_RS->SetRateValue(SP_RateValue);
		ResponseTextBox->AddText(RateValueResponse);
	}
	if (SP_FunctionSelection==2 && IsThatTextANumber(NewBatchValue)) {
		string BatchValueResponse = Port_RS->SetBatchValue(NewBatchValue);
		ResponseTextBox->AddText(BatchValueResponse);
	}


	ResponseTextBox->AddText("All done.\n");
}

void SetOfControls::LoadAndSendAllChannelsSettings()
{
	ResponseTextBox->AddText("Loading data...\n");
	int Master = WhichMasterIsChosen();
	bool Channel1Checked = Slave1->IsChecked();
	bool Channel2Checked = Slave2->IsChecked();
	bool Channel3Checked = Slave3->IsChecked();
	bool Channel4Checked = Slave4->IsChecked();

	char* Channel1Value= BlendValueChannel1->GetText();
	char* Channel2Value= BlendValueChannel2->GetText();
	char* Channel3Value= BlendValueChannel3->GetText();
	char* Channel4Value= BlendValueChannel4->GetText();

	bool StopAllBlendsAndBatches = StopBlendingsAndBatches->IsChecked();
	
	if (StopAllBlendsAndBatches) {
		Port_RS->StopAllBlending();
		ResponseTextBox->AddText("All blends and batches stopped.\n");
		return;
	}

	if (Master == 0) {
		ResponseTextBox->AddText("No new blending mode is set.\n");
		return;
	}

	ResponseTextBox->AddText("Sending...\n");

	if (Channel1Checked &&IsThatTextANumber(Channel1Value)) {
		string response;
		Port_RS->SetCurrentChannelSelection(Channel1);
		if (Master!=1) {
			Port_RS->SetSPFunction(3);
			response=Port_RS->SetBlendValue(Channel1Value);
		}
		else {
			response=Port_RS->SetRateValue(Channel1Value);
		}
		ResponseTextBox->AddText(response);
	}
	if (Channel2Checked &&IsThatTextANumber(Channel2Value)) {
		string response;
		Port_RS->SetCurrentChannelSelection(Channel2);
		if (Master != 2) {
			Port_RS->SetSPFunction(3);
			response=Port_RS->SetBlendValue(Channel2Value);
		}
		else {
			response=Port_RS->SetRateValue(Channel2Value);
		}
		ResponseTextBox->AddText(response);
	}
	if (Channel3Checked &&IsThatTextANumber(Channel3Value)) {
		string response;
		Port_RS->SetCurrentChannelSelection(Channel3);
		if (Master != 3) {
			Port_RS->SetSPFunction(3);
			response=Port_RS->SetBlendValue(Channel3Value);
		}
		else {
			response=Port_RS->SetRateValue(Channel3Value);
		}
		ResponseTextBox->AddText(response);
	}
	if (Channel4Checked &&IsThatTextANumber(Channel4Value)) {
		string response;
		Port_RS->SetCurrentChannelSelection(Channel4);
		if (Master != 4) {
			Port_RS->SetSPFunction(3);
			response=Port_RS->SetBlendValue(Channel4Value);
		}
		else {
			response=Port_RS->SetRateValue(Channel4Value);
		}
		ResponseTextBox->AddText(response);
	}

	Port_RS->SetOnBlendingMode(Master);
	
	ResponseTextBox->AddText("All done.\n");
}

bool SetOfControls::IsThatTextANumber(const char text[])
{
	if ((strlen(text) == 0)) {
		return false;
	}
	char* bufor;
	double example= strtod(text, &bufor);
	
	return ((strlen(bufor)==0));	//bufor==NULL || 
}

int SetOfControls::WhichMasterIsChosen()
{
	if (Master1->IsChecked()) {
		return 1;
	}
	if (Master2->IsChecked()) {
		return 2;
	}
	if (Master3->IsChecked()) {
		return 3;
	}
	if (Master4->IsChecked()) {
		return 4;
	}
	return 0;
}

void SetOfControls::OnCommand(int id)
{
	switch (id) {
	case ID_COMBOBOX2:
	{
		DealWithChannelChange();
		break;
	}case ID_COMBOBOX8:
	{
		if (SP_Function->WhichOptionIsChosen() == 0) {
			SP_Rate->SetNotToReadOnly();
			BatchValue->SetToReadOnly();
		}
		else {
			SP_Rate->SetToReadOnly();
			BatchValue->SetNotToReadOnly();
		}
		break;
	}
	case ID_COMBOBOX9:
	{
		if (SP_VOR->WhichOptionIsChosen() != 0) {
			SP_Rate->SetToReadOnly();
			BatchValue->SetToReadOnly();
		}
		else {
			SP_Rate->SetNotToReadOnly();
			BatchValue->SetNotToReadOnly();
		}
		break;
	}
	case ID_BUTTON1:
	{
		CreatePortAndOtherControls();
		break;
	}
	case ID_BUTTON2:
	{
		ResponseTextBox->ClearTextBox();
		break;
	}
	case ID_BUTTON3:
	{
		try {
			LoadAndSendGlobalSettings();
		}
		catch (Exception e) {
			ResponseTextBox->AddText(e.getMessage());
		}
		break;
	}
	case ID_BUTTON4:
	{
		ResponseTextBox->AddText("Loading...\n");				//taka konstrukcja do wszystkich case'ów
		try {
			string GlobalInformation = Port_RS->GetGlobalInfo();
			ResponseTextBox->AddText(GlobalInformation);
		}
		catch (Exception e) {
			ResponseTextBox->AddText(e.getMessage());
		}
		break;
	}
	case ID_BUTTON5:
	{
		try {
			LoadAndSendChannelSettings();
		}
		catch (Exception e) {
			ResponseTextBox->AddText(e.getMessage());
		}
		break;
	}
	case ID_BUTTON6:
	{
		ResponseTextBox->AddText("Loading...\n");
		try {
			string ChannelInformation = Port_RS->GetChannelInfo();
			ResponseTextBox->AddText(ChannelInformation);
		}
		catch (Exception e) {
			ResponseTextBox->AddText(e.getMessage());
		}
		break;
	}
	case ID_BUTTON7:
	{
		try{
			LoadAndSendAllChannelsSettings();
		}
		catch (Exception e) {
			ResponseTextBox->AddText(e.getMessage());
		}
		break;
	}
	case ID_BUTTON8:
	{
		ResponseTextBox->AddText("Loading...\n");
		try {
			string AllChannelsInformation = Port_RS->GetAllChannelsInfo();
			ResponseTextBox->AddText(AllChannelsInformation);
		}
		catch (Exception e) {
			ResponseTextBox->AddText(e.getMessage());
		}
		break;
	}
	case ID_CHECKBOX1:
	{
		FactorySetOn->ChangeCheckedStatus();
		break;
	}
	case ID_CHECKBOX2:
	{
		Reset_PV_Totalizer->ChangeCheckedStatus();
		break;
	}
	case ID_CHECKBOX3:
	{
		Slave1->ChangeCheckedStatus();
		if (Slave1->IsChecked()) {
			BlendValueChannel1->SetNotToReadOnly();
		}
		else {
			BlendValueChannel1->SetToReadOnly();
		}
		break;
	}
	case ID_CHECKBOX4:
	{
		Slave2->ChangeCheckedStatus();
		if (Slave2->IsChecked()) {
			BlendValueChannel2->SetNotToReadOnly();
		}
		else {
			BlendValueChannel2->SetToReadOnly();
		}
		break;
	}
	case ID_CHECKBOX5:
	{
		Slave3->ChangeCheckedStatus();
		if (Slave3->IsChecked()) {
			BlendValueChannel3->SetNotToReadOnly();
		}
		else {
			BlendValueChannel3->SetToReadOnly();
		}
		break;
	}
	case ID_CHECKBOX6:
	{
		Slave4->ChangeCheckedStatus();
		if (Slave4->IsChecked()) {
			BlendValueChannel4->SetNotToReadOnly();
		}
		else {
			BlendValueChannel4->SetToReadOnly();
		}
		break;
	}
	case ID_CHECKBOX7:
	{
		StopBlendingsAndBatches->ChangeCheckedStatus();
		break;
	}
	case ID_RADIO1:
	{
		CheckRadioButton(parentInfo->hHandle, ID_RADIO1, ID_RADIO2, ID_RADIO1);
		break;
	}
	case ID_RADIO2:
	{
		CheckRadioButton(parentInfo->hHandle, ID_RADIO1, ID_RADIO2, ID_RADIO2);
		Slave2->SetToChecked();
		break;
	}
	case ID_RADIO3:
	{
		CheckRadioButton(parentInfo->hHandle, ID_RADIO3, ID_RADIO4, ID_RADIO3);
		break;
	}
	case ID_RADIO4:
	{
		CheckRadioButton(parentInfo->hHandle, ID_RADIO3, ID_RADIO4, ID_RADIO4);
		break;
	}
	case ID_RADIO5:
	{
		CheckRadioButton(parentInfo->hHandle, ID_RADIO5, ID_RADIO6, ID_RADIO5);
		break;
	}
	case ID_RADIO6:
	{
		CheckRadioButton(parentInfo->hHandle, ID_RADIO5, ID_RADIO6, ID_RADIO6);
		break;
	}
	case ID_RADIO7:
	{
		CheckRadioButton(parentInfo->hHandle, ID_RADIO7, ID_RADIO10, ID_RADIO7);
		CheckRadioButton(parentInfo->hHandle, ID_CHECKBOX3, ID_CHECKBOX6, ID_CHECKBOX3);
		BlendValueChannel1->SetNotToReadOnly();
		break;
	}
	case ID_RADIO8:
	{
		CheckRadioButton(parentInfo->hHandle, ID_RADIO7, ID_RADIO10, ID_RADIO8);
		CheckRadioButton(parentInfo->hHandle, ID_CHECKBOX3, ID_CHECKBOX6, ID_CHECKBOX4);
		BlendValueChannel2->SetNotToReadOnly();
		break;
	}
	case ID_RADIO9:
	{
		CheckRadioButton(parentInfo->hHandle, ID_RADIO7, ID_RADIO10, ID_RADIO9);
		CheckRadioButton(parentInfo->hHandle, ID_CHECKBOX3, ID_CHECKBOX6, ID_CHECKBOX5);
		BlendValueChannel3->SetNotToReadOnly();
		break;
	}
	case ID_RADIO10:
	{
		CheckRadioButton(parentInfo->hHandle, ID_RADIO7, ID_RADIO10, ID_RADIO10);
		CheckRadioButton(parentInfo->hHandle, ID_CHECKBOX3, ID_CHECKBOX6, ID_CHECKBOX6);
		BlendValueChannel4->SetNotToReadOnly();
		break;
	}
	default:
		return;
	}
	return;
}

HBRUSH SetOfControls::OnColor(HDC wParam, HWND lParam)
{
	if (ResponseTextBox->IsItTheSameHandle(lParam)) {										//kolejne na wyci¹ganie uchwytu
		SetTextColor(wParam, RGB(0, 0, 0));
		SetBkColor(wParam, GetSysColor(COLOR_WINDOW - 1));
		SetBkMode(wParam, TRANSPARENT);
		SetDCBrushColor(wParam, GetSysColor(COLOR_WINDOW - 1));
		return (HBRUSH)GetStockObject(DC_BRUSH);
	}
	else {
		SetTextColor((HDC)wParam, RGB(0, 0, 0));
		SetBkColor(wParam, RGB(255, 255, 255));
		SetBkMode(wParam, TRANSPARENT);
		SetDCBrushColor(wParam, RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(DC_BRUSH);
	}
}

void SetOfControls::ChangeSizes(int width, int height)
{
	Response->ChangeSize(width - 375, height - 15);
	ResponseTextBox->ChangeSize(width - 380, height - 78);
}
