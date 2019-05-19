
#ifndef QUADTREECLASS_H
#define QUADTREECLASS_H
#include "Lib/Node.h"
#include "DirectXHelp.h"
#include "Mesh.h"
#include <string>
#include <iostream>

class Box
{
public:
	Box();
	Box(AABB aabb);
	void CalculatePoints();
	XMFLOAT3 calculateDist(XMFLOAT3& p2, XMFLOAT3& p1);
	void maxValue(XMFLOAT3& p1, XMFLOAT3& p2, XMFLOAT3& vmax);
	void minValue(XMFLOAT3& p1, XMFLOAT3& p2, XMFLOAT3& vmin);
	XMFLOAT3 diagonals[4];
public:
	AABB aabb;
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
	FrustumCuller(XMMATRIX viewMat, XMMATRIX projection);
	~FrustumCuller();
	float dot(XMFLOAT4 plane, XMFLOAT4 box);
	void CalculateFrustumPlanes(const XMMATRIX& viewMat, XMMATRIX& projMat, XMFLOAT4 outPlanes[6]);
};


class Elements
{
public:
	Elements() {}
	Elements(Sphere sphere, float r) { this->sphere = sphere; }
	Sphere sphere;
	Mesh* mesh;

};

class QuadTreeClass
{
private:
	struct NodeType
	{
		AABB aabb;
		NodeType* nodes[4] = { nullptr };
		NodeType* parent = nullptr;
		List<Elements> element;
		std::string name;
		int depth = 0;
		bool subdivided = false;
	};
	ID3D11Device * d = nullptr;
	ID3D11DeviceContext * dc = nullptr;
public:
	QuadTreeClass();
	QuadTreeClass(AABB& b, ID3D11Device * d, ID3D11DeviceContext * dc, int Depth = 10);
	~QuadTreeClass();

	bool Insert(Elements& e);
	void Render(FrustumCuller&f);

	bool ClearQuadTree(NodeType *n);
	int GetDrawCount() { return this->numberOfDrawCount; }
	int GetDepth() { return this->currentDepth; }
	NodeType * getParent() { return this->parentNode; }

private:
	bool Render(AABB& b, NodeType* n);
	bool Render(FrustumCuller &f, NodeType* n);
	bool ClearQuadTree();
	bool contain(FrustumCuller &f, NodeType * n, bool child = true); //
	bool contain(AABB &e, NodeType * n, bool child = true); //

	bool Insert(Elements &e, NodeType * n);
	bool contain(Elements &e, NodeType * n);
	bool subdivide(NodeType* n);
	bool storeData(NodeType *n);
	float dot(XMFLOAT3 s, XMFLOAT3 p) { return s.x * p.x + s.y* p.y + s.z + p.z ; }

private:
	const int CAP = 10;
	int numberOfDrawCount = 0;
	int TotalDepth = 0;
	int currentDepth = 0;
	NodeType* parentNode;
};

#endif // !QUADTREECLASS
