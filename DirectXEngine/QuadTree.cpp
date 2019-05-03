#include "QuadTree.h"
#include <iostream>
QuadTree::~QuadTree()
{
	this->TopLeft = nullptr;
	this->TopRight = nullptr;
	this->BottomLeft = nullptr;
	this->BottomRight = nullptr;
	while (this->data.length() > 0) {
		this->data.removeAt(0);
	}
}
bool QuadTree::Insert(Elements& point, QuadTree *children, ID3D11Device * d, ID3D11DeviceContext * dc)
{

	if (children == nullptr) {
		return false;
	}
	if (!children->contains(point, children))
		return false;
	if (dc != nullptr && d != nullptr) {
		children->boundary.set(dc, d);
	}
	//check if capacity < 2 && !subdivided , then its inside this tree
	if (children->data.length() < children->Capacity && !children->subdivided) {
		children->data.insertAt(0, point);
		return true;
	}

	if (children->data.length() >= children->Capacity && !children->subdivided)
	{
		depth++;
		this->subdivide(children);
		std::cout << "Rezie the QuadTree" << std::endl;
		//transfer data to children
		if (this->storeData(children)) {
			std::cout << "Store the data" << std::endl;
		}

		//lastely store the point into one of the children
		if (this->storePoint(children->TopLeft, point)) {
			std::cout << "Node : (" << point.x << "," << point.y << ")" << "is in TopLeft Side" << std::endl;
		}
		else if (this->storePoint(children->TopRight, point)) {
			std::cout << "Node : (" << point.x << "," << point.y << ")" << "is in TopRight Side" << std::endl;
		}
		else  if (this->storePoint(children->BottomLeft, point)) {
			std::cout << "Node : (" << point.x << "," << point.y << ")" << "is in BottomLeft Side" << std::endl;
		}
		else  if (this->storePoint(children->BottomRight, point)) {
			std::cout << "Node : (" << point.x << "," << point.y << ")" << "is in BottomRight Side" << std::endl;
		}
		return true;
	}

	//now check children if they are not nullptr;

	if (Insert(point, children->TopLeft,d,dc)) {
		return true;
	}
	else if (Insert(point, children->TopRight,d,dc)) {
		return true;
	}
	else if (Insert(point, children->BottomLeft,d,dc)) {
		return true;
	}
	else if (Insert(point, children->BottomRight,d,dc)) {
		return true;
	}
	return true;
}
bool QuadTree::contains(Elements & point, QuadTree *node)
{
	if (node == nullptr) {
		return false;
	}

	float x = node->boundary.x;
	float y = node->boundary.y;
	float w = node->boundary.w;
	float h = node->boundary.h;

	float x1 = x;
	float y1 = y;
	float x2 = x + w;
	float y2 = y + h;

	bool inside = false;


	if (point.x >= x1 && point.x <= x2 && point.y >= y1 && point.y <= y2) {
		inside = true;
	}
	return inside;
}
bool QuadTree::contains(FrustumCuller &fru, QuadTree * n)
{
	if (n == nullptr)
		return false;
	// check box outside/inside of frustum
	XMFLOAT3 mMin = n->boundary.vmin;
	XMFLOAT3 mMax = n->boundary.vmax;
	float x = n->boundary.x;
	float y = n->boundary.y;
	float z = n->boundary.z;
	float w = n->boundary.w;
	XMFLOAT3 pos = XMFLOAT3(x, y, z);
	//for (int i = 0; i < 6; i++)
	//{
	//	int out = 0;
	//	out += ((fru.dot(fru.mPlane[i], XMFLOAT4(mMin.x, mMin.z, mMin.y, 1.0f)) < 0.0) ? 1 : 0);
	//	out += ((fru.dot(fru.mPlane[i], XMFLOAT4(mMax.x, mMin.z, mMin.y, 1.0f)) < 0.0) ? 1 : 0);
	//	out += ((fru.dot(fru.mPlane[i], XMFLOAT4(mMin.x, mMax.z, mMin.y, 1.0f)) < 0.0) ? 1 : 0);
	//	out += ((fru.dot(fru.mPlane[i], XMFLOAT4(mMax.x, mMax.z, mMin.y, 1.0f)) < 0.0) ? 1 : 0);
	//	out += ((fru.dot(fru.mPlane[i], XMFLOAT4(mMin.x, mMin.z, mMax.y, 1.0f)) < 0.0) ? 1 : 0);
	//	out += ((fru.dot(fru.mPlane[i], XMFLOAT4(mMax.x, mMin.z, mMax.y, 1.0f)) < 0.0) ? 1 : 0);
	//	out += ((fru.dot(fru.mPlane[i], XMFLOAT4(mMin.x, mMax.z, mMax.y, 1.0f)) < 0.0) ? 1 : 0);
	//	out += ((fru.dot(fru.mPlane[i], XMFLOAT4(mMax.x, mMax.z, mMax.y, 1.0f)) < 0.0) ? 1 : 0);
	//	if (out == 8) return false;
	//}
	//// check frustum outside/inside box
	//int out;
	//out = 0; for (int i = 0; i < 8; i++) out += ((fru.mPlane[i].x > mMax.x) ? 1 : 0); if (out == 8) return false;
	//out = 0; for (int i = 0; i < 8; i++) out += ((fru.mPlane[i].x < mMin.x) ? 1 : 0); if (out == 8) return false;
	//out = 0; for (int i = 0; i < 8; i++) out += ((fru.mPlane[i].z > mMax.z) ? 1 : 0); if (out == 8) return false;
	//out = 0; for (int i = 0; i < 8; i++) out += ((fru.mPlane[i].z < mMin.z) ? 1 : 0); if (out == 8) return false;
	//out = 0; for (int i = 0; i < 8; i++) out += ((fru.mPlane[i].y > mMax.y) ? 1 : 0); if (out == 8) return false;
	//out = 0; for (int i = 0; i < 8; i++) out += ((fru.mPlane[i].y < mMin.y) ? 1 : 0); if (out == 8) return false;
	//std::string text = "";
	//text += "Intersect with --> " + n->name;
	//std::cout << text << std::endl;
	bool res = true;
	//test all 6 frustum planes
	for (int i = 0; i < 6; i++)
	{
		XMFLOAT4 plane = fru.mPlane[i];
		//calculate distance from sphere center to plane.
		//if distance larger then sphere radius - sphere is outside frustum
		if (plane.x * pos.x + plane.y * pos.y + plane.z * pos.z + plane.w <= -w)
			res = false;
		//return false; //with flag works faster
	}
	return res;
}
bool QuadTree::contains(Box & b, QuadTree * n)
{
	if (n == nullptr)
		return false;
	// check box outside/inside of frustum

	XMFLOAT3 mMin = n->boundary.vmin;
	XMFLOAT3 mMax = n->boundary.vmax;

	if (
		(mMin.x <= b.vmax.x) && (mMax.x >= b.vmin.x) &&
		(mMin.y <= b.vmax.y) && (mMax.y >= b.vmin.y) &&
		(mMin.z <= b.vmax.z) && (mMax.z >= b.vmin.z)) {
	//	std::cout << "\n Intersect with --> " << n->name << std::endl;
		return true;
	}
	return false;
}
bool QuadTree::contains(Elements & point)
{
	float x = boundary.x;
	float y = boundary.y;
	float w = boundary.w;
	float h = boundary.h;

	if (
		point.x >= x - w &&
		point.x <= x + w &&
		point.y >= y - h &&
		point.y <= y + h)
	{

		std::cout << "contains" << std::endl;
		return true;
	}
	return false;
}

