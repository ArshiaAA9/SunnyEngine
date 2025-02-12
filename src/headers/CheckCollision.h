#include "Transform.h"
#include "Colliders.h"

CollisionPoints Test_Sphere_Sphere(
	const Collider* a, const Transform* ta,
	const Collider* b, const Transform* tb);

CollisionPoints Test_Sphere_Plane(
	const Collider* a, const Transform* ta,
	const Collider* b, const Transform* tb);