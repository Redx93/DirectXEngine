#include "PointQuadtree.h"

QuadTreeClass::QuadTreeClass()
{
	AABB aabb;
	aabb.position = Vector3(0,0,0 );
	aabb.size = Vector3(200, 200, 200);
	parentNode = new NodeType;
	parentNode->aabb = aabb;
	parentNode->name = "Root Node";
	this->TotalDepth = 10;
}

QuadTreeClass::QuadTreeClass(AABB& b, ID3D11Device * d,
	ID3D11DeviceContext * dc, int Depth)
{
	this->d = d;
	this->dc = dc;
	parentNode = new NodeType;
	parentNode->aabb = b;
	parentNode->name = "Root Node";
	this->TotalDepth = Depth;
}

QuadTreeClass::~QuadTreeClass()	{	}

bool QuadTreeClass::Insert(Elements& e)
{

	if (!this->contain(e, this->parentNode)) {
		return false;
	}
	Insert(e, parentNode);
	return true;
}

bool QuadTreeClass::ClearQuadTree()
{
	return ClearQuadTree(this->parentNode);
}


void QuadTreeClass::Render(FrustumCuller &f)
{
	if (&f != nullptr) {
		if (contain(f, this->parentNode))
		{
			Render(f, this->parentNode);
		}
	}

}

bool QuadTreeClass::ClearQuadTree(NodeType *n)
{
	if (n == nullptr)
		return false;

	if (n->element.length() > 0) {

		while (n->element.length() > 0)
		{
			n->element.removeAt(0);
		}
		for (int i = 0; i < 4; i++)
		{
			delete n->nodes[i];
		}
		n->nodes[0] = nullptr;
		n->nodes[1] = nullptr;
		n->nodes[2] = nullptr;
		n->nodes[3] = nullptr;

	}
	//efter tagit bort barnen ta bort föräldern

	if (n->nodes[0] != nullptr)
		ClearQuadTree(n->nodes[0]);
	if (n->nodes[1] != nullptr)
		ClearQuadTree(n->nodes[1]);
	if (n->nodes[2] != nullptr)
		ClearQuadTree(n->nodes[2]);
	if (n->nodes[3] != nullptr)
		ClearQuadTree(n->nodes[3]);

	if (n != nullptr) {
		delete n;
		n = nullptr;
	}
	if (parentNode == n && parentNode != nullptr) {
		delete parentNode;
		parentNode = nullptr;
	}
	return true;
}

bool QuadTreeClass::Render(AABB& b, NodeType * n)
{
	if (n == nullptr)
		return false;
	if (!this->contain(b, n, false))
		return false;

	//check children
	if (contain(b, n->nodes[0]))
		Render(b, n->nodes[0]);
	if (contain(b, n->nodes[1]))
		Render(b, n->nodes[1]);
	if (contain(b, n->nodes[2]))
		Render(b, n->nodes[2]);
	if (contain(b, n->nodes[3]))
		Render(b, n->nodes[3]);

	//check if we have any anything in this leafe to draw
	if (n->element.length() > 0) {
		this->numberOfDrawCount += n->element.length();
		//std::cout << n->name << ", there are :" << std::endl;
		for (int i = 0; i < n->element.length(); i++)
		{
			std::cout << "Element " << i + 1 << " at :" << n->element.getAt(i).sphere << std::endl;
		}
	}
	return true;
}

bool QuadTreeClass::Render(FrustumCuller & f, NodeType * n)
{
	if (n == nullptr)
		return false;
	if (!this->contain(f, n, false))
		return false;

	//check children
	if (contain(f, n->nodes[0]))
		Render(f, n->nodes[0]);
	if (contain(f, n->nodes[1]))
		Render(f, n->nodes[1]);
	if (contain(f, n->nodes[2]))
		Render(f, n->nodes[2]);
	if (contain(f, n->nodes[3]))
		Render(f, n->nodes[3]);

	
	//check if we have any anything in this leafe to draw
	if (n->element.length() > 0) {
		this->numberOfDrawCount += n->element.length();
		std::cout << n->name << ", there are :" << std::endl;
		for (int i = 0; i < n->element.length(); i++)
		{
			std::cout << "Element " << i + 1 << " at :" << n->element.getAt(i).sphere << std::endl;
			n->element.getAt(i).mesh->draw();
		}
	}
	return true;
}

bool QuadTreeClass::Insert(Elements& e, NodeType * n)
{
	if (n == nullptr)
		return false;

	if (!this->contain(e, n))
		return false;
	if (n->element.length() >= CAP && !n->subdivided && n->depth < TotalDepth) {
		//subdivde
		this->subdivide(n);
		this->storeData(n);
	}
	if (n->element.length() < CAP && !n->subdivided ) {
		std::cout << "Store Element at :" << n->name << std::endl;
		n->element.insertAt(0, e);

		return true;
	}

	//insert to the children if possible
	Insert(e, n->nodes[0]); //TR
	Insert(e, n->nodes[1]); //TL
	Insert(e, n->nodes[2]);//BR
	Insert(e, n->nodes[3]);//BL

	return true;
}

