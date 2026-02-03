#include ".\input.h"
#include "./global.h"

CInput::CInput(void)
:m_pDi(NULL),
m_pDidevKey(NULL),
m_pDidevMouse(NULL)
{
	memset(&this->m_KeyState, 0, sizeof(this->m_KeyState));
	memset(&this->m_MouseState, 0, sizeof(this->m_MouseState));
}

CInput::~CInput(void)
{
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.06
// 기능 : 초기화
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CInput::Init(void)
{
	InitDirectInput(true, true);
	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.06
// 기능 : 연산처리
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CInput::Frame(void)
{
	if(!this->KeyProcess(this->m_KeyState))
		return FALSE;

	if(!this->MouseProcess(&this->m_MouseState))
		return FALSE;

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.06
// 기능 : 출력처리
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CInput::Render(void)
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.06
// 기능 : 해제
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CInput::Release(void)
{
	if(this->m_pDi)
	{
		if(this->m_pDidevKey)
		{
			this->m_pDidevKey->Unacquire();
			this->m_pDidevKey->Release();
			this->m_pDidevKey = NULL;
		}
		if(this->m_pDidevMouse)
		{
			this->m_pDidevMouse->Unacquire();
			this->m_pDidevMouse->Release();
			this->m_pDidevMouse = NULL;
		}

		this->m_pDi->Release();
		this->m_pDi = NULL;
	}
	return true;
	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.06
// 기능 : 다이렉트 인풋 초기화
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CInput::InitDirectInput(bool keyboard, bool mouse)
{
	HRESULT hr;//GetModuleHandle(NULL)
	if(FAILED(hr = DirectInput8Create(g_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&this->m_pDi, NULL)))
	{
		if( DIERR_BETADIRECTINPUTVERSION == hr)
		{
			int kkk = 0;
		}else if( DIERR_INVALIDPARAM == hr)
		{
			int kkk = 0;
		}else if( DIERR_OLDDIRECTINPUTVERSION == hr)
		{
			int kkk = 0;
		}else if( DIERR_OUTOFMEMORY == hr)
		{
			int kkk = 0;
		}

		return FALSE;
	}

	if(keyboard)
	{
		if(FAILED(this->m_pDi->CreateDevice(GUID_SysKeyboard, &this->m_pDidevKey, NULL)))
			return false;
		if(FAILED(this->m_pDidevKey->SetDataFormat(&c_dfDIKeyboard)))
			return false;
		if(FAILED(this->m_pDidevKey->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY)))
			return false;
		while(m_pDidevKey->Acquire() == DIERR_INPUTLOST);
	}
	if(mouse)
	{
		if(FAILED(this->m_pDi->CreateDevice(GUID_SysMouse, &this->m_pDidevMouse, NULL)))
			return false;
		if(FAILED(this->m_pDidevMouse->SetDataFormat(&c_dfDIMouse)))
			return false;
		if(FAILED(this->m_pDidevMouse->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
			return false;
		while(m_pDidevMouse->Acquire() == DIERR_INPUTLOST);
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.06
// 기능 : 키보드 입력 처리
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CInput::KeyProcess(BYTE *key)
{
	HRESULT m_hr;

	ZeroMemory(key, 256);

	m_hr = this->m_pDidevKey->GetDeviceState(256, key);

	if(FAILED(m_hr))
	{
		m_hr = this->m_pDidevKey->Acquire();
		while(m_hr == DIERR_INPUTLOST)
			this->m_pDidevKey->Acquire();

		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.06
// 기능 : 마우스 입력 처리
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CInput::MouseProcess(DIMOUSESTATE *MouseState)
{
	HRESULT m_hr;
	ZeroMemory(MouseState, sizeof(DIMOUSESTATE));

	m_hr = this->m_pDidevMouse->GetDeviceState(sizeof(DIMOUSESTATE), MouseState);

	if(FAILED(m_hr))
	{
		m_hr = this->m_pDidevMouse->Acquire();
		while(m_hr == DIERR_INPUTLOST)
			this->m_pDidevMouse->Acquire();

		return FALSE;
	}

	return TRUE;	
}