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

#include <windowsx.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

//DirectXTex
#include "../DirectTex/DirectXTex.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

// Imgui
#include "../ImGUi/imgui.h"
#include "../ImGUi/imgui_impl_win32.h"
#include "../ImGUi/imgui_impl_dx11.h"

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

// Types
#include "Types.h"

//Framework
#include "FrameWork/Device/Device.h"

// Math
#include "FrameWork/Math/Vector2.h"
#include "FrameWork/Math/Transform.h"

// Utility
#include "FrameWork/Utility/InputManager.h"
#include "FrameWork/Utility/Timer.h"

//Render
#include "FrameWork/Render/ConstantBuffer.h"
#include "FrameWork/Render/GlobalBuffer.h"
#include "FrameWork/Render/VertexLayOut.h"
#include "FrameWork/Render/VertexBuffer.h"
#include "FrameWork/Render/IndexBuffer.h"
#include "FrameWork/Render/VertexShader.h"
#include "FrameWork/Render/PixelShader.h"

// Collider
#include "FrameWork/Collider/RectCollider.h"

//TextureMapping
#include "FrameWork/TextureMapping/SRV.h"
#include "FrameWork/TextureMapping/SamplerState.h"
#include "FrameWork/TextureMapping/BlendState.h"
#include "FrameWork/TextureMapping/StateManager.h"

// Object
#include "Object/Basic/Quad.h"
#include "Object/SolarSystem/Planet.h"

#include "Object/Dungreed/Bullets.h"
#include "Object/Dungreed/Bow.h"
#include "Object/Dungreed/Player.h"

// Scene
#include "Scene/Scene.h"

// Program
#include "Program/Program.h"

extern HWND hWnd;