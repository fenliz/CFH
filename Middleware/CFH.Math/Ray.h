#pragma once
#include "Common.h"
#include "Vector3.h"

namespace CFH
{
	namespace Math
	{
		struct BoundingBox;
		struct BoundingSphere;
		struct BoundingFrustum;
		struct Plane;

		struct DLL_API Ray final
		{
		public:
			Vector3 Position;
			Vector3 Direction;

			Ray();
			Ray(Vector3 position, Vector3 direction);
			~Ray();

			bool operator==(Ray ray) const;
			bool operator!=(Ray ray) const;

			bool Intersects(BoundingBox boundingBox) const;
			bool Intersects(BoundingBox boundingBox, float& distance) const;
			bool Intersects(BoundingBox boundingBox, Vector3& point) const;
			bool Intersects(BoundingFrustum boundingFrustum) const;
			bool Intersects(BoundingFrustum boundingFrustum, float& distance) const;
			bool Intersects(BoundingFrustum boundingFrustum, Vector3& point) const;
			bool Intersects(BoundingSphere boundingSphere) const;
			bool Intersects(BoundingSphere boundingSphere, float& distance) const;
			bool Intersects(BoundingSphere boundingSphere, Vector3& point) const;
			bool Intersects(Plane plane) const;
			bool Intersects(Plane plane, float& distance) const;
			bool Intersects(Plane plane, Vector3& point) const;
		};
	}
}

