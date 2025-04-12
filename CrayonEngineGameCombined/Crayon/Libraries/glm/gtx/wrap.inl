/// @ref gtx_wrap

namespace glm
{
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> clamp(vec<L, ComponentType, Q> const& Texcoord)
	{
		return glm::clamp(Texcoord, vec<L, ComponentType, Q>(0), vec<L, ComponentType, Q>(1));
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER genType clamp(genType const& Texcoord)
	{
		return clamp(vec<1, genType, defaultp>(Texcoord)).x;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> repeat(vec<L, ComponentType, Q> const& Texcoord)
	{
		return glm::fract(Texcoord);
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER genType repeat(genType const& Texcoord)
	{
		return repeat(vec<1, genType, defaultp>(Texcoord)).x;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> mirrorClamp(vec<L, ComponentType, Q> const& Texcoord)
	{
		return glm::fract(glm::abs(Texcoord));
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER genType mirrorClamp(genType const& Texcoord)
	{
		return mirrorClamp(vec<1, genType, defaultp>(Texcoord)).x;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> mirrorRepeat(vec<L, ComponentType, Q> const& Texcoord)
	{
		vec<L, ComponentType, Q> const Abs = glm::abs(Texcoord);
		vec<L, ComponentType, Q> const Clamp = glm::mod(glm::floor(Abs), vec<L, ComponentType, Q>(2));
		vec<L, ComponentType, Q> const Floor = glm::floor(Abs);
		vec<L, ComponentType, Q> const Rest = Abs - Floor;
		vec<L, ComponentType, Q> const Mirror = Clamp + Rest;
		return mix(Rest, vec<L, ComponentType, Q>(1) - Rest, glm::greaterThanEqual(Mirror, vec<L, ComponentType, Q>(1)));
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER genType mirrorRepeat(genType const& Texcoord)
	{
		return mirrorRepeat(vec<1, genType, defaultp>(Texcoord)).x;
	}
}//namespace glm
