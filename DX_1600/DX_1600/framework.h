﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>
#include <wrl/client.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

//DirectXTex
#include "../DirectTex/DirectXTex.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

// Types
#include "Types.h"

//Framework
#include "FrameWork/Device/Device.h"

//Render
#include "FrameWork/Render/VertexLayOut.h"
#include "FrameWork/Render/VertexBuffer.h"
#include "FrameWork/Render/VertexShader.h"
#include "FrameWork/Render/PixelShader.h"

//TextureMapping
#include "FrameWork/TextureMapping/SamplerState.h"
#include "FrameWork/TextureMapping/SRV.h"

// Scene
#include "Scene/Scene.h"

// Program
#include "Program/program.h"

extern HWND hWnd;
