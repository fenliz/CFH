#pragma once
#include "Common.h"
#include "Vector3.h"

namespace CFH
{
	namespace Math
	{
		struct BoundingFrustum;
		struct BoundingSphere;
		struct Ray;
		struct Plane;
		enum class PlaneIntersectionType;

		enum class DLL_API ContainmentType
		{
			Disjoint,
			Contains,
			Intersects
		};

		struct DLL_API BoundingBox final
		{
		public:
			static const int Corners = 8;
			static const int Planes = 6;
			Vector3 Min, Max;

			BoundingBox();
			BoundingBox(Vector3 min, Vector3 max);
			~BoundingBox();

			bool operator==(BoundingBox boundingBox);
			bool operator!=(BoundingBox boundingBox);
			BoundingBox operator=(BoundingBox boundingBox);

			static BoundingBox CreateFromPoints(Vector3 points[], int count);
			static void CreateFromPoints(Vector3 points[], int count, BoundingBox& result);
			static BoundingBox CreateFromSphere(BoundingSphere boundingSphere);
			static void CreateFromSphere(BoundingSphere boundingSphere, BoundingBox& result);
			static BoundingBox CreateMerged(BoundingBox boundingBox, BoundingBox boundingBox2);
			static void CreateMerged(BoundingBox boundingBox, BoundingBox boundingBox2, BoundingBox& result);

			ContainmentType Contains(Vector3 point) const;
			void Contains(Vector3 point, ContainmentType& result) const;
			ContainmentType Contains(BoundingBox boundingBox) const;
			void Contains(BoundingBox boundingBox, ContainmentType& result) const;
			ContainmentType Contains(BoundingFrustum boundingFrustum) const;
			void Contains(BoundingFrustum boundingFrustum, ContainmentType& result) const;
			ContainmentType Contains(BoundingSphere boundingSphere) const;
			void Contains(BoundingSphere boundingSphere, ContainmentType& result) const;

			bool Intersects(BoundingBox boundingBox) const;
			void Intersects(BoundingBox boundingBox, bool& result) const;
			bool Intersects(BoundingFrustum boundingFrustum) const;
			void Intersects(BoundingFrustum boundingFrustum, bool& result) const;
			bool Intersects(BoundingSphere boundingSphere) const;
			void Intersects(BoundingSphere boundingSphere, bool& result) const;
			PlaneIntersectionType Intersects(Plane plane) const;
			void Intersects(Plane plane, PlaneIntersectionType& result) const;
			bool Intersects(Ray ray, float& distance) const;
			void Intersects(Ray ray, float& distance, bool& result) const;

			void GetCorners(Vector3* corners) const;
			Vector3 GetCorner(int index) const;
			void GetCorner(int index, Vector3& result) const;
		};
	}
}