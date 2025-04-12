#pragma once

#include "../common.hpp"

namespace glm{
namespace detail
{
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType mod289(ComponentType const& x)
	{
		return x - floor(x * (static_cast<ComponentType>(1.0) / static_cast<ComponentType>(289.0))) * static_cast<ComponentType>(289.0);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType permute(ComponentType const& x)
	{
		return mod289(((x * static_cast<ComponentType>(34)) + static_cast<ComponentType>(1)) * x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<2, ComponentType, Q> permute(vec<2, ComponentType, Q> const& x)
	{
		return mod289(((x * static_cast<ComponentType>(34)) + static_cast<ComponentType>(1)) * x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> permute(vec<3, ComponentType, Q> const& x)
	{
		return mod289(((x * static_cast<ComponentType>(34)) + static_cast<ComponentType>(1)) * x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> permute(vec<4, ComponentType, Q> const& x)
	{
		return mod289(((x * static_cast<ComponentType>(34)) + static_cast<ComponentType>(1)) * x);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType taylorInvSqrt(ComponentType const& r)
	{
		return static_cast<ComponentType>(1.79284291400159) - static_cast<ComponentType>(0.85373472095314) * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<2, ComponentType, Q> taylorInvSqrt(vec<2, ComponentType, Q> const& r)
	{
		return static_cast<ComponentType>(1.79284291400159) - static_cast<ComponentType>(0.85373472095314) * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> taylorInvSqrt(vec<3, ComponentType, Q> const& r)
	{
		return static_cast<ComponentType>(1.79284291400159) - static_cast<ComponentType>(0.85373472095314) * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> taylorInvSqrt(vec<4, ComponentType, Q> const& r)
	{
		return static_cast<ComponentType>(1.79284291400159) - static_cast<ComponentType>(0.85373472095314) * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<2, ComponentType, Q> fade(vec<2, ComponentType, Q> const& t)
	{
		return (t * t * t) * (t * (t * static_cast<ComponentType>(6) - static_cast<ComponentType>(15)) + static_cast<ComponentType>(10));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> fade(vec<3, ComponentType, Q> const& t)
	{
		return (t * t * t) * (t * (t * static_cast<ComponentType>(6) - static_cast<ComponentType>(15)) + static_cast<ComponentType>(10));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> fade(vec<4, ComponentType, Q> const& t)
	{
		return (t * t * t) * (t * (t * static_cast<ComponentType>(6) - static_cast<ComponentType>(15)) + static_cast<ComponentType>(10));
	}
}//namespace detail
}//namespace glm

