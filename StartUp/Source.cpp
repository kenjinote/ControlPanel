#include <stdio.h>
#include <windows.h>
#include <cpl.h> 

typedef LONG(WINAPI *PCPLAPPLET)(HWND hwndCPL, UINT message, LPARAM lParam1, LPARAM lParam2);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	HMODULE hModule = LoadLibrary(TEXT("ControlPanel.cpl"));
	PCPLAPPLET CPlApplet = (PCPLAPPLET)GetProcAddress(hModule, "CPlApplet");
	HWND hWnd = GetDesktopWindow();
	LONG lResult = CPlApplet(hWnd, CPL_INIT, 0, 0);
	if (lResult)
	{
		CPLINFO info;
		lResult = CPlApplet(hWnd, CPL_GETCOUNT, 0, 0);
		for (LRESULT l = 0; l < lResult; ++l)
			lResult = CPlApplet(hWnd, CPL_INQUIRE, l, (LPARAM)&info);

		lResult = CPlApplet(hWnd, CPL_DBLCLK, 0, 0);
		lResult = CPlApplet(hWnd, CPL_STOP, 0, 0);
		lResult = CPlApplet(hWnd, CPL_EXIT, 0, 0);
	}
	FreeLibrary(hModule);
	return 0;
}