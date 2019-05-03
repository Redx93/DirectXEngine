#ifndef QUADTREEE_H
#define QUADTREEE_H
#include "Lib/Node.h"
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Mesh.h"
#include "Lib/VertexBuffer.h"
using namespace DirectX;
struct Vertex2
{
	XMFLOAT3 position;
	XMFLOAT3 color;

};
class Box
{

public:
	Box();
	~Box(){}
	Box(float x, float y, float z, float w, float h, float d = 10);
	void set(ID3D11DeviceContext * deviceContext,ID3D11Device * device);
	void CalculatePoints();
	XMFLOAT3 calculateDist(XMFLOAT3 p2, XMFLOAT3 p1);
	void maxValue(XMFLOAT3& p1, XMFLOAT3& p2, XMFLOAT3& vmax);
	void minValue(XMFLOAT3& p1, XMFLOAT3& p2, XMFLOAT3& vmin);
	XMFLOAT3 diagonals[4];
public:
	int numberOfdraw = 0;
	void draw(Mesh m, XMMATRIX view, XMMATRIX projection, XMFLOAT3 camPos, ConstantBuffer<PerFrameMatrices> constantBuffer);
	//draw square;
	void draw();
	float x;
	float y;
	float z;
	float w;
	float h;
	float d;
	XMFLOAT3 vmax = XMFLOAT3(0, 0, 0);
	XMFLOAT3 vmin = XMFLOAT3(0, 0, 0);;

};

class FrustumCuller
{
public:

	DirectX::XMMATRIX m_View;
	DirectX::XMMATRIX m_Projection;

	DirectX::XMFLOAT4 mPlane[6];
public:
	int numberOfdraw;
	FrustumCuller();
	FrustumCuller(XMMATRIX viewMat, XMMATRIX projection);
	~FrustumCuller();
	void draw(Mesh m,XMMATRIX view, XMMATRIX projection, XMFLOAT3 camPos, ConstantBuffer<PerFrameMatrices> constantBuffer);
	float dot(XMFLOAT4 plane, XMFLOAT4 box);
	void CalculateFrustumPlanes(const XMMATRIX& viewMat, XMMATRIX& projMat, XMFLOAT4 outPlanes[6]);
};

class Elements
{
public:
	Elements() {}
	Elements(float x, float y) { this->x = x; this->y = y; }
	float x = 0;
	float y = 0;
	Mesh mesh;
};
class QuadTree
{
private:
	Box boundary;
	bool subdivided = false;

	QuadTree *TopLeft = nullptr;
	QuadTree *TopRight = nullptr;
	QuadTree *BottomLeft = nullptr;
	QuadTree *BottomRight = nullptr;

	List<Elements> data; //max 2;
	const int Capacity = 2;
public:
	QuadTree(Box boundary) {this->boundary = boundary;depth = 0;}
	~QuadTree();
	int depth;
	bool Insert(Elements &Node, QuadTree *children, ID3D11Device * d, ID3D11DeviceContext * dc);
	//for point
	bool Search(Elements *node, QuadTree* current);
	//for frustum
	bool Search(FrustumCuller *node, QuadTree* current,
		XMMATRIX view, XMMATRIX projection,
		XMFLOAT3 camPos, ConstantBuffer<PerFrameMatrices> constantBuffer, 
		ID3D11Device * device, ID3D11DeviceContext * deviceContext);
	bool Search(Box *node, QuadTree* current,
		XMMATRIX view, XMMATRIX projection,
		XMFLOAT3 camPos, ConstantBuffer<PerFrameMatrices> constantBuffer);
	bool removed(QuadTree* current);
private:
	//check for contain point
	bool contains(Elements &Node, QuadTree* node);
	//check for contain frustum;
	bool contains(FrustumCuller &f, QuadTree* node);
	//check for box
	bool contains(Box &f, QuadTree* node);

	bool contains(Elements &Node);
	bool subdivide(QuadTree* parent);
	bool storeData(QuadTree *parent);
	bool storePoint(QuadTree *parent, Elements node);

	//frustum
};


#endif // !QUADTREEE_H
