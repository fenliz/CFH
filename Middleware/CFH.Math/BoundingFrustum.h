#pragma once
#include "Common.h"
#include "Plane.h"
#include "Matrix4.h"

namespace CFH
{
	namespace Math
	{
		enum class ContainmentType;
		enum class PlaneIntersectionType;
		struct BoundingBox;
		struct BoundingSphere;
		struct Ray;

		struct DLL_API BoundingFrustum final
		{
		private:
			Matrix4 inverseViewProjection_;
			Matrix4 viewProjection_;
			Plane planes_[6];
			Vector3 corners_[6];

			void CalculateCorner(int index, Vector3& result) const;

		public:
			static const int Corners = 8;
			static const int Planes = 6;

			BoundingFrustum();
			BoundingFrustum(Matrix4 value);
			~BoundingFrustum();

			bool operator==(BoundingFrustum boundingFrustum) const;
			bool operator!=(BoundingFrustum boundingFrustum) const;
			BoundingFrustum operator=(BoundingFrustum boundingFrustum);

			void SetViewProjection(Matrix4 matrix);
			Matrix4 GetViewProjection() const;
			void GetViewProjection(Matrix4& result) const;
			Matrix4 GetInverseViewProjection() const;
			void GetInverseViewProjection(Matrix4& result) const;

			Plane GetTop() const;
			void GetTop(Plane& result) const;
			Plane GetBottom() const;
			void GetBottom(Plane& result) const;
			Plane GetFar() const;
			void GetFar(Plane& result) const;
			Plane GetNear() const;
			void GetNear(Plane& result) const;
			Plane GetRight() const;
			void GetRight(Plane& result) const;
			Plane GetLeft() const;
			void GetLeft(Plane& result) const;
			void GetCorners(Vector3* corners, int size) const;
			Vector3 GetCorner(int index) const;
			void GetCorner(int index, Vector3& result) const;
			Plane GetPlane(int index) const;
			void GetPlane(int index, Plane& result) const;

			ContainmentType Contains(Vector3 point) const;
			void Contains(Vector3 point, ContainmentType& result) const;
			ContainmentType Contains(BoundingBox boundingBox) const;
			void Contains(BoundingBox boundingBox, ContainmentType& result) const;
			ContainmentType Contains(BoundingFrustum boundingFrustum) const;
			void Contains(BoundingFrustum boundingFrustum, ContainmentType& result) const;
			ContainmentType Contains(BoundingSphere boundingSphere) const;
			void Contains(BoundingSphere boundingSphere, ContainmentType& result) const;

			bool Intersects(BoundingBox box) const;
			void Intersects(BoundingBox box, bool& result) const;
			bool Intersects(BoundingFrustum frustum) const;
			void Intersects(BoundingFrustum frustum, bool& result) const;
			bool Intersects(BoundingSphere sphere) const;
			void Intersects(BoundingSphere sphere, bool& result) const;
			PlaneIntersectionType Intersects(Plane plane) const;
			void Intersects(Plane plane, PlaneIntersectionType& result) const;
			bool Intersects(Ray ray, float& distance) const;
			void Intersects(Ray ray, float& distance, bool& result) const;
		};
	}
}