bool QuadTree::subdivide(QuadTree* parent)
{
	float x = parent->boundary.x;
	float y = parent->boundary.y;
	float z = parent->boundary.z;
	float w = parent->boundary.w;
	float h = parent->boundary.h;
	float d = parent->boundary.d;
	parent->subdivided = true;

	Box TR(x + w / 2, y + h / 2, z, w / 2, h / 2);
	parent->TopRight = new QuadTree(TR);

	Box TL(x, y + h / 2, z, w / 2, h / 2);
	parent->TopLeft = new QuadTree(TL);

	Box BR(x + w / 2, y, z, w / 2, h / 2);
	parent->BottomRight = new QuadTree(BR);

	Box BL(x, y, z, w / 2, h / 2);
	parent->BottomLeft = new QuadTree(BL);

	return parent->subdivided;
}

bool QuadTree::storeData(QuadTree *parent)
{

	//the parent should not hold the data
	//givee it to the children (ne, nw, se, sw)
	for (int i = 0; i < parent->data.length(); i++)
	{
		Elements point = parent->data.getAt(i);

		if (parent->TopLeft->contains(point, parent->TopLeft)) {
			parent->TopLeft->data.insertAt(0, point);
			std::cout << "Node : (" << point.x << "," << point.y << ")" << "is in TopLeft Side" << std::endl;
		}
		else if (parent->TopRight->contains(point, parent->TopRight)) {
			parent->TopRight->data.insertAt(0, point);
			std::cout << "Node : (" << point.x << "," << point.y << ")" << "is in TopRight Side" << std::endl;
		}
		else if (parent->BottomLeft->contains(point, parent->BottomLeft)) {
			parent->BottomLeft->data.insertAt(0, point);
			std::cout << "Node : (" << point.x << "," << point.y << "," << ")" << "is in BottomLeft Side" << std::endl;
		}
		else if (parent->BottomRight->contains(point, parent->BottomRight)) {
			parent->BottomRight->data.insertAt(0, point);
			std::cout << "Node : (" << point.x << "," << point.y << ")" << "is in BottomRight Side" << std::endl;
		}
	}
	while (parent->data.length() > 0)
	{
		parent->data.removeAt(0);
	}
	return false;
}

