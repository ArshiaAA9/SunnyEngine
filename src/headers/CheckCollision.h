#include "Transform.h"
#include "Colliders.h"

CollisionPoints checkCircleCircle(
	const Collider* a, const Transform* ta,
	const Collider* b, const Transform* tb);

CollisionPoints checkCircleRect(
	const Collider* a, const Transform* ta,
	const Collider* b, const Transform* tb);

CollisionPoints checkRectRect(
	const Collider* a, const Transform* ta,
	const Collider* b, const Transform* tb);
