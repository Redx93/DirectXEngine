#ifndef MESH_H
#define MESH_H

#include "Lib/Transform.h"
#include "Lib/VertexBuffer.h"
#include "Lib/LoadObj.h"
#include "Lib/ConstantBuffer.h"
#include "DirectXHelp.h"
class Mesh:public Transform,public LoadObj
{
private:
	ID3D11Device *device = nullptr;
	ID3D11DeviceContext * deviceContext = nullptr;
	ConstantBuffer<Matrices> MatricesBuffer;
public:
	bool InitializeObject(ID3D11Device *device, ID3D11DeviceContext *deviceContext,
		string file);
	void draw();

	~Mesh();
};


#endif 