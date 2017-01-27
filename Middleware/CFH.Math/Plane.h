#pragma once
#include "Common.h"
#include "Vector3.h"

namespace CFH
{
	namespace Math
	{
		struct BoundingBox;
		struct Quaternion;
		struct BoundingFrustum;
		struct BoundingSphere;
		struct Vector4;
		struct Matrix4;

		enum class DLL_API PlaneIntersectionType
		{
			Back,
			Front,
			Intersecting
		};

		struct DLL_API Plane final
		{
		public:
			float D;
			Vector3 Normal;

			Plane();
			Plane(float a, float b, float c, float d);
			Plane(Vector3 normal, float d);
			Plane(Vector3 point1, Vector3 point2, Vector3 point3);
			Plane(Vector4 value);
			~Plane();

			Plane operator=(Plane plane);

			static Plane CreateFromPoints(Vector3 point1, Vector3 point2, Vector3 point3);
			static void CreateFromPoints(Vector3 point1, Vector3 point2, Vector3 point3, Plane& result);

			float Dot(Vector4 vector) const;
			void Dot(Vector4 vector, float& result) const;
			float DotCoordinate(Vector3 vector) const;
			void DotCoordinate(Vector3 vector, float& result) const;
			float DotNormal(Vector3 vector) const;
			void DotNormal(Vector3 vector, float& result) const;

			void Normalize();
			static Plane Normalize(Plane plane);
			static void Normalize(Plane plane, Plane& result);

			float Distance(Vector3 point) const;
			void Distance(Vector3 point, float& result) const;
			Vector3 DistanceVector(Vector3 point) const;
			void DistanceVector(Vector3 point, Vector3& result) const;

			Vector3 GetLocation() const;
			void GetLocation(Vector3& result) const;

			static Vector3 Project(Vector3 point, Plane plane);
			static void Project(Vector3 point, Plane plane, Vector3& result);

			PlaneIntersectionType Intersects(Vector3 point) const;
			void Intersects(Vector3 point, PlaneIntersectionType& result) const;
			PlaneIntersectionType Intersects(Vector3 point, float& distance) const;
			void Intersects(Vector3 point, float& distance, PlaneIntersectionType& result) const;
			PlaneIntersectionType Intersects(BoundingBox boundingBox) const;
			void Intersects(BoundingBox boundingBox, PlaneIntersectionType& result) const;
			PlaneIntersectionType Intersects(BoundingFrustum boundingFrustum) const;
			void Intersects(BoundingFrustum boundingFrustum, PlaneIntersectionType& result) const;
			PlaneIntersectionType Intersects(BoundingSphere boundingSphere) const;
			void Intersects(BoundingSphere boundingSphere, PlaneIntersectionType& result) const;
		};
	}
}