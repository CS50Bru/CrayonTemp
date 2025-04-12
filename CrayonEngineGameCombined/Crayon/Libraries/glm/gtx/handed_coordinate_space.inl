/// @ref gtx_handed_coordinate_space

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER bool rightHanded
	(
		vec<3, ComponentType, Q> const& tangent,
		vec<3, ComponentType, Q> const& binormal,
		vec<3, ComponentType, Q> const& normal
	)
	{
		return dot(cross(normal, tangent), binormal) > ComponentType(0);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER bool leftHanded
	(
		vec<3, ComponentType, Q> const& tangent,
		vec<3, ComponentType, Q> const& binormal,
		vec<3, ComponentType, Q> const& normal
	)
	{
		return dot(cross(normal, tangent), binormal) < ComponentType(0);
	}
}//namespace glm
