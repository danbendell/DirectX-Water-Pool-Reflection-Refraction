#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include <windows.h>
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "debugwindowclass.h"
#include "rendertextureclass.h"
#include "reflectionshaderclass.h"
#include "refractionshaderclass.h"
#include "watershaderclass.h"

// GLOBALS
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
	public:
		GraphicsClass();
		GraphicsClass(const GraphicsClass&);
		~GraphicsClass();

		bool Initialize(int, int, HWND);
		void Shutdown();
		bool Frame();
		bool Render();

	private:
		bool RenderToTexture();
		bool RenderRefractionToTexture();
		bool RenderReflectionToTexture();
		bool RenderScene();

	private:
		D3DClass* m_D3D;
		CameraClass* m_Camera;
		ModelClass *m_GroundModel, *m_WallModel, *m_BathModel, *m_WaterModel;
		//ColorShaderClass* m_ColorShader;
		TextureShaderClass* m_TextureShader;
		LightShaderClass* m_LightShader;
		RefractionShaderClass* m_RefractionShader;
		WaterShaderClass* m_WaterShader;
		LightClass* m_Light;
		DebugWindowClass* m_DebugWindow;
		RenderTextureClass *m_RefractionTexture, *m_ReflectionTexture;
		ModelClass* m_FloorModel;
		ReflectionShaderClass* m_ReflectionShader;
		float m_waterHeight, m_waterTranslation;
};

#endif

