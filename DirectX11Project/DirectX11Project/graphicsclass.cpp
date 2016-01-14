////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Input = 0;
	m_Light = 0;
	//Models
	m_FireModel = 0;
	m_GroundModel = 0;
	m_WallModel = 0;
	m_BathModel = 0;
	m_WaterModel = 0;
	m_BallModel = 0;
	m_FirePlaceModel = 0;
	m_SkyboxModel = 0;
	//Textures
	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
	//Shaders
	m_LightShader = 0;
	m_RefractionShader = 0;
	m_WaterShader = 0;
	m_FireShader = 0;

}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	m_Input->Initialize();

	m_GroundModel = new ModelClass;
	if (!m_GroundModel)
	{
		return false;
	}

	result = m_GroundModel->Initialize(m_D3D->GetDevice(), L"../DirectX11Project/data/wall01.dds", "../DirectX11Project/data/ground.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the ground model object.", L"Error", MB_OK);
		return false;
	}

	m_WallModel = new ModelClass;
	if (!m_WallModel)
	{
		return false;
	}

	result = m_WallModel->Initialize(m_D3D->GetDevice(), L"../DirectX11Project/data/wall01.dds", "../DirectX11Project/data/wall.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the wall model object.", L"Error", MB_OK);
		return false;
	}

	m_BathModel = new ModelClass;
	if (!m_BathModel)
	{
		return false;
	}

	result = m_BathModel->Initialize(m_D3D->GetDevice(), L"../DirectX11Project/data/pool_large.dds", "../DirectX11Project/data/bath.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bath model object.", L"Error", MB_OK);
		return false;
	}

	m_WaterModel = new ModelClass;
	if (!m_WaterModel)
	{
		return false;
	}

	result = m_WaterModel->Initialize(m_D3D->GetDevice(), L"../DirectX11Project/data/water02.dds", "../DirectX11Project/data/water.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water model object.", L"Error", MB_OK);
		return false;
	}

	m_BallModel = new ModelClass;
	if (!m_BallModel)
	{
		return false;
	}

	result = m_BallModel->Initialize(m_D3D->GetDevice(), L"../DirectX11Project/data/basketball01.dds", "../DirectX11Project/data/sphere.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water model object.", L"Error", MB_OK);
		return false;
	}

	m_FirePlaceModel = new ModelClass;
	if(!m_FirePlaceModel) 
	{
		return false;
	}

	result = m_FirePlaceModel->Initialize(m_D3D->GetDevice(), L"../DirectX11Project/data/rock01.dds", "../DirectX11Project/data/fire_place.txt");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the water model object.", L"Error", MB_OK);
		return false;
	}

	m_SkyboxModel = new ModelClass;
	if (!m_SkyboxModel)
	{
		return false;
	}

	result = m_SkyboxModel->Initialize(m_D3D->GetDevice(), L"../DirectX11Project/data/rock01.dds", "../DirectX11Project/data/inverted_sphere.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightingClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, -1.0f, 0.5f);

	// Create the refraction render to texture object.
	m_RefractionTexture = new RenderTextureClass;
	if (!m_RefractionTexture)
	{
		return false;
	}

	// Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection render to texture object.
	m_ReflectionTexture = new RenderTextureClass;
	if (!m_ReflectionTexture)
	{
		return false;
	}

	// Initialize the reflection render to texture object.
	result = m_ReflectionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the refraction shader object.
	m_RefractionShader = new RefractionShaderClass;
	if (!m_RefractionShader)
	{
		return false;
	}

	// Initialize the refraction shader object.
	result = m_RefractionShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the water shader object.
	m_WaterShader = new WaterShaderClass;
	if (!m_WaterShader)
	{
		return false;
	}

	// Initialize the water shader object.
	result = m_WaterShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the fire shader object.
	m_FireShader = new FireShaderClass;
	if (!m_FireShader)
	{
		return false;
	}

	// Initialize the fire shader object.
	result = m_FireShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire shader object.", L"Error", MB_OK);
		return false;
	}

	// Set the height of the water.
	m_waterHeight = 2.75f;

	// Initialize the position of the water.
	m_waterTranslation = 0.0f;

	// Initalize the water intensity
	m_waterIntensity = 0.01f;

	return true;
}


