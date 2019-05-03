#include "Geometry.h"

ostream& operator<<(ostream& stream, const Sphere& shape) {
	stream << "position:(" << shape.position.x << ", " << shape.position.y << ", " << shape.position.z << "), " <<
		"radius: " << shape.radius;
	return stream;
}