bool QuadTree::storePoint(QuadTree * parent, Elements node)
{
	if (parent->contains(node, parent)) {
		parent->data.insertAt(0, node);
		return true;
	}
	return false;
}

bool QuadTree::Search(Elements * element, QuadTree* current)
{

	//Preorder(Root, Left, Right)
	if (current == nullptr) {
		return false;
	}
	if (!current->contains(*element, current))
		return false;

	//check if we got no children so we can draw;
	if (current->data.length() > 0 && current->BottomRight == nullptr) {
		for (int i = 0; i < current->data.length(); i++)
		{
			std::cout << "Point at : (" << current->data.getAt(i).x
				<< "," << current->data.getAt(i).y << ")" << std::endl;
			//eg data->draw();
		}
		std::cout << "NrOfDrawCalls :" << current->data.length() << std::endl;
	}
	//check children 
	if (current->contains(*element, current->TopLeft) && current->TopLeft != nullptr) {
		current->Search(element, current->TopLeft);

	}
	else if (current->TopRight->contains(*element, current->TopRight) && current->TopRight != nullptr) {
		current->Search(element, current->TopRight);
	}
	else if (current->BottomLeft->contains(*element, current->BottomLeft) && current->BottomLeft != nullptr) {
		current->Search(element, current->BottomLeft);
	}

	else if (current->BottomRight->contains(*element, current->BottomRight) && current->BottomRight != nullptr) {
		current->Search(element, current->BottomRight);
	}
	return true;
}

