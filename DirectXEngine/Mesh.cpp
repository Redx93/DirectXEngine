#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <iomanip>  
#include <sstream>

bool Mesh::InitializeObject(ID3D11Device *device, ID3D11DeviceContext *deviceContext, 
	string file)
{
	this->device = device;
	this->deviceContext = deviceContext;
	Initialize(device, deviceContext, file);
	// function
	//tobinart();
	//this->CreatePrimitive(CUBE);
	if (!MatricesBuffer.Initialize(device))
		return false;


	return true;


}
float gIncrement = 0;
void Mesh::draw()
{
	gIncrement += sin(0.001);
	//setRotation(0.0f, 1.0, 0.0f, gIncrement);
	UINT stride = sizeof(float) * 11;//sizeof(Vertex);
	UINT offset = 0;
	for (int i = 0; i < textures.size(); i++)
	{
		/*if (DIFFUSE == textures[i].getType()) 
			deviceContext->PSSetShaderResources(0, 1, textures[i].getTextureView());	
		else*/
			deviceContext->PSSetShaderResources(0, 1, textures[i].getTextureView());

	}

	MatricesBuffer.data.world = getWorld();
	MatricesBuffer.updateConstantBuffer(deviceContext);
	deviceContext->GSSetConstantBuffers(1, 1, MatricesBuffer.getConstantBuffer());
	
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), vertexBuffer.Stride(), &offset);
	deviceContext->Draw(indices.size(), 0);
	
}

Mesh::~Mesh()
{
	device = nullptr;
	deviceContext =nullptr;
}

//
//bool Mesh::translation(float x, float y, float z)
//{
//	/*transform.Translation = DirectX::XMMatrixTranslation(x, y, z);
//	transform.Translation = DirectX::XMMatrixTranspose(transform.Translation);*/
//	return true;
//}
//
//bool Mesh::Rotations(float r)
//{
//	/*transform.Rotation = DirectX::XMMatrixRotationY(r);
//	transform.Rotation = DirectX::XMMatrixTranspose(transform.Rotation);*/
//	return true;
//}
//
//bool Mesh::ApplayTransform()
//{
//	//world = transform.Translation * transform.Rotation;
//	//world = DirectX::XMMatrixTranspose(world);
//	return true;
//}
//float height =2;
//bool Mesh::TestMove(float dt,float& speed)
//{
//	transform.Position.y = transform.Position.y +speed *dt;
//
//	if (transform.Position.y > height || transform.Position.y < 0 ) {
//		height = height - speed * 0.1;
//		speed =speed*(-1.1);
//	}
//
//	
//	this->world = XMMatrixTranspose(XMMatrixMultiply(XMMatrixScaling(transform.Scale.x, transform.Scale.y, transform.Scale.z),
//		XMMatrixTranslation(transform.Position.x, transform.Position.y, transform.Position.z)));
//	world = DirectX::XMMatrixTranspose(world);
//	return true;
//
//
//
//
//	XMMatrixRotationAxis()
//}
