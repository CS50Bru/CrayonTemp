/// @ref gtx_polar_coordinates

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> polar
	(
		vec<3, ComponentType, Q> const& euclidean
	)
	{
		ComponentType const Length(length(euclidean));
		vec<3, ComponentType, Q> const tmp(euclidean / Length);
		ComponentType const xz_dist(sqrt(tmp.x * tmp.x + tmp.z * tmp.z));

		return vec<3, ComponentType, Q>(
			asin(tmp.y),	// latitude
			atan(tmp.x, tmp.z),		// longitude
			xz_dist);				// xz distance
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> euclidean
	(
		vec<2, ComponentType, Q> const& polar
	)
	{
		ComponentType const latitude(polar.x);
		ComponentType const longitude(polar.y);

		return vec<3, ComponentType, Q>(
			cos(latitude) * sin(longitude),
			sin(latitude),
			cos(latitude) * cos(longitude));
	}

}//namespace glm
