#include "Buttons.h"

WindowInformation::WindowInformation(HINSTANCE hInstance):
	Instance(hInstance),
	hHandle(NULL)
{;}

WindowInformation::WindowInformation(HINSTANCE hInstance, HWND hHandle) :
	Instance(hInstance),
	hHandle(hHandle)
{;}

BoxInfo::BoxInfo(int id, const char name[]) :
	ID(id),
	text(name)
{;}

Point::Point(int x, int y):
	x(x),
	y(y)
{;}

Size::Size(int height, int width, Point * upperLeftCornerPoint) :
	height(height),
	width(width),
	upperLeftCorner(upperLeftCornerPoint)
{;}

Size::~Size()
{
	delete upperLeftCorner;
}

void Control::SetParameters(Size * thisSize, WindowInformation * parentInformation, BoxInfo * thisInfo)
{
	parentInfo = parentInformation;
	ControlInfo = thisInfo;
	sizeOfControl = thisSize;
}

void Control::MakeHandle(TypeOfControl text){
	NormalFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	switch (text) {
	case FrameControl:
	{
		hHandle = CreateWindowEx(0, "BUTTON", ControlInfo->text, WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_GROUPBOX,
			sizeOfControl->upperLeftCorner->x, sizeOfControl->upperLeftCorner->y, sizeOfControl->width, sizeOfControl->height,
			parentInfo->hHandle, NULL, parentInfo->Instance, NULL);
		break;
	}
	case StaticTextControl:
	{
		hHandle = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 
			sizeOfControl->upperLeftCorner->x, sizeOfControl->upperLeftCorner->y, sizeOfControl->width, sizeOfControl->height, parentInfo->hHandle, NULL, parentInfo->Instance, NULL);
		SetWindowText(hHandle, ControlInfo->text);
		SendMessage(hHandle, WM_SETFONT, (WPARAM)NormalFont, 0);
		break;
	}
	case TextBoxWithScroll:
	{
		hHandle = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
			sizeOfControl->upperLeftCorner->x, sizeOfControl->upperLeftCorner->y, sizeOfControl->width, sizeOfControl->height, parentInfo->hHandle, NULL, parentInfo->Instance, NULL);
		SendMessage(hHandle, WM_SETFONT, (WPARAM)NormalFont, 0); 
		break;
	}
	case TextBoxNoScroll:
	{
		hHandle = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			sizeOfControl->upperLeftCorner->x, sizeOfControl->upperLeftCorner->y, sizeOfControl->width, sizeOfControl->height, parentInfo->hHandle, NULL, parentInfo->Instance, NULL);
		SendMessage(hHandle, WM_SETFONT, (WPARAM)NormalFont, 0);
		break;
	}
	case ButtonControl:
	{
		hHandle = CreateWindowEx(0, "BUTTON", ControlInfo->text, WS_CHILD | WS_VISIBLE, sizeOfControl->upperLeftCorner->x, sizeOfControl->upperLeftCorner->y, sizeOfControl->width, sizeOfControl->height,
			parentInfo->hHandle,(HMENU)ControlInfo->ID, parentInfo->Instance, NULL);
		break;
	}
	case RadioButtonControl:
	{
		hHandle = CreateWindowEx(0, "BUTTON", ControlInfo->text, WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, sizeOfControl->upperLeftCorner->x, sizeOfControl->upperLeftCorner->y, sizeOfControl->width, sizeOfControl->height,
			parentInfo->hHandle, (HMENU)ControlInfo->ID, parentInfo->Instance, NULL);
		SendMessage(hHandle, WM_SETFONT, (WPARAM)NormalFont, 0);
		break;
	}
	case CheckBoxControl:
	{
		hHandle = CreateWindowEx(0, "BUTTON", ControlInfo->text, WS_CHILD | WS_VISIBLE | BS_CHECKBOX, sizeOfControl->upperLeftCorner->x, sizeOfControl->upperLeftCorner->y, sizeOfControl->width, sizeOfControl->height,
			parentInfo->hHandle, (HMENU)ControlInfo->ID, parentInfo->Instance, NULL);
		SendMessage(hHandle, WM_SETFONT, (WPARAM)NormalFont, 0);
		break;
	}
	case ComboBoxControl:
	{
		hHandle = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			sizeOfControl->upperLeftCorner->x, sizeOfControl->upperLeftCorner->y, sizeOfControl->width, sizeOfControl->height, parentInfo->hHandle, (HMENU)ControlInfo->ID, parentInfo->Instance, NULL);
		SendMessage(hHandle, WM_SETFONT, (WPARAM)NormalFont, 0);
		break;
	}
	default:
	{
		MessageBox(parentInfo->hHandle, "Uwaga", "Cos nie tak", MB_ICONEXCLAMATION);
		break;
	}
	}
}