bool QuadTree::Search(FrustumCuller * element, QuadTree * current,
	XMMATRIX v, XMMATRIX p, XMFLOAT3 cam, ConstantBuffer<PerFrameMatrices> cb, ID3D11Device * d, ID3D11DeviceContext * dc)
{
	//Preorder(Root, Left, Right)
	if (current == nullptr) {
		return false;
	}
	if (!current->contains(*element, current))
		return false;
	if (dc != nullptr && d != nullptr &&current->contains(*element, current->TopLeft)) {

		//current->boundary.draw();
	}
	//check if we got no children so we can draw;
	if (current->data.length() > 0 && current->TopLeft == nullptr) {
		element->numberOfdraw += current->data.length();
		for (int i = 0; i < current->data.length(); i++)
		{
			std::cout << "Point at : (" << current->data.getAt(i).x
				<< "," << current->data.getAt(i).y << ")" << std::endl;

			// data->draw();
			element->draw(current->data.getAt(i).mesh, v, p, cam, cb);
			//current->data.getAt(i).mesh.draw();
		}
		std::cout << "NrOfDrawCalls :" << current->data.length() << std::endl;
	}
	//check children 
	if (current->contains(*element, current->TopLeft) && current->TopLeft != nullptr) {
		current->Search(element, current->TopLeft,v,p,cam,cb,d,dc);

	}
	if (current->TopRight->contains(*element, current->TopRight) && current->TopRight != nullptr) {
		current->Search(element, current->TopRight, v, p, cam, cb,d,dc);
	}
	if (current->BottomLeft->contains(*element, current->BottomLeft) && current->BottomLeft != nullptr) {
		current->Search(element, current->BottomLeft, v, p, cam, cb,d,dc);
	}

	if (current->BottomRight->contains(*element, current->BottomRight) && current->BottomRight != nullptr) {
		current->Search(element, current->BottomRight, v, p, cam, cb,d,dc);
	}
	return true;
}

bool QuadTree::Search(Box * element, QuadTree* current,
	XMMATRIX v, XMMATRIX p,
	XMFLOAT3 cam, ConstantBuffer<PerFrameMatrices> cb)
{
	//Preorder(Root, Left, Right)
	if (current == nullptr) {
		return false;
	}
	if (!current->contains(*element, current))
		return false;

	//check if we got no children so we can draw;
	if (current->data.length() > 0 && current->TopLeft == nullptr) {
		element->numberOfdraw += current->data.length();
		for (int i = 0; i < current->data.length(); i++)
		{
			std::cout << "Point at : (" << current->data.getAt(i).x
				<< "," << current->data.getAt(i).y << ")" << std::endl;

			// data->draw();
			element->draw(current->data.getAt(i).mesh, v, p, cam, cb);
			//current->data.getAt(i).mesh.draw();
		}
		std::cout << "NrOfDrawCalls :" << current->data.length() << std::endl;
	}
	//check children 
	if (current->contains(*element, current->TopLeft) && current->TopLeft != nullptr) {
		current->Search(element, current->TopLeft, v, p, cam, cb);

	}
	if (current->TopRight->contains(*element, current->TopRight) && current->TopRight != nullptr) {
		current->Search(element, current->TopRight, v, p, cam, cb);
	}
	if (current->BottomLeft->contains(*element, current->BottomLeft) && current->BottomLeft != nullptr) {
		current->Search(element, current->BottomLeft, v, p, cam, cb);
	}

	if (current->BottomRight->contains(*element, current->BottomRight) && current->BottomRight != nullptr) {
		current->Search(element, current->BottomRight, v, p, cam, cb);
	}
	return true;

}

bool QuadTree::removed(QuadTree* current)
{
	if (current == nullptr)
		return false;
	if (current->data.length() > 0) {
		
		while (data.length() > 0)
		{
			data.removeAt(0);
		}
		delete current->TopLeft;
		delete current->TopRight;
		delete 	current->BottomRight;
		delete current->BottomLeft;
		current->TopLeft = nullptr;
		current->TopRight = nullptr;
		current->BottomRight = nullptr;
		current->BottomLeft = nullptr;
		delete current;
		current = nullptr;
		return true;
	}
	if (current->TopLeft != nullptr)
		removed(current->TopLeft);
	if (current->TopRight != nullptr)
		removed(current->TopRight);
	if (current->BottomRight != nullptr)
		removed(current->BottomRight);
	if (current->BottomLeft != nullptr)
		removed(current->BottomLeft);		


	return true;
}

///