void GraphicsClass::Shutdown()
{
	if (m_WaterShader)
	{
		m_WaterShader->Shutdown();
		delete m_WaterShader;
		m_WaterShader = 0;
	}

	if (m_RefractionShader)
	{
		m_RefractionShader->Shutdown();
		delete m_RefractionShader;
		m_RefractionShader = 0;
	}

	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	if (m_FireShader)
	{
		m_FireShader->Shutdown();
		delete m_FireShader;
		m_FireShader = 0;
	}

	if (m_BallModel)
	{
		m_BallModel->Shutdown();
		delete m_BallModel;
		m_BallModel = 0;
	}

	if(m_FirePlaceModel)
	{
		m_FirePlaceModel->Shutdown();
		delete m_FirePlaceModel;
		m_FirePlaceModel = 0;
	}

	if (m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	if (m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}

	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if (m_WaterModel)
	{
		m_WaterModel->Shutdown();
		delete m_WaterModel;
		m_WaterModel = 0;
	}

	if (m_BathModel)
	{
		m_BathModel->Shutdown();
		delete m_BathModel;
		m_BathModel = 0;
	}

	if (m_WallModel)
	{
		m_WallModel->Shutdown();
		delete m_WallModel;
		m_WallModel = 0;
	}

	if (m_GroundModel)
	{
		m_GroundModel->Shutdown();
		delete m_GroundModel;
		m_GroundModel = 0;
	}
	
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

void GraphicsClass::MoveWallLeft()
{
	m_wallXTranslation -= 0.025f;
	m_ballXTranslation -= 0.025f;
	
	return;
}

void GraphicsClass::MoveWallRight()
{
	m_wallXTranslation += 0.025f;
	m_ballXTranslation += 0.025f;
	return;
}

void GraphicsClass::MoveBallForward()
{
	m_ballZTranslation += 0.025f;

	return;
}

void GraphicsClass::MoveBallBackwards()
{
	m_ballZTranslation -= 0.025f;

	return;
}

void GraphicsClass::IncreaseWaterIntensity()
{
	if (m_waterIntensity >= 0.1f) return;
	m_waterIntensity += 0.001f;

	return;
}

void GraphicsClass::DecreaseWaterIntensity()
{
	if (m_waterIntensity <= 0.0f) return;
	m_waterIntensity -= 0.001f;
	
	return;
}

bool GraphicsClass::Frame()
{
	// Update the position of the water to simulate motion.
	m_waterTranslation += 0.001f;
	if (m_waterTranslation > 1.0f)
	{
		m_waterTranslation -= 1.0f;
	}

	// Set the position and rotation of the camera.
	m_Camera->SetPosition(10.0f, 6.0f, -10.0f);
	m_Camera->SetRotation(0.0f, -45.0f, 0.0f);

	return true;
}


bool GraphicsClass::Render()
{
	bool result;

	
	// Render the refraction of the scene to a texture.
	result = RenderRefractionToTexture();
	if (!result)
	{
		return false;
	}

	// Render the reflection of the scene to a texture.
	result = RenderReflectionToTexture();
	if (!result)
	{
		return false;
	}

	// Render the scene as normal to the back buffer.
	result = RenderScene();
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::RenderRefractionToTexture()
{
	D3DXVECTOR4 clipPlane;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Setup a clipping plane based on the height of the water to clip everything above it.
	clipPlane = D3DXVECTOR4(0.0f, -1.0f, 0.0f, m_waterHeight);

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Translate to where the bath model will be rendered.
	D3DXMatrixTranslation(&worldMatrix, 0.0f, 2.2f, 0.0f);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BathModel->Render(m_D3D->GetDeviceContext());

	// Render the bath model using the light shader.
	result = m_RefractionShader->Render(m_D3D->GetDeviceContext(), m_BathModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_BathModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), clipPlane);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return true;
}


bool GraphicsClass::RenderReflectionToTexture()
{
	D3DXMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix;
	bool result;


	// Set the render target to be the reflection render to texture.
	m_ReflectionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	// Clear the reflection render to texture.
	m_ReflectionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Use the camera to render the reflection and create a reflection view matrix.
	m_Camera->RenderReflection(m_waterHeight);

	// Get the camera reflection view matrix instead of the normal view matrix.
	reflectionViewMatrix = m_Camera->GetReflectionViewMatrix();

	//// Get the world and projection matrices from the d3d object.
	//m_D3D->GetWorldMatrix(worldMatrix);
	//m_D3D->GetProjectionMatrix(projectionMatrix);

	//// Translate to where the wall model will be rendered.
	//D3DXMatrixTranslation(&worldMatrix, m_wallXTranslation, 6.0f, 8.0f);

	//// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_WallModel->Render(m_D3D->GetDeviceContext());

	//// Render the wall model using the light shader and the reflection view matrix.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_WallModel->GetIndexCount(), worldMatrix, reflectionViewMatrix,
	//	projectionMatrix, m_WallModel->GetTexture(), m_Light->GetDirection(),
	//	m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	//if (!result)
	//{
	//	return false;
	//}

	// Get the world and projection matrices from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMATRIX matScale;
	D3DXMATRIX matTranslate;
	D3DXMatrixScaling(&matScale, 0.25f, 0.25f, 0.25f);
	D3DXMatrixTranslation(&matTranslate, m_ballXTranslation, 5.0f, m_ballZTranslation + 6.0f);

	worldMatrix = matScale * matTranslate;

	// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BallModel->Render(m_D3D->GetDeviceContext());

	// Render the wall model using the light shader and the reflection view matrix.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BallModel->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, m_BallModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return true;
}


bool GraphicsClass::RenderScene()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix;
	bool result;
	D3DXVECTOR3 scrollSpeeds, scales;
	D3DXVECTOR2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;
	D3DXVECTOR3 transCoords;
	D3DXMATRIX modelScale;
	D3DXMATRIX modelTranslate;
	D3DXMATRIX modelRotation;

	// Increment the frame time counter.
	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}

	// Set the three scrolling speeds for the three different noise textures.
	scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	distortion3 = D3DXVECTOR2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.5f, 0.5f, 1.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//Render the Floor Model
	transCoords = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	result = RenderModel(m_GroundModel, transCoords, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	////Render the Wall Model
	//transCoords = D3DXVECTOR3(m_wallXTranslation, 6.0f,2 8.0f);
	//result = RenderModel(m_WallModel, transCoords, worldMatrix, viewMatrix, projectionMatrix);
	//if (!result)
	//{
	//	return false;
	//}

	/*transCoords = D3DXVECTOR3(0.0f, 4.0f, 0.0f);
	result = RenderModel(m_FirePlaceModel, transCoords, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}*/

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	D3DXMatrixScaling(&modelScale, 0.25f, 0.25f, 0.25f);
	D3DXMatrixTranslation(&modelTranslate, m_ballXTranslation, 5.0f, m_ballZTranslation + 6.0f);

	worldMatrix = modelScale * modelTranslate;

	// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BallModel->Render(m_D3D->GetDeviceContext());

	// Render the wall model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BallModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_BallModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}


	//Render the Bath Model
	transCoords = D3DXVECTOR3(0.0f, 2.3f, 0.0f);
	result = RenderModel(m_BathModel, transCoords, worldMatrix, viewMatrix, projectionMatrix);
	if(!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the camera reflection view matrix.
	reflectionMatrix = m_Camera->GetReflectionViewMatrix();

	// Translate to where the water model will be rendered.
	D3DXMatrixTranslation(&worldMatrix, 0.0f, m_waterHeight, 0.0f);

	// Put the water model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_WaterModel->Render(m_D3D->GetDeviceContext());

	// Render the water model using the water shader.
	result = m_WaterShader->Render(m_D3D->GetDeviceContext(), m_WaterModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, reflectionMatrix, m_ReflectionTexture->GetShaderResourceView(),
		m_RefractionTexture->GetShaderResourceView(), m_WaterModel->GetTexture(),
		m_waterTranslation, m_waterIntensity);
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderModel(ModelClass* model, D3DXVECTOR3 translationCoord, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
	bool result;

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix); 

	// Translate to where the bath model will be rendered.
	D3DXMatrixTranslation(&worldMatrix, translationCoord.x, translationCoord.y, translationCoord.z);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	model->Render(m_D3D->GetDeviceContext());

	// Render the bath model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, model->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());

	return result;
}