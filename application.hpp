#pragma once
#ifndef APPLICATION
#define APPLICATION
#include"IDs.h"
#include "Controls.h"

class Window {
	MSG LoopMessage;
	const LPSTR ClassName = (LPSTR)"PortRS";

	WindowInformation* WindowInfo;
	SetOfControls* Controls;

	//Port* Comm;		//Potrzebny wska�nik na klas� portu, aby m�c na nim dzia�a�

	bool RegisterWindowClass();
	
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);				
	static LRESULT CALLBACK WndProcNext(HWND, UINT, WPARAM, LPARAM);

	void OnCommand(HWND, int, HWND, UINT);
	HBRUSH OnColor(HWND, HDC, HWND, UINT);
	void OnSize(HWND, UINT, int, int);
	void OnClose(HWND);
	void OnDestroy(HWND);

	void ChangeSizeOfWindow();

	void MakeWindow();
	
public:
	Window(HINSTANCE);
	~Window();

	void ShowWindowOnScreen(int nCmdShow);
	MSG MessageLoop();
	
	bool IsValid();					//mo�na zamieni� na zwracanie wyj�tku w kostruktorze, o ile to zadzia�a
};



#endif