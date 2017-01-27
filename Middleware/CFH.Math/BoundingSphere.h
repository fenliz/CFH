#pragma once
#include "Common.h"
#include "Vector3.h"

namespace CFH
{
	namespace Math
	{
		enum class ContainmentType;
		enum class PlaneIntersectionType;
		struct BoundingBox;
		struct BoundingFrustum;
		struct Plane;
		struct Ray;
		struct Matrix4;

		struct DLL_API BoundingSphere final
		{
		public:
			Vector3 Center;
			float Radius;

			BoundingSphere();
			BoundingSphere(Vector3 center, float radius);
			~BoundingSphere();

			bool operator==(BoundingSphere boundingSphere) const;
			bool operator!=(BoundingSphere boundingSphere) const;
			BoundingSphere operator=(BoundingSphere boundingSphere);

			static BoundingSphere CreateFromBoundingBox(BoundingBox boundingBox);
			static void CreateFromBoundingBox(BoundingBox boundingBox, BoundingSphere& result);
			static BoundingSphere CreateFromFrustum(BoundingFrustum boundingFrustum);
			static void CreateFromFrustum(BoundingFrustum boundingFrustum, BoundingSphere& result);
			static BoundingSphere CreateFromPoints(Vector3 points[], int count);
			static void CreateFromPoints(Vector3 points[], int count, BoundingSphere& result);
			static BoundingSphere CreateMerged(BoundingSphere boundingSphere, BoundingSphere boundingSphere2);
			static void CreateMerged(BoundingSphere boundingSphere, BoundingSphere boundingSphere2, BoundingSphere& result);

			ContainmentType Contains(Vector3 point) const;
			void Contains(Vector3 point, ContainmentType& result) const;
			ContainmentType Contains(BoundingBox boundingBox) const;
			void Contains(BoundingBox boundingBox, ContainmentType& result) const;
			ContainmentType Contains(BoundingFrustum boundingFrustum) const;
			void Contains(BoundingFrustum boundingFrustum, ContainmentType& result) const;
			ContainmentType Contains(BoundingSphere boundingSphere) const;
			void Contains(BoundingSphere boundingSphere, ContainmentType& result) const;

			bool Intersects(BoundingBox boundingBox) const;
			bool Intersects(BoundingFrustum boundingFrustum) const;
			bool Intersects(BoundingSphere boundingSphere) const;
			PlaneIntersectionType Intersects(Plane plane) const;
			void Intersects(Plane plane, PlaneIntersectionType& result) const;
			bool Intersects(Ray ray, float& distance) const;

			BoundingSphere Transform(Matrix4 matrix);
			void Transform(Matrix4 matrix, BoundingSphere& result);
		};
	}
}


