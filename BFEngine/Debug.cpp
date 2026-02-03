#include ".\debug.h"
#include "./global.h"

CDebug::CDebug(void) : 
dwbefFrame(0),
dwMillisec(0),
fFrameCount(0.0f)
{
}

CDebug::~CDebug(void)
{
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.01
// 기능 : 디버그 모드 초기화
// 반환값 : bool
//////////////////////////////////////////////////////////////////
BOOL CDebug::Init(void)
{
	memset(&this->vPos1, 0, sizeof(this->vPos1));
	memset(&this->vPos2, 0, sizeof(this->vPos2));
	memset(&this->vPos3, 0, sizeof(this->vPos3));
	memset(&this->vPos4, 0, sizeof(this->vPos4));

	m_Skymap.Init();

	m_Skymap.SetSkyMapTexture(0, "../Resource/SkyMap/hel_05.dds");
	m_Skymap.SetSkyMapTexture(1, "../Resource/SkyMap/hel_06.dds");
	m_Skymap.SetSkyMapTexture(2, "../Resource/SkyMap/hel_02.dds");
	m_Skymap.SetSkyMapTexture(3, "../Resource/SkyMap/hel_04.dds");
	m_Skymap.SetSkyMapTexture(4, "../Resource/SkyMap/hel_03.dds");
	m_Skymap.SetSkyMapTexture(5, "../Resource/SkyMap/hel_01.dds");

	m_Skymap.SetTextureUVPos();

	this->InitFont();

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.01
// 기능 : 디버그 모드 연산
// 반환값 : bool
//////////////////////////////////////////////////////////////////
BOOL CDebug::Frame(void)
{
	this->vPos1.x = 0.0f;
	this->vPos1.y = 0.0f;
	this->vPos1.z = 0.0f;

	this->vPos2.x = 100.0f;
	this->vPos2.y = 0.0f;
	this->vPos2.z = 0.0f;

	this->vPos3.x = 0.0f;
	this->vPos3.y = 100.0f;
	this->vPos3.z = 0.0f;

	this->vPos4.x = 0.0f;
	this->vPos4.y = 0.0f;
	this->vPos4.z = 100.0f;

	m_Skymap.Frame();

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.01
// 기능 : 디버그 모드 랜더링
// 반환값 : bool
//////////////////////////////////////////////////////////////////
BOOL CDebug::Render(void)
{
	this->CheckFrame();

	this->DrawLine(vPos1, vPos2, 0xff0000ff);
	this->DrawLine(vPos1, vPos3, 0xff00ff00);
	this->DrawLine(vPos1, vPos4, 0xffff0000);

	m_Skymap.Render();

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.01
// 기능 : 디버그 모드 해제
// 반환값 : bool
//////////////////////////////////////////////////////////////////
BOOL CDebug::Release(void)
{

	m_Skymap.Release();
	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.01
// 기능 : 디버그 모드 선그리기
// 반환값 : bool
//////////////////////////////////////////////////////////////////
BOOL CDebug::DrawLine(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DCOLOR color)
{
	g_pD3device->SetFVF(FVFDEBUGLINE);

	this->SetLine(v0, v1);
	g_pD3device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
	g_pD3device->SetRenderState(D3DRS_TEXTUREFACTOR, color);
	g_pD3device->DrawPrimitiveUP(D3DPT_LINELIST, 1, &this->m_dLine, sizeof(ST_DEBUGLINE));

	//바뀐 설정을 원래대로 되돌려 놓는다.
	g_pD3device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	
	return TRUE;
}

BOOL CDebug::SetLine(D3DXVECTOR3 v0, D3DXVECTOR3 v1)
{
	this->m_dLine[0].m_Line.x = v0.x;
	this->m_dLine[0].m_Line.y = v0.y;
	this->m_dLine[0].m_Line.z = v0.z;

	//this->m_dLine[0].Color = 0xffff0000;

	this->m_dLine[1].m_Line.x = v1.x;
	this->m_dLine[1].m_Line.y = v1.y;
	this->m_dLine[1].m_Line.z = v1.z;

	//this->m_dLine[1].Color = 0xffff0000;

	return TRUE;
}



BOOL CDebug::CheckFrame(void)
{
	DWORD fFrame = timeGetTime();

	dwMillisec += fFrame - this->dwbefFrame;

	if(dwMillisec > 1000)
	{
		this->nFPS = (int)this->fFrameCount;

		dwMillisec = 0;
		this->fFrameCount = 0.0f;
	}

	RECT rtFont = {10, 10, 100, 100};
	sprintf(sFrame, "FPS : %d", this->nFPS);

	this->m_font->DrawText(0, sFrame, -1, &rtFont, DT_LEFT, 0xffff0000);
	
	this->dwbefFrame = fFrame;
	this->fFrameCount ++;

	return true;
}


BOOL CDebug::InitFont(void)
{
	D3DXFONT_DESC ftdest;

	memset(&ftdest, 0, sizeof(D3DXFONT_DESC));

	ftdest.CharSet = DEFAULT_CHARSET;
	ftdest.Height = 15;
	ftdest.Width = 7;
	ftdest.Weight = 1000;
	
	strcpy(ftdest.FaceName, "TIme New Roman");

	D3DXCreateFontIndirect(g_pD3device, &ftdest, &this->m_font);
	
	return true;
}
