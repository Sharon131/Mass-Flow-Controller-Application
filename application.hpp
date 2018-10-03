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

	//Port* Comm;		//Potrzebny wskaŸnik na klasê portu, aby móc na nim dzia³aæ

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
	
	bool IsValid();					//mo¿na zamieniæ na zwracanie wyj¹tku w kostruktorze, o ile to zadzia³a
};



#endif