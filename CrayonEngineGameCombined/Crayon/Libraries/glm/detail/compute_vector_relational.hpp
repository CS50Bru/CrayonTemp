#pragma once

//#include "compute_common.hpp"
#include "setup.hpp"
#include <limits>

namespace glm{
namespace detail
{
	template <typename ComponentType, bool isFloat>
	struct compute_equal
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static bool call(ComponentType a, ComponentType b)
		{
			return a == b;
		}
	};
/*
	template <typename ComponentType>
	struct compute_equal<ComponentType, true>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static bool call(ComponentType a, ComponentType b)
		{
			return detail::compute_abs<ComponentType, std::numeric_limits<ComponentType>::is_signed>::call(b - a) <= static_cast<ComponentType>(0);
			//return std::memcmp(&a, &b, sizeof(ComponentType)) == 0;
		}
	};
*/
}//namespace detail
}//namespace glm
