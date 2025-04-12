/// @ref gtx_functions
/// @file glm/gtx/functions.hpp
///
/// @see core (dependence)
/// @see gtc_quaternion (dependence)
///
/// @defgroup gtx_functions GLM_GTX_functions
/// @ingroup gtx
///
/// Include <glm/gtx/functions.hpp> to use the features of this extension.
///
/// List of useful common functions.

#pragma once

// Dependencies
#include "../detail/setup.hpp"
#include "../detail/qualifier.hpp"
#include "../detail/type_vec2.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	ifndef GLM_ENABLE_EXPERIMENTAL
#		pragma message("GLM: GLM_GTX_functions is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("GLM: GLM_GTX_functions extension included")
#	endif
#endif

namespace glm
{
	/// @addtogroup gtx_functions
	/// @{

	/// 1D gauss function
	///
	/// @see gtc_epsilon
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType gauss(
		ComponentType x,
		ComponentType ExpectedValue,
		ComponentType StandardDeviation);

	/// 2D gauss function
	///
	/// @see gtc_epsilon
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL ComponentType gauss(
		vec<2, ComponentType, Q> const& Coord,
		vec<2, ComponentType, Q> const& ExpectedValue,
		vec<2, ComponentType, Q> const& StandardDeviation);

	/// @}
}//namespace glm

#include "functions.inl"

