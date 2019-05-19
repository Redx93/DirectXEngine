#ifndef GameObjects_H
#define GameObjects_H

#include "Mesh.h"

class GameObjects
{
private:

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	float gIncrement = 0;
public:
	ConstantBuffer<PerFrameMatrices> constantBuffer;

	vector<Mesh> meshes;
	bool InitializeGameObjects(ID3D11Device* device, ID3D11DeviceContext * deviceContext);
	~GameObjects();
};

#endif // !OBJMODEL_H
