/// @ref gtx_closest_point

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> closestPointOnLine
	(
		vec<3, ComponentType, Q> const& point,
		vec<3, ComponentType, Q> const& a,
		vec<3, ComponentType, Q> const& b
	)
	{
		ComponentType LineLength = distance(a, b);
		vec<3, ComponentType, Q> Vector = point - a;
		vec<3, ComponentType, Q> LineDirection = (b - a) / LineLength;

		// Project Vector to LineDirection to get the distance of point from a
		ComponentType Distance = dot(Vector, LineDirection);

		if(Distance <= ComponentType(0)) return a;
		if(Distance >= LineLength) return b;
		return a + LineDirection * Distance;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<2, ComponentType, Q> closestPointOnLine
	(
		vec<2, ComponentType, Q> const& point,
		vec<2, ComponentType, Q> const& a,
		vec<2, ComponentType, Q> const& b
	)
	{
		ComponentType LineLength = distance(a, b);
		vec<2, ComponentType, Q> Vector = point - a;
		vec<2, ComponentType, Q> LineDirection = (b - a) / LineLength;

		// Project Vector to LineDirection to get the distance of point from a
		ComponentType Distance = dot(Vector, LineDirection);

		if(Distance <= ComponentType(0)) return a;
		if(Distance >= LineLength) return b;
		return a + LineDirection * Distance;
	}

}//namespace glm
