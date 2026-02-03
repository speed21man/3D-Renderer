#include "./window.h"
#include "./global.h"

HWND g_hWnd;
HINSTANCE g_hInst;

CWindow *pWindow = NULL;
//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 생성자와 소멸자
//////////////////////////////////////////////////////////////////
CWindow::CWindow(void)
{
	pWindow = this;
	//this->Init();
}

CWindow::~CWindow(void)
{
	//this->Release();
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 윈도우 레지스터리를 등록시키고 CWindow를 초기화 시킴
// 반환값 : bool
//////////////////////////////////////////////////////////////////
bool CWindow::Init()
{
	return true;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 윈도우 레지스터리를 등록 함수
// 반환값 : 없음
//////////////////////////////////////////////////////////////////
void CWindow::WndClassRegister(HINSTANCE hInst)
{
	WNDCLASSEX wcx;

	wcx.cbSize		= sizeof( wcx );
	wcx.style		= CS_HREDRAW | CS_VREDRAW;					// 윈도우가 어떤 형태를 가질 것인가를 지정하는 멤버이다.
	wcx.lpfnWndProc = (WNDPROC)CWindow::StaticWndProc;				// 윈도우의 메시지 처리 함수를 지정한다. ( 여기서 지정한 함수가 모든 메시지를 처리한다. )
	wcx.cbClsExtra	= 0;										// 일종의 예약 영역이다. 윈도우즈가 내부적으로 사용하며 아주 특수한 목적에 사용되는 여분의 공간이다. 사용하지 않을 경우 0으로 지정.
	wcx.cbWndExtra	= 0;										// 일종의 예약 영역이다. 윈도우즈가 내부적으로 사용하며 아주 특수한 목적에 사용되는 여분의 공간이다. 사용하지 않을 경우 0으로 지정.
	wcx.hInstance	= hInst;								// 윈도우 클래스를 등록하는 프로그램의 번호
	wcx.hIcon 		= LoadIcon( NULL,IDI_APPLICATION );			// 윈도우가 사용할 아이콘을 지정한다.
	wcx.hCursor		= LoadCursor( NULL,IDC_ARROW );				// 윈도우가 사용할 마우스 커서를 지정한다.
	wcx.hIconSm		= NULL;
	wcx.hbrBackground = (HBRUSH) GetStockObject( WHITE_BRUSH );	// 윈도우의 배경 색상을 지정한다. 윈도우의 배경 색상을 채색할 브러시를 지정한다.	
	wcx.lpszMenuName  = NULL;									// 사용할 메뉴를 지정한다.
	wcx.lpszClassName = "BFENGINE";							// 윈도우 클래스의 이름을 문자열로 정의한다.

	RegisterClassEx(&wcx);

}

////////////////////////////////////////////////////////////////////
//// 작성자 : 박정엽
//// 작성일 : 08.03.25
//// 기능 : 메세지 루프를 돌림
//// 반환값 : 없음
////////////////////////////////////////////////////////////////////
//void CWindow::Run()
//{
//	while(1)
//	{
//		if(!PeekMessage(m_Msg, g_hWnd, 0, 0, 0))
//		{
//
//		}	
//	}
//}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 메모리 해제
// 반환값 : bool
//////////////////////////////////////////////////////////////////
bool CWindow::Release()
{
	return true;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 윈도우 생성
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CWindow::CreateWin(HINSTANCE hInst)
{
	//인스턴스를 전역으로 쓰기 위함
	g_hInst = hInst;

	this->WndClassRegister(hInst);

	//g_hWnd = CreateWindowEx(NULL, "BFENGINE", "+_+ 건들면 뒤진다", 
	//						WS_OVERLAPPEDWINDOW,
	//						0, 0, 
	//						CGlobalVar::CreateInstance()->GetDisplayMode().Width,
	//						CGlobalVar::CreateInstance()->GetDisplayMode().Height,
	//						NULL, NULL, hInst, NULL );

	g_hWnd = CreateWindowEx(NULL, "BFENGINE", "+_+ 건들면 뒤진다", 
							WS_OVERLAPPEDWINDOW,
							0, 0, 
							1024,
							768,
							NULL, NULL, hInst, NULL );

	ShowWindow(g_hWnd , SW_SHOW); 

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.26
// 기능 : 윈도우 메세지 프로시져
// 반환값 : LRESULT
//////////////////////////////////////////////////////////////////
LRESULT CALLBACK CWindow::StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return pWindow->WndProc(hWnd, msg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.06
// 기능 : 윈도우 메세지 프로시져
// 반환값 : LRESULT
//////////////////////////////////////////////////////////////////
LRESULT CWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}