bool QuadTreeClass::contain(Elements & s, NodeType * n)
{
	if (n == nullptr) {
		return false;
	}
	float x = n->aabb.position.x;
	float y = n->aabb.position.z;
	float w = n->aabb.size.x;
	float h = n->aabb.size.z;
	bool inside = true;
	////elemts är en sphere, quadträdet är en rektangle
	if (s.sphere.position.x - s.sphere.radius >= x + w ||
		s.sphere.position.x + s.sphere.radius <= x ||
		s.sphere.position.z - s.sphere.radius >= y + h ||
		s.sphere.position.z + s.sphere.radius <= y) {
		inside = false;
	}
	return inside;
}

bool QuadTreeClass::contain(FrustumCuller & fru, NodeType * n, bool child)
{
	//if (n == nullptr)
	//	return false;
	//// check box outside/inside of frustum
	//float x = n->boundaries.x;
	//float y = n->boundaries.y;
	//float z = n->boundaries.z;
	//float w = n->boundaries.w;
	//float h = n->boundaries.h;
	//float d = n->boundaries.d;
	////rework for a sphere
	//x = x + w / 2;//center
	//y = y + h / 2;//w and h the same
	//z = z + d / 2;
	//XMFLOAT3 pos = XMFLOAT3(x, y, z);
	//XMFLOAT3 maxs = n->boundaries.vmax;
	//XMFLOAT3 mins = n->boundaries.vmin;
	//bool res = true;
	//int count = 0;
	//// Problemet ligger i att vi testar sphere när vi ska testa box
	//for (int i = 0; i < 6 && res == true; i++)
	//{
	//	XMFLOAT4 plane = fru.mPlane[i];
	//	////calculate distance from sphere center to plane.
	//	////if distance larger then sphere radius - sphere is outside frustum
	//	//float d2 = plane.x * pos.x + plane.y * pos.y + plane.z * pos.z;
	//	////	res = false;
	//	//XMFLOAT3 s = XMFLOAT3(x, y, z);
	//	//XMFLOAT3 p = XMFLOAT3(plane.x, plane.y, plane.z);
	//	//float d = dot(s, p) - plane.w;
	//	//if (d > d2)
	//	//	res = false;

	//	XMFLOAT3 vmin, vmax;
	//	{
	//		// X axis
	//		if (plane.x > 0)
	//		{
	//			vmin.x = mins.x;
	//			vmax.x = maxs.x;
	//		}
	//		else
	//		{
	//			vmin.x = maxs.x;
	//			vmax.x = mins.x;
	//		}
	//		// Y axis
	//		if (plane.y > 0)
	//		{
	//			vmin.y = mins.y;
	//			vmax.y = maxs.y;
	//		}
	//		else
	//		{
	//			vmin.y = maxs.y;
	//			vmax.y = mins.y;
	//		}
	//		// Z axis
	//		if (plane.z > 0)
	//		{
	//			vmin.z = mins.z;
	//			vmax.z = maxs.z;
	//		}
	//		else
	//		{
	//			vmin.z = maxs.z;
	//			vmax.z = mins.z;
	//		}
	//		XMFLOAT3 pTemp;
	//		pTemp = XMFLOAT3(plane.x, plane.y, plane.z);

	//		if (dot(pTemp, vmin) + plane.w > 0) {
	//			res = false;
	//		}
	//		if (dot(pTemp, vmax) + plane.w >= 0)
	//			res = true;
	//	}
	//}
	return true;
}

bool QuadTreeClass::contain(AABB& b, NodeType * n, bool child)
{
	//if (n == nullptr)
	//	return false;

	//float x = n->aabb.position.x;
	//float y = n->aabb.position.y;
	//float w = n->aabb.size.y;
	//float h = n->aabb.size.x;

	//float x2 = x + w;
	//float y2 = y + h;

	//std::string text = "";
	//if ((abs(x - b.position.x) * 2 < (w + b.w)) &&
	//	(abs(y - b.y) * 2 < (h + b.h)))
	//{
	//	if (child == true) {
	//		text += "Intersect with --> " + n->name;
	//		std::cout << text << std::endl;
	//	}
	//	return true;
	//}
	return true;
}

