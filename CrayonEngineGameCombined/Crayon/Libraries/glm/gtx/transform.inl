/// @ref gtx_transform

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> translate(vec<3, ComponentType, Q> const& v)
	{
		return translate(mat<4, 4, ComponentType, Q>(static_cast<ComponentType>(1)), v);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> rotate(ComponentType angle, vec<3, ComponentType, Q> const& v)
	{
		return rotate(mat<4, 4, ComponentType, Q>(static_cast<ComponentType>(1)), angle, v);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> scale(vec<3, ComponentType, Q> const& v)
	{
		return scale(mat<4, 4, ComponentType, Q>(static_cast<ComponentType>(1)), v);
	}

}//namespace glm
