#include "application.hpp"

bool Window::RegisterWindowClass()
{
	WNDCLASSEX Win;

	Win.cbSize = sizeof(WNDCLASSEX);
	Win.style = 0;
	Win.lpfnWndProc = WndProcNext;
	Win.cbClsExtra = 0;
	Win.cbWndExtra = 0;
	Win.hInstance = WindowInfo->Instance;
	Win.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Win.hCursor = LoadCursor(NULL, IDC_ARROW);
	Win.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
	Win.lpszMenuName = NULL;
	Win.lpszClassName = ClassName;
	Win.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&Win);
}

//FUNKCJE PROCEDURY OBS£UGUJ¥CEJ OKNO
LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_CTLCOLOREDIT, OnColor);
		HANDLE_MSG(hwnd, WM_SIZE, OnSize);
		HANDLE_MSG(hwnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT Window::WndProcNext(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* ptr;

	if (message == WM_NCCREATE)
	{
		CREATESTRUCT *cs = (CREATESTRUCT*)lParam;
		ptr = (Window*)cs->lpCreateParams;

		SetLastError(0);
		if (SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)ptr) == 0)
		{
			if (GetLastError() != 0)
				return FALSE;
		}
	}
	else
	{
		ptr = (Window*)GetWindowLongPtr(hwnd, GWL_USERDATA);
	}

	if (ptr)	return ptr->WndProc(hwnd,message, wParam, lParam);
	
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void Window::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	Controls->OnCommand(id);
	/*switch (id) {
		case ID_COMBOBOX1:
		{
			//combobox function
			if (!ComboPortSelection->IsAnyOptionChosen())	return;
			SetText(this);
			break;
		}
		case ID_COMBOBOX2:
		{
			//combobox funtion nr 2 (ustawianie dzia³ania)
			break;
		}
		case ID_BUTTON1:
		{
			//wyslij zaadanie do wykonania. Osobna funkcja
			break;
		}
		case ID_RADIO1:
		{
			CheckRadioButton(WindowInfo->hHandle, ID_RADIO1, ID_RADIO2, ID_RADIO1);
			break;
		}
		case ID_RADIO2:
		{
			CheckRadioButton(WindowInfo->hHandle, ID_RADIO1, ID_RADIO2, ID_RADIO2);
			break;
		}
		default:
			return;
	}*/
	return;
}

HBRUSH Window::OnColor(HWND hwnd, HDC wParam, HWND lParam, UINT codeNotify)
{
	return Controls->OnColor(wParam, lParam);
	/*if (lParam == Controls->GetHandleOfText1()) {										//kolejne na wyci¹ganie uchwytu
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
	}*/
}

void Window::OnSize(HWND WindowHandle, UINT wParam, int width, int height)
{
	if (WindowHandle == WindowInfo->hHandle) {
		ChangeSizeOfWindow();
		Controls->ChangeSizes(width, height);
		UpdateWindow(WindowHandle);
	}
}

void Window::OnClose(HWND hwnd) {
	DestroyWindow(hwnd);
}

void Window::OnDestroy(HWND hwnd) {
	PostQuitMessage(0);
}

void Window::ChangeSizeOfWindow()
{
	RECT rect;
	int nWidth, nHeight;
	if (GetWindowRect(WindowInfo->hHandle, &rect))
	{
		nWidth = rect.right - rect.left;
		nHeight = rect.bottom - rect.top;
		MoveWindow(WindowInfo->hHandle, rect.left, rect.top, nWidth, nHeight, TRUE);
	}
}

void Window::MakeWindow()
{
	RegisterWindowClass();						//Czy tu nie wywali, jak nie sprawdzamy, czy siê uda³o i potem z tego pomoc¹ próbujemy zrobiæ uchwyt? Nie. Dzia³a jak trzeba

	WindowInfo->hHandle = CreateWindowEx(WS_EX_CLIENTEDGE, ClassName, "Komunikacja RS", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 550, NULL, NULL, WindowInfo->Instance, this);
}

Window::Window(HINSTANCE HINSTANCE){
	WindowInfo = new WindowInformation(HINSTANCE);
	this->MakeWindow();
	Controls = new SetOfControls(WindowInfo);
}

Window::~Window()
{
	this->OnClose(this->WindowInfo->hHandle);

	delete Controls;
}

void Window::ShowWindowOnScreen(int nCmdShow)
{
	ShowWindow(WindowInfo->hHandle, nCmdShow);			//SW_MAXIMIZE
	UpdateWindow(WindowInfo->hHandle);
}

MSG Window::MessageLoop()
{
	while (GetMessage(&LoopMessage, NULL, 0, 0))
	{
		TranslateMessage(&LoopMessage);
		DispatchMessage(&LoopMessage);
	}
	return LoopMessage;
}

bool Window::IsValid()
{
	return (WindowInfo->hHandle == NULL);
}
