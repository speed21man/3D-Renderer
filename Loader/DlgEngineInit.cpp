#include ".\dlgengineinit.h"
#include "../BFEngine/global.h"

#include "./resource.h"

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.27
// 기능 : 생성자와 소멸자
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
CDlgEngineInit::CDlgEngineInit(void)
{
}

CDlgEngineInit::~CDlgEngineInit(void)
{
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.27
// 기능 : 엔진 셋업 다이얼로그 박스 생성(Modal 상태)
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CDlgEngineInit::Init(HINSTANCE hInst)
{
	//CreateDialog(hInst, MAKEINTRESOURCE(ID_DXSETUP), HWND_DESKTOP, (DLGPROC)CDlgEngineInit::DlgMsgProc);
	int result = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, (DLGPROC)CDlgEngineInit::DlgMsgProc);
	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.27
// 기능 : 엔진 셋업 해제
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CDlgEngineInit::Release(void)
{
	//DeleteObject(this->m_hOldBitmap);
	//DeleteObject(this->m_hBitmap);
	//DeleteDC(this->m_MemDC);
	//DeleteDC(this->m_hdc);
	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.27
// 기능 : 다이얼로그 프로시져
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CALLBACK CDlgEngineInit::DlgMsgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP m_hBitmap = NULL;
	static HBITMAP m_hOldBitmap = NULL;
	static HDC m_hdc = NULL;
	static HDC m_MemDC = NULL;

	PAINTSTRUCT ps;

	switch(msg)
	{
	case WM_INITDIALOG:
		
		m_hBitmap = (HBITMAP)LoadImage(g_hInst, DIALOGIMAGEPATH, IMAGE_BITMAP, 0, 0, 
			LR_DEFAULTCOLOR | LR_LOADFROMFILE | 
			LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

		m_hdc = GetDC(hDlg);
		m_MemDC = CreateCompatibleDC(m_hdc);
		
		m_hOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);

		g_pBFEngine->m_pD3d->CheckDisplayMode();

		//비디오 카드 명 출력
		char chrDisplay[255];
		wsprintf(chrDisplay, "%s", g_pBFEngine->m_pD3d->PreDisplayIdentifier().Description);
		SetDlgItemText(hDlg, IDC_EDIT1, chrDisplay);

		//지원할 수 있는 디스플레이 출력
		char chrDisMode[255];
		for(unsigned int i=0; i < g_pBFEngine->m_pD3d->vDisMode.size() ; i++)
		{
			wsprintf(chrDisMode, "%d X %d @ %d", 
				g_pBFEngine->m_pD3d->vDisMode[i]->Width, 
				g_pBFEngine->m_pD3d->vDisMode[i]->Height,
				g_pBFEngine->m_pD3d->vDisMode[i]->RefreshRate);

			SendDlgItemMessage(hDlg, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)chrDisMode);
		}

		//현재 디스플레이 설정 출력
		char chrPreDisMode[255];
		wsprintf(chrPreDisMode, "%d X %d @ %d", 
							g_pBFEngine->m_pD3d->PreDisplayMode().Width, 
							g_pBFEngine->m_pD3d->PreDisplayMode().Height,
							g_pBFEngine->m_pD3d->PreDisplayMode().RefreshRate);

		SetDlgItemText(hDlg, IDC_COMBO1, chrPreDisMode);

		//화면 설정 출력
		char chrScrMode[255];
		wsprintf(chrScrMode, "TRUE");
		SendDlgItemMessage(hDlg, IDC_COMBO2, CB_ADDSTRING, 0, (LPARAM)chrScrMode);

		wsprintf(chrScrMode, "FALSE");
		SendDlgItemMessage(hDlg, IDC_COMBO2, CB_ADDSTRING, 0, (LPARAM)chrScrMode);

		return TRUE;

	case WM_PAINT:
		m_hdc = BeginPaint(hDlg, &ps);
		BitBlt(m_hdc, 17, 20, 400, 150, m_MemDC, 0, 10, SRCCOPY);
		EndPaint(hDlg, &ps);
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			char chrDisMode[255];
			D3DDISPLAYMODE tempDisMode;
			GetDlgItemText(hDlg, IDC_COMBO1, chrDisMode, lstrlen(chrDisMode));

			sscanf(chrDisMode, "%d X %d @ %d", 
										&tempDisMode.Width, 
										&tempDisMode.Height, 
										&tempDisMode.RefreshRate);

			//CGlobalVar::CreateInstance()->SetDisplayMode(&tempDisMode);

			//char chrFullScr[255];
			//GetDlgItemText(hDlg, IDC_COMBO1, chrDisMode, lstrlen(chrFullScr));
			//(strcmp(chrFullScr, "TRUE")) ?  
			//	g_DisMode.bFullScreen = FALSE : g_DisMode.bFullScreen = TRUE; 

			DeleteObject(m_hOldBitmap);
			DeleteObject(m_hBitmap);
			DeleteDC(m_MemDC);
			DeleteDC(m_hdc);

			EndDialog(hDlg, TRUE);
			return TRUE;

		case IDCANCEL:
			//exit(1);
			//DestroyWindow(g_hWnd);
			return TRUE;	
		}
		return FALSE;
	}
	return FALSE;
}