//
Box::Box()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
	this->h = 0;
	this->d = 2;
	CalculatePoints();
}
Box::Box(float x, float y, float z, float w, float h, float d)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->h = h;
	this->d = d;
	CalculatePoints();
}
void Box::set(ID3D11DeviceContext * deviceContext, ID3D11Device * device)
{
	this->deviceContext = deviceContext;
	this->device = device;
	//if (vertexBuffer.Get() != nullptr) 
	{
		XMFLOAT3 p1 = XMFLOAT3(x, y, z); //red
		XMFLOAT3 p2 = XMFLOAT3(x + w, y + h, z + d);

		XMFLOAT3 p3 = XMFLOAT3(x + w, y, z);//yellow
		XMFLOAT3 p4 = XMFLOAT3(x, y + h, z + d);

		XMFLOAT3 p5 = XMFLOAT3(x, y + h, z);//orange
		XMFLOAT3 p6 = XMFLOAT3(x + w, y - h, z + d);

		XMFLOAT3 p7 = XMFLOAT3(x + w, y + h, z);//blue
		XMFLOAT3 p8 = XMFLOAT3(x, y, z + d);


		Vertex2 v[]{
		XMFLOAT3(x, y + h, z),//v1
		XMFLOAT3(1.0,1.0,1.0),
		XMFLOAT3(x + w,y + h,z),//v2
		XMFLOAT3(1.0,1.0,1.0),
		XMFLOAT3(x,y,z),//v3
		XMFLOAT3(1.0, 1.0, 1.0),
		XMFLOAT3(x + w,y + h,z),//v2
		XMFLOAT3(1.0,1.0,1.0),
		XMFLOAT3(x + w,y,z),//v4
		};

		vertexBuffer.Initialize(device, &v[0], sizeof(*v));
	}
}
void Box::CalculatePoints()
{
	XMFLOAT3 p1 = XMFLOAT3(x, y, z); //red
	XMFLOAT3 p2 = XMFLOAT3(x + w, y + h, z + d);
	diagonals[0] = calculateDist(p2, p1);
	maxValue(p1, p2, vmax);
	minValue(p1, p2, vmin);

	XMFLOAT3 p3 = XMFLOAT3(x + w, y, z);//yellow
	XMFLOAT3 p4 = XMFLOAT3(x, y + h, z + d);
	diagonals[1] = calculateDist(p3, p4);
	maxValue(p3, p4, vmax);
	minValue(p3, p4, vmin);

	XMFLOAT3 p5 = XMFLOAT3(x, y + h, z);//orange
	XMFLOAT3 p6 = XMFLOAT3(x + w, y - h, z + d);
	diagonals[2] = calculateDist(p5, p6);
	maxValue(p5, p6, vmax);
	minValue(p5, p6, vmin);

	XMFLOAT3 p7 = XMFLOAT3(x + w, y + h, z);//blue
	XMFLOAT3 p8 = XMFLOAT3(x, y, z + d);
	diagonals[3] = calculateDist(p7, p8);
	maxValue(p7, p8, vmax);
	minValue(p7, p8, vmin);
}

