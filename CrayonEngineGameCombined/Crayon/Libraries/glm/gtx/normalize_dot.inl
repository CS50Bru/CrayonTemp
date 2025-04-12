/// @ref gtx_normalize_dot

namespace glm
{
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType normalizeDot(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& y)
	{
		return glm::dot(x, y) * glm::inversesqrt(glm::dot(x, x) * glm::dot(y, y));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType fastNormalizeDot(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& y)
	{
		return glm::dot(x, y) * glm::fastInverseSqrt(glm::dot(x, x) * glm::dot(y, y));
	}
}//namespace glm
