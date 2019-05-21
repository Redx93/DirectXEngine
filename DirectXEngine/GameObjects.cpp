#include "GameObjects.h"


bool GameObjects::InitializeGameObjects(ID3D11Device* device, ID3D11DeviceContext * deviceContext)
{
	//this->data = data;
	this->device = device;
	this->deviceContext = deviceContext;

	//for (int i = 0; i < 1; i++)
	//{
	//	for (int j = 0; j <6; j++)
	//	{
	//		Mesh cube;
	//		//cube.InitializeObject(device, deviceContext, "ObjFiles/cube.obj");
	//		cube.InitializeObject(device, deviceContext, "ObjFiles/cube.obj");
	//		cube.setScale(2, 2, 2);
	//		cube.setPosition(4.f + j*2, 0.0f,0);
	//		meshes.push_back(cube);

	//	}
	//}

	Mesh cube;
	//cube.InitializeObject(device, deviceContext, "ObjFiles/cube.obj");
	cube.InitializeObject(device, deviceContext, "ObjFiles/boat.obj");
	cube.setScale(2, 2, 2);
	cube.setPosition(0.0f, 0.0f, 0.0);
	meshes.push_back(cube);
	Mesh cube1;
	//cube.InitializeObject(device, deviceContext, "ObjFiles/cube.obj");
	cube1.InitializeObject(device, deviceContext, "ObjFiles/earth.obj");
	cube1.setScale(2, 2, 2);
	cube1.setPosition(3.0f, 0.0f, 1.0);
	meshes.push_back(cube1);

	Mesh cube2;
	//cube.InitializeObject(device, deviceContext, "ObjFiles/cube.obj");
	cube2.InitializeObject(device, deviceContext, "ObjFiles/cube.obj");
	cube2.setScale(2, 2, 2);
	cube2.setPosition(5.0f, 0.0f, 2.0);
	meshes.push_back(cube2);

	Mesh cube3;
	//cube.InitializeObject(device, deviceContext, "ObjFiles/cube.obj");
	cube3.InitializeObject(device, deviceContext, "ObjFiles/earth.obj");
	cube3.setScale(2, 2, 2);
	cube3.setPosition(7.0f,0.0f, 3.0);
	meshes.push_back(cube3);

	Mesh cube4;
	//cube.InitializeObject(device, deviceContext, "ObjFiles/cube.obj");
	cube4.InitializeObject(device, deviceContext, "ObjFiles/earth.obj");
	cube4.setScale(2, 2, 2);
	cube4.setPosition(10.0f, 0.0f, 4.0);
	meshes.push_back(cube4);
	return true;
}

GameObjects::~GameObjects()
{
	device = nullptr;
	deviceContext = nullptr;
	meshes.clear();
}


