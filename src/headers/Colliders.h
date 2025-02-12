

enum ColliderType {
	SPHERE,
	PLANE
};

struct Collider {
	ColliderType Type;
};

struct SphereCollider : Collider {
	Vector2 Center;
	float Radius;
};

struct PlaneCollider : Collider {
	Vector2 Normal;
	float Distance;
};