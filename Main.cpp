#include<iostream>
#include"application.hpp"
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Window hWindow(hInstance);
	
	if (hWindow.IsValid()) {
		MessageBox(NULL, "Problemy z aplikacj¹. Spróbuj uruchomiæ ponownie", "Uwaga!", MB_ICONEXCLAMATION);
		return 1;
	}
	
	hWindow.ShowWindowOnScreen(nCmdShow);

	MSG Message=hWindow.MessageLoop();

	return Message.wParam;
}
