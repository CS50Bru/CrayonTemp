/// @ref gtx_log_base

namespace glm
{
	template<typename genType>
	GLM_FUNC_QUALIFIER genType log(genType const& x, genType const& base)
	{
		return glm::log(x) / glm::log(base);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> log(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& base)
	{
		return glm::log(x) / glm::log(base);
	}
}//namespace glm
