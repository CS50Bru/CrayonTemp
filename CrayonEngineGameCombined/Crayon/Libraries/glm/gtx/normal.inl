/// @ref gtx_normal

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> triangleNormal
	(
		vec<3, ComponentType, Q> const& p1,
		vec<3, ComponentType, Q> const& p2,
		vec<3, ComponentType, Q> const& p3
	)
	{
		return normalize(cross(p1 - p2, p1 - p3));
	}
}//namespace glm
