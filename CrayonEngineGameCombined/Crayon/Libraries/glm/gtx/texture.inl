/// @ref gtx_texture

namespace glm
{
	template <length_t L, typename ComponentType, qualifier Q>
	inline ComponentType levels(vec<L, ComponentType, Q> const& Extent)
	{
		return glm::log2(compMax(Extent)) + static_cast<ComponentType>(1);
	}

	template <typename ComponentType>
	inline ComponentType levels(ComponentType Extent)
	{
		return vec<1, ComponentType, defaultp>(Extent).x;
	}
}//namespace glm

