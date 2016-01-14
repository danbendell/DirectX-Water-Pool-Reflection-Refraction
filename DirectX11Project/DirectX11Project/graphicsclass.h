#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include <windows.h>
#include <xnamath.h>
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "firemodelclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "LightingClass.h"
#include "debugwindowclass.h"
#include "rendertextureclass.h"
#include "reflectionshaderclass.h"
#include "refractionshaderclass.h"
#include "watershaderclass.h"
#include "fireshaderclass.h"
#include "inputclass.h"

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
		void MoveWallLeft();
		void MoveWallRight();
		void MoveBallForward();
		void MoveBallBackwards();
		void IncreaseWaterIntensity();
		void DecreaseWaterIntensity();

	private:
		bool RenderModel(ModelClass*, D3DXVECTOR3, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
		bool RenderToTexture();
		bool RenderRefractionToTexture();
		bool RenderReflectionToTexture();
		bool RenderScene();

	private:
		D3DClass* m_D3D;
		CameraClass* m_Camera;
		ModelClass *m_GroundModel, *m_WallModel, *m_BathModel, *m_WaterModel, *m_BallModel, *m_FirePlaceModel, *m_SkyboxModel;
		FireModelClass* m_FireModel;
		//ColorShaderClass* m_ColorShader;
		TextureShaderClass* m_TextureShader;
		LightShaderClass* m_LightShader;
		RefractionShaderClass* m_RefractionShader;
		WaterShaderClass* m_WaterShader;
		LightingClass* m_Light;
		DebugWindowClass* m_DebugWindow;
		RenderTextureClass *m_RefractionTexture, *m_ReflectionTexture;
		ModelClass* m_FloorModel;
		ReflectionShaderClass* m_ReflectionShader;
		FireShaderClass* m_FireShader;
		InputClass* m_Input;

		float m_waterHeight, m_waterTranslation;
		float m_wallXTranslation, m_ballXTranslation, m_ballZTranslation;
		float m_waterIntensity;
};

#endif

