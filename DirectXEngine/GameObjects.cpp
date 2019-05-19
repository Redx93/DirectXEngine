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
			cube.setPosition(4.f, 0.0f,0);
			meshes.push_back(cube);

		}
	}


	return true;
}

GameObjects::~GameObjects()
{
	device = nullptr;
	deviceContext = nullptr;
	meshes.clear();
}


