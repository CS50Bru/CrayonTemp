/// @ref gtx_extend

namespace glm
{
	template<typename genType>
	GLM_FUNC_QUALIFIER genType extend
	(
		genType const& Origin,
		genType const& Source,
		genType const& Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<2, ComponentType, Q> extend
	(
		vec<2, ComponentType, Q> const& Origin,
		vec<2, ComponentType, Q> const& Source,
		ComponentType const& Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> extend
	(
		vec<3, ComponentType, Q> const& Origin,
		vec<3, ComponentType, Q> const& Source,
		ComponentType const& Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> extend
	(
		vec<4, ComponentType, Q> const& Origin,
		vec<4, ComponentType, Q> const& Source,
		ComponentType const& Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}
}//namespace glm