int Control::CountLength()
{
	return 8 * (strlen(ControlInfo->text));
}

Control::~Control()
{
	delete sizeOfControl;
	delete ControlInfo;
}

bool Control::IsItTheSameHandle(HWND otherHandle)
{
	return (hHandle==otherHandle);
}

void Control::SetFontToNormal()
{
	SendMessage(hHandle, WM_SETFONT, (WPARAM)NormalFont, 0);
}

void Control::ChangeSize(int width, int height)
{
	MoveWindow(hHandle, sizeOfControl->upperLeftCorner->x, sizeOfControl->upperLeftCorner->y, width, height, TRUE);
	sizeOfControl->height = height;
	sizeOfControl->width = width;
}

void Control::HideOrShowControl(HideOrShow choice)
{
	switch (choice) {
	case hide:
	{
		ShowWindow(hHandle, SW_HIDE);
		break;
	}
	case show:
	{
		ShowWindow(hHandle, SW_SHOW);
		break;
	}
	}
}

void Control::HideControl()
{
	ShowWindow(hHandle, SW_HIDE);
}

void Control::ChangeName(const char newName[])
{
	SetWindowTextA(hHandle,newName);
}

void Control::SetToReadOnly()
{
	SendMessage(hHandle,EM_SETREADONLY,TRUE,0);
}

void Control::SetNotToReadOnly()
{
	SendMessage(hHandle, EM_SETREADONLY, FALSE, 0);
}

StaticText::StaticText(Size * sizeOfStatic, WindowInformation * parentInformation, const char textOfControl[]) :
	heightOfText(20)
{
	SetParameters(sizeOfStatic, parentInformation, new BoxInfo(0, textOfControl));
	MakeHandle(StaticTextControl);
}

StaticText::StaticText(Point * position, WindowInformation * parentInformation, const char textOfControl[]) :
	heightOfText(20)
{
	parentInfo = parentInformation;
	ControlInfo = new BoxInfo(0, textOfControl);
	sizeOfControl = new Size(heightOfText, CountLength(), position);
	MakeHandle(StaticTextControl);
}

Frame::Frame(Size * sizeOfFrame, WindowInformation * parentInformation, const char textOfControl[])
{
	SetParameters(sizeOfFrame, parentInformation, new BoxInfo(0, textOfControl));
	MakeHandle(FrameControl);
}

TextBox::TextBox(Size * sizeOfTextBox, WindowInformation * parentInformation, TypeOfControl WhichTextBox)
{
	SetParameters(sizeOfTextBox,parentInformation,NULL);
	MakeHandle(WhichTextBox);
}

void TextBox::AddText(string textToAdd)
{
	DWORD lengthOfPreviousText = GetWindowTextLength(hHandle);
	SendMessage(hHandle, EM_SETSEL, lengthOfPreviousText, lengthOfPreviousText);
	SendMessage(hHandle, EM_REPLACESEL, TRUE, (LPARAM)textToAdd.c_str());
}

void TextBox::ClearTextBox()
{
	SetWindowText(hHandle, "Clear.\n");
}

char* TextBox::GetText()
{
	DWORD lengthOfText = GetWindowTextLength(hHandle);
	LPSTR LoadedText = (LPSTR)GlobalAlloc(GPTR, lengthOfText + 1);
	GetWindowText(hHandle, LoadedText, lengthOfText + 1);

	return LoadedText;
}

Button::Button(Size * sizeOfButton, WindowInformation * parentInformation, BoxInfo * thisInfo):
	heightOfButton(20)
{
	SetParameters(sizeOfButton, parentInformation, thisInfo);
	MakeHandle(ButtonControl);
}

Button::Button(Point* position, WindowInformation * parentInformation, BoxInfo * thisInfo):
	heightOfButton(20)
{
	parentInfo = parentInformation;
	ControlInfo = thisInfo;
	sizeOfControl = new Size(heightOfButton,CountLength(),position);
	MakeHandle(ButtonControl);
}

