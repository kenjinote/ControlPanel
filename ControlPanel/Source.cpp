#include <Windows.h> 
#include <cpl.h> 
#include <strsafe.h>
#include "resource.h"

#define DLLEXPORT __declspec(dllexport) 
#define DLLIMPORT __declspec(dllimport)
HINSTANCE g_hInstance = NULL;

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD fdReason, LPVOID pvReserved)
{
	switch (fdReason)
	{
	case DLL_PROCESS_ATTACH:
		g_hInstance = hInstance;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

INT_PTR CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		if (wParam == IDOK || wParam == IDCANCEL)
		{
			EndDialog(hWnd, wParam);
		}
		break;
	}
	return 0;
}

LONG CALLBACK CPlApplet(HWND hWnd, UINT message, LPARAM lParam1, LPARAM lParam2)
{
	switch (message)
	{
	case CPL_INIT:
		return 1;
	case CPL_GETCOUNT:
		return 1;
	case CPL_NEWINQUIRE:
		if (lParam2)
		{
			NEWCPLINFO *pNewCpl = (NEWCPLINFO*)lParam2;
			pNewCpl->dwSize = sizeof(NEWCPLINFO);
			pNewCpl->dwFlags = 0;
			pNewCpl->dwHelpContext = 0;
			pNewCpl->lData = 0;
			pNewCpl->hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1));
			StringCbCopy(pNewCpl->szName, sizeof(pNewCpl->szName), TEXT("szName"));
			StringCbCopy(pNewCpl->szInfo, sizeof(pNewCpl->szInfo), TEXT("szInfo"));
			pNewCpl->szHelpFile[0] = 0;
			return 0;
		}
		return 1;
	case CPL_DBLCLK:
		DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DialogProc);
		return 0;
	case CPL_STOP:
	case CPL_EXIT:
	default:
		return 0;
	}
	return 1;
}
