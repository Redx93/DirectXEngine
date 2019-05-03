#include "GameObjects.h"


bool GameObjects::InitializeGameObjects(ID3D11Device* device, ID3D11DeviceContext * deviceContext)
{
	//this->data = data;
	this->device = device;
	this->deviceContext = deviceContext;

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j <1; j++)
		{
			Mesh cube;
			//cube.InitializeObject(device, deviceContext, "ObjFiles/cube.obj");
			cube.InitializeObject(device, deviceContext, "ObjFiles/boat.obj");
			cube.setScale(2, 2, 2);
			cube.setPosition(4.f*j, 0.0f, 4.f*i);
			meshes.push_back(cube);

		}
	}


	return true;
}

bool GameObjects::CreatePrimitive(PRIMITIVIES primitivies)
{
	if (primitivies == CUBE) {
		Primitive cube;
		cube.initializeCube(device, deviceContext);
		primitives.push_back(cube);
		
	}//else if
	return true;
}	
float speed = 0.001f;
void GameObjects::render(const XMMATRIX &view, const XMMATRIX &projection, const XMFLOAT3& camPos, float dt)
{

}


GameObjects::~GameObjects()
{
	device = nullptr;
	deviceContext = nullptr;
	meshes.clear();
	primitives.clear();
}