bool QuadTreeClass::subdivide(NodeType * n)
{
	if (!TotalDepth > n->depth) {
		return false;
	}
	n->subdivided = true;
	currentDepth = n->depth + 1;

	float x = n->aabb.position.x;
	float y = n->aabb.position.y;
	float z = n->aabb.position.z;
	float w = n->aabb.size.x;
	float h = n->aabb.size.y;
	float d = n->aabb.size.z;

	//Box TR(x + w / 2, y + h / 2, z, w / 2, h / 2);
	AABB abb(Vector3(x + w / 2, y + h / 2, z), Vector3(w / 2, h / 2, d / 2));
	n->nodes[0] = new NodeType();
	n->nodes[0]->aabb = abb;
	n->nodes[0]->name = "TR";
	//the parent to this node
	n->nodes[0]->parent = n;
	//calculate the depth
	n->nodes[0]->depth = n->depth + 1;

	AABB abb2(Vector3(x , y + h / 2, z), Vector3(w / 2, h / 2, d / 2));
	n->nodes[1] = new NodeType();
	n->nodes[1]->aabb = abb2;
	n->nodes[1]->name = "TL";
	//the parent to this node
	n->nodes[1]->parent = n;
	//calculate the depth
	n->nodes[1]->depth = n->depth + 1;

	AABB abb3(Vector3(x + w / 2, y , z), Vector3(w / 2, h / 2, d / 2));
	n->nodes[2] = new NodeType();
	n->nodes[2]->aabb = abb3;
	n->nodes[2]->name = "BR";
	//the parent to this node
	n->nodes[2]->parent = n;
	//calculate the depth
	n->nodes[2]->depth = n->depth + 1;

	AABB abb4(Vector3(x, y, z), Vector3(w / 2, h / 2, d / 2));
	n->nodes[3] = new NodeType();
	n->nodes[3]->aabb = abb4;
	n->nodes[3]->name = "BL";
	//the parent to this node
	n->nodes[3]->parent = n;
	//calculate the depth
	n->nodes[3]->depth = n->depth + 1;
	return n->subdivided;
}

bool QuadTreeClass::storeData(NodeType * n)
{
	if (n == nullptr)
		return false;
	std::cout << "Subdivide and store " << n->element.length() << " elements from " << n->name << " to :" << std::endl;
	for (int i = 0; i < n->element.length(); i++)
	{
		Elements element = n->element.getAt(i);
		if (contain(element, n->nodes[0])) {
			n->nodes[0]->element.insertAt(0, element);
			//std::cout << "Node : (" << point.x << "," << point.y << ") " << "at TL" << std::endl;
		}
		else if (contain(element, n->nodes[1])) {
			n->nodes[1]->element.insertAt(0, element);
			//std::cout << "Node : (" << point.x << "," << point.y << ") " << "at TR" << std::endl;
		}
		else if (contain(element, n->nodes[2])) {
			n->nodes[2]->element.insertAt(0, element);
			//std::cout << "Node : (" << point.x << "," << point.y << "," << ") " << "at BL" << std::endl;
		}
		else if (contain(element, n->nodes[3])) {
			n->nodes[3]->element.insertAt(0, element);
			//std::cout << "Node : (" << point.x << "," << point.y << ") " << "at BR" << std::endl;
		}
	}
	while (n->element.length() > 0)
	{
		n->element.removeAt(0);
	}
	return false;
}



Box::Box()
{
	AABB aabb(Vector3(0,0,0),Vector3(0,0,0));
	this->aabb = aabb;
	CalculatePoints();
}
Box::Box(AABB aabb)
{
	this->aabb = aabb;
	CalculatePoints();
}
void Box::CalculatePoints()
{
	//float x = aabb.position.x;
	//float y = aabb.position.y;
	//float z = aabb.position.z;

	//XMFLOAT3 p1 = XMFLOAT3(x, y, z); //red
	//XMFLOAT3 p2 = XMFLOAT3(x + w, y + h, z + d);
	//diagonals[0] = calculateDist(p2, p1);
	//maxValue(p1, p2, vmax);
	//minValue(p1, p2, vmin);

	//XMFLOAT3 p3 = XMFLOAT3(x + w, y, z);//yellow
	//XMFLOAT3 p4 = XMFLOAT3(x, y + h, z + d);
	//diagonals[1] = calculateDist(p3, p4);
	//maxValue(p3, p4, vmax);
	//minValue(p3, p4, vmin);

	//XMFLOAT3 p5 = XMFLOAT3(x, y + h, z);//orange
	//XMFLOAT3 p6 = XMFLOAT3(x + w, y - h, z + d);
	//diagonals[2] = calculateDist(p5, p6);
	//maxValue(p5, p6, vmax);
	//minValue(p5, p6, vmin);

	//XMFLOAT3 p7 = XMFLOAT3(x + w, y + h, z);//blue
	//XMFLOAT3 p8 = XMFLOAT3(x, y, z + d);
	//diagonals[3] = calculateDist(p7, p8);
	//maxValue(p7, p8, vmax);
	//minValue(p7, p8, vmin);
}

XMFLOAT3 Box::calculateDist(XMFLOAT3& p2, XMFLOAT3& p1)
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



FrustumCuller::FrustumCuller(XMMATRIX view, XMMATRIX projection)
	: m_View(view)
	, m_Projection(projection)
{
	CalculateFrustumPlanes(view, projection, mPlane);
}

FrustumCuller::~FrustumCuller()
{
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
