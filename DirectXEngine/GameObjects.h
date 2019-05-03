#ifndef GameObjects_H
#define GameObjects_H

#include "Mesh.h"
#include "Mesh/Primitive.h"
#include "Lights.h"

class GameObjects
{
private:
	vector<Primitive> primitives;
	//QuadTree qt;
	//vector<Light> light;


	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	float gIncrement = 0;
public:
	ConstantBuffer<PerFrameMatrices> constantBuffer;

	vector<Mesh> meshes;
	//GameObjects();
	bool InitializeGameObjects(ID3D11Device* device, ID3D11DeviceContext * deviceContext);
	bool CreatePrimitive(PRIMITIVIES primitivies);
	void render(const XMMATRIX& view, const XMMATRIX& projection, const XMFLOAT3 &camPos,
		float dt);
	~GameObjects();
};

#endif // !OBJMODEL_H
