/// @ref gtx_mixed_product

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType mixedProduct
	(
		vec<3, ComponentType, Q> const& v1,
		vec<3, ComponentType, Q> const& v2,
		vec<3, ComponentType, Q> const& v3
	)
	{
		return dot(cross(v1, v2), v3);
	}
}//namespace glm
