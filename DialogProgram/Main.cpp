#include <Windows.h>
#include "resource.h"
#include <tchar.h>

HINSTANCE hInst;

INT_PTR CALLBACK MainProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT WINAPI _tWinMain(HINSTANCE hInstanceExe, HINSTANCE, PTSTR pszCmdLine, int nCmdShow)
{
	hInst = hInstanceExe;
	DialogBox(hInstanceExe, MAKEINTRESOURCE(IDD_MAINBOX), NULL, MainProc);
	return 0;
}

INT_PTR CALLBACK MainProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_BTN_Query && HIWORD(wParam) == BN_CLICKED)
		{
			TCHAR Buffer_Edit[MAX_PATH] = { 0 };
			HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_VariableName);
			SendMessage(hEdit, WM_GETTEXT, (WPARAM)MAX_PATH, (LPARAM)Buffer_Edit);
			PTCHAR Buffer_Env = NULL;
			DWORD dResult = GetEnvironmentVariable(Buffer_Edit, NULL, 0);
			if (dResult != 0)
			{
				Buffer_Env = (PTCHAR)malloc(dResult * sizeof(TCHAR));
				GetEnvironmentVariable(Buffer_Edit, Buffer_Env, dResult);
				HWND hEdit2 = GetDlgItem(hDlg, IDC_EDIT_ENV);
				SendMessage(hEdit2, WM_SETTEXT, 0, (LPARAM)Buffer_Env);
			}
			else
			{
				MessageBox(hDlg, TEXT("Get ENV Variabel Failed."), TEXT("Fail"), MB_OK);
			}
		}
		break;
	}
	return (INT_PTR)FALSE;
}