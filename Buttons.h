#ifndef BUTTONS
#define BUTTONS
#include<windows.h>
#include<windowsx.h>
#include<string>

using namespace std;

struct WindowInformation {
	HWND hHandle;
	HINSTANCE Instance;

	WindowInformation(HINSTANCE hInstance);
	WindowInformation(HINSTANCE hInstance, HWND hHandle);
};

struct BoxInfo {
	int ID;
	const char* text;

	BoxInfo(int id, const char name[]);
};

struct Point {
	int x;
	int y;

	Point(int x, int y);
};

struct Size {
	Point* upperLeftCorner;
	int height;
	int width;

	Size(int height, int width, Point* upperLeftCornerPoint);
	~Size();
};

enum TypeOfControl {
	FrameControl,
	StaticTextControl,
	TextBoxWithScroll,
	TextBoxNoScroll,
	ButtonControl,
	RadioButtonControl,
	CheckBoxControl,
	ComboBoxControl
};

enum HideOrShow {
	hide,
	show
};

class Control {
protected:
	HWND hHandle;
	WindowInformation * parentInfo;
	Size* sizeOfControl;
	BoxInfo* ControlInfo;
	HFONT NormalFont;

	void SetParameters(Size* thisSize, WindowInformation* parentInformation, BoxInfo* thisInfo);
	void MakeHandle(TypeOfControl name);

	int CountLength();

public:
	~Control();
	bool IsItTheSameHandle(HWND otherHandle);		//IsTheHandleSameAs();
	void SetFontToNormal();
	void ChangeSize(int width, int height);
	void HideOrShowControl(HideOrShow choice);
	void HideControl();
	void ChangeName(const char newName[]);

	void SetToReadOnly();
	void SetNotToReadOnly();
};

class StaticText
	:public Control
{
	int heightOfText;
public:
	StaticText(Size* sizeOfStatic, WindowInformation* parentInfo, const char textOfControl[]);
	StaticText(Point* position, WindowInformation* parentInfo, const char textOfControl[]);
};

class Frame
	:public Control
{
public:
	Frame(Size* sizeOfFrame, WindowInformation* parentInformation, const char textOfControl[]);
};

class TextBox 
	:public Control
{
public:
	TextBox(Size* sizeOfTextBox, WindowInformation* parentInformation, TypeOfControl WhichTextBox);

	void AddText(string textToAdd);		//AddTextToTheCurrentOne
	void ClearTextBox();
	char* GetText();
};

class Button 
	:public Control
{
	int heightOfButton;
public:
	Button(Size* sizeOfButton, WindowInformation* parentInfo, BoxInfo* thisInfo);
	Button(Point* position, WindowInformation* parentInfo, BoxInfo* thisInfo);
};

class RadioButton
	:public Control
{
	int heightOfText;
public:
	RadioButton(Size* sizeOfRadio, WindowInformation* parentInfo, BoxInfo* thisInfo);
	RadioButton(Point* position, WindowInformation* parentInfo, BoxInfo* thisInfo);

	bool IsChecked();
};

class CheckBox
	:public Control
{
	int heightOfText;
public:
	CheckBox(Size* sizeOfCheckBox, WindowInformation* parentInfo, BoxInfo* thisInfo);
	CheckBox(Point* position, WindowInformation* parentInfo, BoxInfo* thisInfo);
	
	bool IsChecked();
	void SetToChecked();
	void SetToUnChecked();

	void ChangeCheckedStatus();
};

class ComboBox 
	:public Control
{
public:
	ComboBox(Size* sizeOfCombo, WindowInformation* parentInformation, int ID);
	

	//void SetComboText();		//??!! Do dopracowania
	void SetComboPortSelection();
	void SetComboChannelSelection();

	void SetComboPortType();
	void SetComboDecimalPoint();
	void SetComboMeasureUnits();
	void SetComboTimeBase();

	void SetComboSP_Function();
	void SetComboSP_VOR();
	void SetComboProgrammingSource();

	void SetOption(int fromUp);

	bool IsAnyOptionChosen();
	int WhichOptionIsChosen();
};

#endif