#ifndef HELPER_H
#define HELPER_H
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include <DirectXMath.h>
#include <vector>
#include <wrl/client.h>
using namespace DirectX;
using Microsoft::WRL::ComPtr;//screen aspect

#define WIDTH  800
#define HEIGHT  600

struct LightPixelShader {
	float lightType;//4 nu 16
	XMFLOAT3 AmbientColor;
	float AmbientLight;
	XMFLOAT3 LightColor;
	float Strength;
	XMFLOAT3 position;
};
struct LIGHT {
	LightPixelShader Light[2];
};

struct PerFrameMatrices
{
	XMMATRIX view;
	XMMATRIX projection;
	XMFLOAT3 camPos;
	float padding;//4 nu 16
};

struct Matrices {
	XMMATRIX world;
};
struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT2 TextCoord;
	//XMFLOAT3 Color;
};
enum LightType
{
	POINTLIGHT,
	SPOTLIGHT
};

//
//class Box
//{
//public:
//	Box();
//	Box(float x, float y, float z, float w, float h, float d = 10);
//	void CalculatePoints();
//	XMFLOAT3 calculateDist(XMFLOAT3 p2, XMFLOAT3 p1);
//	void maxValue(XMFLOAT3& p1, XMFLOAT3& p2, XMFLOAT3& vmax);
//	void minValue(XMFLOAT3& p1, XMFLOAT3& p2, XMFLOAT3& vmin);
//	XMFLOAT3 diagonals[4];
//public:
//	float x;
//	float y;
//	float z;
//	float w;
//	float h;
//	float d;
//	XMFLOAT3 vmax = XMFLOAT3(0, 0, 0);
//	XMFLOAT3 vmin = XMFLOAT3(0, 0, 0);;
//};
//
//class FrustumCuller
//{
//public:
//
//	DirectX::XMMATRIX m_View;
//	DirectX::XMMATRIX m_Projection;
//
//	DirectX::XMFLOAT4 mPlane[6];
//public:
//	FrustumCuller(XMMATRIX viewMat, XMMATRIX projection);
//	~FrustumCuller();
//	float dot(XMFLOAT4 plane, XMFLOAT4 box);
//	void CalculateFrustumPlanes(const XMMATRIX& viewMat, XMMATRIX& projMat, XMFLOAT4 outPlanes[6]);
//};
//


#endif // !HELPER_H