XMFLOAT3 Box::calculateDist(XMFLOAT3 p2, XMFLOAT3 p1)
{
	return XMFLOAT3(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

void Box::maxValue(XMFLOAT3 & p1, XMFLOAT3 & p2, XMFLOAT3& vmax)
{
	if (p1.x >= vmax.x && p1.y >= vmax.y && p1.z >= vmax.z) {
		vmax = p1;
	}
	if (p2.x >= vmax.x && p2.y >= vmax.y && p2.z >= vmax.z) {
		vmax = p2;
	}
}

void Box::minValue(XMFLOAT3 & p1, XMFLOAT3 & p2, XMFLOAT3 & vmin)
{
	if (p1.x <= vmin.x && p1.y <= vmin.y && p1.z <= vmin.z) {
		vmin = p1;
	}
	if (p2.x <= vmin.x && p2.y <= vmin.y && p2.z <= vmin.z) {
		vmin = p2;
	}
}

void Box::draw(Mesh m, XMMATRIX view, XMMATRIX projection, XMFLOAT3 camPos, ConstantBuffer<PerFrameMatrices> constantBuffer)
{
	m.draw(view, projection, camPos, constantBuffer);
}

void Box::draw()
{
	// Bind the vertex buffer
	UINT stride = sizeof(Vertex2);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	//deviceContext->PSSetShaderResources(0, 1, texture[0].getTextureView());
	//deviceContext->IASetIndexBuffer(indicesbuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	//deviceContext->PSSetSamplers(0, 1, &CubesTexSamplerState);
	deviceContext->Draw(6, 0);
}



FrustumCuller::FrustumCuller()
{
}

FrustumCuller::FrustumCuller(XMMATRIX  view, XMMATRIX  projection)
	: m_View(view)
	, m_Projection(projection)
{
	CalculateFrustumPlanes(view, projection, mPlane);
	numberOfdraw = 0;
}

FrustumCuller::~FrustumCuller()
{
}

void FrustumCuller::draw(Mesh m, XMMATRIX view,XMMATRIX projection,XMFLOAT3 camPos, ConstantBuffer<PerFrameMatrices> constantBuffer)
{
	m.draw(view, projection, camPos, constantBuffer);
}

float FrustumCuller::dot(XMFLOAT4 plane, XMFLOAT4 box)
{
	float angle = acos(sqrt(pow(plane.x, 2) + pow(plane.y, 2) + pow(plane.z, 2))
		* sqrt(pow(box.x, 2) + pow(box.y, 2) + pow(box.z, 2)));
	//if(angle)
	//	//return angle;

	float value = sqrt(pow(plane.x, 2) + pow(plane.y, 2) + pow(plane.z, 2))
		* sqrt(pow(box.x, 2) + pow(box.y, 2) + pow(box.z, 2))*cos(angle);

	return value;
}

void FrustumCuller::CalculateFrustumPlanes(const XMMATRIX & viewMat, XMMATRIX & projMat, XMFLOAT4 outPlanes[6])
{
	XMMATRIX view = viewMat;// XMLoadFloat4x4(&viewMat);
	XMMATRIX proj = projMat;// XMLoadFloat4x4(&projMat);
	XMMATRIX viewprojmat = XMMatrixMultiply(view, proj);

	XMFLOAT4X4 viewproj;
	XMStoreFloat4x4(&viewproj, viewprojmat);

	// Left clipping plane
	outPlanes[0].x = viewproj._14 + viewproj._11;
	outPlanes[0].y = viewproj._24 + viewproj._21;
	outPlanes[0].z = viewproj._34 + viewproj._31;
	outPlanes[0].w = viewproj._44 + viewproj._41;

	// Right clipping plane
	outPlanes[1].x = viewproj._14 - viewproj._11;
	outPlanes[1].y = viewproj._24 - viewproj._21;
	outPlanes[1].z = viewproj._34 - viewproj._31;
	outPlanes[1].w = viewproj._44 - viewproj._41;

	// Top clipping plane
	outPlanes[2].x = viewproj._14 - viewproj._12;
	outPlanes[2].y = viewproj._24 - viewproj._22;
	outPlanes[2].z = viewproj._34 - viewproj._32;
	outPlanes[2].w = viewproj._44 - viewproj._42;

	// Bottom clipping plane
	outPlanes[3].x = viewproj._14 + viewproj._12;
	outPlanes[3].y = viewproj._24 + viewproj._22;
	outPlanes[3].z = viewproj._34 + viewproj._32;
	outPlanes[3].w = viewproj._44 + viewproj._42;

	// Near clipping plane
	outPlanes[4].x = viewproj._13;
	outPlanes[4].y = viewproj._23;
	outPlanes[4].z = viewproj._33;
	outPlanes[4].w = viewproj._43;

	// Far clipping plane
	outPlanes[5].x = viewproj._14 - viewproj._13;
	outPlanes[5].y = viewproj._24 - viewproj._23;
	outPlanes[5].z = viewproj._34 - viewproj._33;
	outPlanes[5].w = viewproj._44 - viewproj._43;

	// Normalize
	for (unsigned i = 0; i < 6; ++i)
	{
		float norm = sqrt(outPlanes[i].x * outPlanes[i].x
			+ outPlanes[i].y * outPlanes[i].y
			+ outPlanes[i].z * outPlanes[i].z);

		outPlanes[i].x /= norm;
		outPlanes[i].y /= norm;
		outPlanes[i].z /= norm;
		outPlanes[i].w /= norm;
	}
}
