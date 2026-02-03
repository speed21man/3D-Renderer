#include "./d3d.h"
#include "./global.h"

LPDIRECT3DDEVICE9 g_pD3device;
//ST_DISPLAYMODE g_DisMode;

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.26
// 기능 : 생성자와 소멸자
// 반환값 : 없음
//////////////////////////////////////////////////////////////////
D3D::D3D(void)
:m_pD3d9(NULL)
{
	//this->m_pD3d9 = NULL;
	memset(&this->m_d3dpp, 0, sizeof(this->m_d3dpp));	
	memset(&this->m_d3dcrt, 0, sizeof(this->m_d3dcrt));
	memset(&this->m_pCaps, 0, sizeof(this->m_pCaps));
	memset(&this->m_D3dFormat, 0, sizeof(this->m_D3dFormat));

	//memset(&g_DisMode, 0, sizeof(g_DisMode));
	//this->Init();
}

D3D::~D3D(void)
{
	//SAFEDEL(this->m_pD3d9);
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.26
// 기능 : DIrectx9 초기화
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL D3D::Init()
{
	if(FAILED(this->m_pD3d9 = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return FALSE;

	//this->CreateDevice9();

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.26
// 기능 : Direcx9 해제
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL D3D::Release()
{
	SAFERELEASE(this->m_pD3d9);
	SAFERELEASE(g_pD3device);

	std::vector<D3DDISPLAYMODE*>::iterator it;

	for(it = this->vDisMode.begin() ; it < this->vDisMode.end()  ; it++)
	{
		delete (*it);
	}
	this->vDisMode.clear();

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.26
// 기능 : directx9 디바이스 생성
// 반환값 : HRESULT
//////////////////////////////////////////////////////////////////
HRESULT D3D::CreateDevice9()
{
	//this->m_pD3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &this->m_pCaps);

	this->SetupDevice9();

	return S_OK;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.26
// 기능 : directx10 디바이스 생성(나중에 먼 훗날 작업할 것임 ㅎㅎ)
// 반환값 : HRESULT
//////////////////////////////////////////////////////////////////
HRESULT D3D::CreateDevice10()
{
	return S_OK;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.26
// 기능 : D3DPRESENT_PARAMETERS의 값을 채우고 디바이스 생성
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////

HRESULT D3D::SetupDevice9(void)
{
	this->m_d3dcrt.AdapterOrdinal = ADADPTMODE;
	this->m_d3dcrt.BehaviorFlags = BEHAVIORMODE;
	this->m_d3dcrt.DeviceType = DEVTYPE;
	this->m_d3dcrt.hFocusWindow = g_hWnd;

	this->m_d3dpp.Windowed = TRUE;//g_DisMode.bFullScreen;
	this->m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->m_d3dpp.BackBufferFormat = PreDisplayMode().Format;
	//this->m_d3dpp.EnableAutoDepthStencil = TRUE;
	this->m_d3dpp.EnableAutoDepthStencil = STENCILMODE;
	//this->m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	this->m_d3dpp.AutoDepthStencilFormat = D3DSTENCILFORMAT;
	this->m_d3dpp.FullScreen_RefreshRateInHz = 0;
	this->m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; 

	if(FAILED(this->m_pD3d9->CreateDevice(this->m_d3dcrt.AdapterOrdinal,
									this->m_d3dcrt.DeviceType, 
									this->m_d3dcrt.hFocusWindow, 
									this->m_d3dcrt.BehaviorFlags, 
									&this->m_d3dpp, 
									&g_pD3device)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.27
// 기능 : 하드웨어 장치에서 지원할 수 있는 해상도를 검사한다.
// 반환값 : HRESULT
//////////////////////////////////////////////////////////////////
HRESULT D3D::CheckDisplayMode(void)
{
	D3DDISPLAYMODE *pDisMode = NULL;

	//long nAdapter = m_pD3d9->GetAdapterCount();

	this->m_D3dFormat = this->PreDisplayMode().Format;

	long modeCnt = m_pD3d9->GetAdapterModeCount(ADADPTMODE, this->m_D3dFormat );

	for(long i=0; i < modeCnt; i++)
	{
		pDisMode = NULL;
		
		SAFENEW(pDisMode, D3DDISPLAYMODE);
		m_pD3d9->EnumAdapterModes(ADADPTMODE, this->m_D3dFormat, i, pDisMode);

		this->vDisMode.push_back(pDisMode);
	}
	
	return S_OK;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.27
// 기능 : 현재 해상도 정보를 가져온다.
// 반환값 : D3DDISPLAYMODE
//////////////////////////////////////////////////////////////////
const D3DDISPLAYMODE D3D::PreDisplayMode(void)
{
	D3DDISPLAYMODE PreDisMode;

	//현재 디스플레이의 해상도 정보를 가져온다.
	m_pD3d9->GetAdapterDisplayMode(ADADPTMODE, &PreDisMode);

	return PreDisMode;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.28
// 기능 : 현재 디스플레이의 이름을 가져온다.
// 반환값 : D3DADAPTER_IDENTIFIER9
//////////////////////////////////////////////////////////////////
const D3DADAPTER_IDENTIFIER9 D3D::PreDisplayIdentifier(void)
{
	D3DADAPTER_IDENTIFIER9 Adapter;

	m_pD3d9->GetAdapterIdentifier(ADADPTMODE, 0, &Adapter);

	return Adapter;
}