RadioButton::RadioButton(Size * sizeOfRadio, WindowInformation * parentInformation, BoxInfo * thisInfo) :
	heightOfText(20)
{
	SetParameters(sizeOfRadio, parentInformation, thisInfo);
	MakeHandle(RadioButtonControl);
}

RadioButton::RadioButton(Point * position, WindowInformation * parentInformation, BoxInfo * thisInfo) :
	heightOfText(20)
{
	parentInfo = parentInformation;
	ControlInfo = thisInfo;
	sizeOfControl = new Size(heightOfText, CountLength(), position);
	MakeHandle(RadioButtonControl);
}

bool RadioButton::IsChecked()
{
	return (IsDlgButtonChecked(parentInfo->hHandle, ControlInfo->ID));
}

CheckBox::CheckBox(Size * sizeOfCheckBox, WindowInformation * parentInformation, BoxInfo * thisInfo):
	heightOfText(20)
{
	SetParameters(sizeOfCheckBox, parentInformation, thisInfo);
	MakeHandle(CheckBoxControl);
}

CheckBox::CheckBox(Point * position, WindowInformation * parentInformation, BoxInfo * thisInfo) :
	heightOfText(20)
{
	parentInfo = parentInformation;
	ControlInfo = thisInfo;
	sizeOfControl = new Size(heightOfText, CountLength(), position);
	MakeHandle(CheckBoxControl);
}

bool CheckBox::IsChecked()
{
	return (IsDlgButtonChecked(parentInfo->hHandle, ControlInfo->ID) == BST_CHECKED);
}

void CheckBox::SetToChecked()
{
	CheckDlgButton(parentInfo->hHandle, ControlInfo->ID, BST_CHECKED);
}

void CheckBox::SetToUnChecked()
{
	CheckDlgButton(parentInfo->hHandle, ControlInfo->ID, BST_UNCHECKED);
}

void CheckBox::ChangeCheckedStatus()
{
	if (IsChecked()) {
		SetToUnChecked();
	}
	else {
		SetToChecked();
	}
}

ComboBox::ComboBox(Size * sizeOfCombo, WindowInformation * parentInformation, int ID)
{
	SetParameters(sizeOfCombo,parentInformation, new BoxInfo(ID, ""));
	MakeHandle(ComboBoxControl);
}

void ComboBox::SetComboPortSelection()
{
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM1");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM2");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM3");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM4");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM5");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM6");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM7");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM8");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM9");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM10");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM11");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"COM12");
}

void ComboBox::SetComboChannelSelection()
{
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Channel1");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Channel2");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Channel3");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Channel4");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"All Channels");
}

void ComboBox::SetComboPortType()
{
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Off");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"0-20 mA");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"4-20 mA");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"0-10 V");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"2-10 V");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"0-5 V");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"1-5 V");
}

void ComboBox::SetComboDecimalPoint()
{
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"xxx.");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"xx.x");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"x.xx");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)".xxx");
}

void ComboBox::SetComboMeasureUnits()
{
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"ml");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"mls");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"mln");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"l");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"ls");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"ln");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"cm^3");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"cm^3s");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"cm^3n");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"m^3");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"m^3s");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"m^3n");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"g");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"lb");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"kg");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"ft^3");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"ft^3s");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"ft^3n");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"scc");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"sl");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"bar");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"mbar");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"psi");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"kPa");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Torr");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"atm");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Volt");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"mA");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"oC");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"oK");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"oR");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"oF");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"g/cc");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"sg");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"%");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"lb/in^3");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"lb/ft^3");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"lb/gal");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"kg/m^3");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"g/ml");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"kg/l");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"g/l");
}

void ComboBox::SetComboTimeBase()
{
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"none");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"sec");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"min");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"hrs");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"day");
}

void ComboBox::SetComboSP_Function()
{
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Rate");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Batch");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Blend");
}

void ComboBox::SetComboSP_VOR()
{
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Normal");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Closed");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Open");
}

void ComboBox::SetComboProgrammingSource()
{
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"Keyboard");
	SendMessage(hHandle, CB_ADDSTRING, 0, (LPARAM)"SerialPort");
}

void ComboBox::SetOption(int fromUp)
{
	SendMessage(hHandle, CB_SETCURSEL, (WPARAM)(fromUp-1), (LPARAM)0);
}

bool ComboBox::IsAnyOptionChosen()
{
	return (ComboBox_GetCurSel(hHandle) != CB_ERR);
}

int ComboBox::WhichOptionIsChosen()
{
	return ComboBox_GetCurSel(hHandle);
}
