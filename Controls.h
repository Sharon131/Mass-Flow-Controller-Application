#ifndef CONTROLS
#define CONTROLS
#include "Buttons.h"
#include "IDs.h"
#include "newVersionPortRS.hpp"

class SetOfControls {
private:
	WindowInformation * parentInfo;
	Channel CurrentChannelChoice;
	NewPort* Port_RS;

	Frame *PortSettings;
	ComboBox *ComboPortSelection;
	Button *ConnectWithPort;

	Frame *ChooseChannel;
	ComboBox *ChannelSelection;

	Frame *Response;
	TextBox* ResponseTextBox;
	Button *ClearTextWindow;

	Frame *GlobalSettings;
	RadioButton *BeepOn, *BeepOff, *ZeroSupressOn, *ZeroSupressOff, *PwrClearOn, *PwrClearOff;
	CheckBox* FactorySetOn;
	Button *SendGlobalSettings, *GetGlobalSettings;

	Frame *ChannelSettings;
	//Input Values:
	StaticText *SignalInText,*DecimalPointStatic,*MeasureUnitsStatic, *TimeBaseStatic,*PV_FullScaleStatic,*GasFactorStatic;
	ComboBox *PortTypeSignalIn, *DecimalPoint, *MeasureUnits, *TimeBase;
	TextBox *PV_FullScale, *GasFactor;
	//Output Values:
	StaticText *SignalOutText,*SP_FunctionStatic, *SP_VOR_Static,*ProgrammingSourceStatic, *SP_RateStatic,*SP_FullScaleStatic,*BatchValueStatic;
	ComboBox *PortTypeSignalOut, *SP_Function, *SP_VOR, *ProgrammingSource;
	TextBox *SP_Rate, *SP_FullScale, *BatchValue;
	CheckBox* Reset_PV_Totalizer;
	Button* SendChannelSettings, *GetChannelSettings;

	Frame *AllChannelsSettings;
	StaticText* MasterChoice;
	RadioButton *Master1, *Master2, *Master3, *Master4;
	CheckBox *Slave1, *Slave2, *Slave3, *Slave4;
	CheckBox* StopBlendingsAndBatches;
	TextBox *BlendValueChannel1, *BlendValueChannel2, *BlendValueChannel3, *BlendValueChannel4;
	Button *SendAllChannelsSettings, *GetAllChannelsSettings;

public:
	SetOfControls(WindowInformation * parentInfo);
	~SetOfControls();

private:
	void SetHandlesToNULL();

	void CreatePortSelection();
	void CreateChannelSelection();
	void CreateResponseWindow();

	void CreatePortAndOtherControls();

	string getComOption(int option);

	void CreateGlobalSetting();
	void CreateChannelSettings();
	void CreateAllChannelsSettings();

	void HideChannelSettings();
	void ShowChannelSettings();

	void HideOrShowChannelSettings(HideOrShow choice);

	void HideAllChannelsSettings();
	void ShowAllChannelsSettings();

	void HideOrShowAllChannelsSettings(HideOrShow choice);

	void DealWithChannelChange();

	void LoadAndSendGlobalSettings();
	void LoadAndSendChannelSettings();
	void LoadAndSendAllChannelsSettings();

	bool IsThatTextANumber(const char text[]);
	int WhichMasterIsChosen();

public:
	void OnCommand(int id);
	HBRUSH OnColor(HDC wParam, HWND lParam);
	
	void ChangeSizes(int width, int height);
};

#endif
