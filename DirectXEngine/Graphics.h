#ifndef Graphics_H
#define Graphics_H


#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include "Input/Camera.h"
#include "GameObjects.h"
#include "Lib/Shaders.h"

//Colours
static const float cyan[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
static const float magenta[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
static const float yellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
static const float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
static const float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

struct BufferDisplay {
	float display;
	XMFLOAT3 padding;
};

struct RenderTarget {
	ID3D11Texture2D* textureTarget = nullptr;
	ID3D11RenderTargetView* renderTarget = nullptr;
	ID3D11ShaderResourceView* shaderResource = nullptr;
};
const UINT BUFFERS = 3;

class Graphics
{
public:
	bool Initialize(HWND hwnd, int width, int height);
	void RenderFrame(float dt);
	~Graphics();

	XMFLOAT3 LookAtPos = XMFLOAT3(0.0f, -1.0f, 0.0f);
	Camera camera;
	//Deferred Render Functions
	void FirstRender();
	void LastRender();
	void DrawPass();

	bool InitializeGraphicsBuffer();
	void DestroyGraphicsBuffer();
	void InitializeScreenQuad();

	bool RenderBackToFront(GameObjects* o);
	float LengthFromCamera(XMFLOAT3 p);
	XMFLOAT3 DirectionLength(XMFLOAT3 v, XMFLOAT3 v2) { return XMFLOAT3(v.x - v2.x, v.y - v2.y, v.z - v2.z); }
	float magnitude(XMFLOAT3 v) { return  std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }
private:
	void updateImguie(float dt);
	GameObjects objects;

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;

	ConstantBuffer<LIGHT> LightBuffer;
	ConstantBuffer<PerFrameMatrices> constantBuffer;
private:
	bool InitializeDirectX(HWND hwmd, int width, int height);
	bool InitializeShaders();
	bool InitializeScene();

	//ID3D11Device* device; //create buffers
	//ID3D11DeviceContext* deviceContext; //set diffrent resources to renderting
	//we set them to diffrent textures
	IDXGISwapChain* swapchain; //swap out our frames when we render it, 
	 ID3D11RenderTargetView* renderTargetView; // for our window

	ID3D11RasterizerState* rasterizerState;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilView* depthStencilView;
	//om både befinner sig på samma zeta ifrån kammran vill man se den röda trianglen istället för gröna i exemplet
	//ID3D11DepthStencilState* depthStencilState;

	//sampler state for texturing
	ID3D11SamplerState*samplerState;

	//Deferred Render
	RenderTarget renderBuffers[BUFFERS];
	ID3D11DepthStencilView* renderDepthStencil = nullptr;
	//Screen-quad for last pass
	ID3D11Buffer* sqVerticesBuffer;
	ID3D11Buffer* sqIndicesBuffer;
	UINT sqIndicesCountForBuffer;

	int FrontTobackMeshDraw;
	int deferredBufferDisplay;
	ConstantBuffer<BufferDisplay> bufferDisplayBuffer;

	//Deferred Render Shaders
	Shader lastPassShaders;
	Shader deferredShaders;
};
#endif // !OBJMODEL_H
