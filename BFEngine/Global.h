#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "./timer.h"
#include "./input.h"
#include "./window.h"
#include "./d3d.h"
#include "./Debug.h"
#include "./BFEngine.h"
#include "./globalvar.h"
#include "./camera.h"
#include "./DebugCamera.h"
#include "./StaticCamera.h"
#include "./light.h"
//#include "./DlgEngineInit.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInst;
extern BFEngine *g_pBFEngine;
extern LPDIRECT3DDEVICE9 g_pD3device; 
//extern ST_DISPLAYMODE g_DisMode;

#endif