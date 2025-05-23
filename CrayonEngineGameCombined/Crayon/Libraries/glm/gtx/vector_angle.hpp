/// @ref gtx_vector_angle
/// @file glm/gtx/vector_angle.hpp
///
/// @see core (dependence)
/// @see gtx_quaternion (dependence)
/// @see gtx_epsilon (dependence)
///
/// @defgroup gtx_vector_angle GLM_GTX_vector_angle
/// @ingroup gtx
///
/// Include <glm/gtx/vector_angle.hpp> to use the features of this extension.
///
/// Compute angle between vectors

#pragma once

// Dependency:
#include "../glm.hpp"
#include "../gtc/epsilon.hpp"
#include "../gtx/quaternion.hpp"
#include "../gtx/rotate_vector.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	ifndef GLM_ENABLE_EXPERIMENTAL
#		pragma message("GLM: GLM_GTX_vector_angle is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("GLM: GLM_GTX_vector_angle extension included")
#	endif
#endif

namespace glm
{
	/// @addtogroup gtx_vector_angle
	/// @{

	//! Returns the absolute angle between two vectors.
	//! Parameters need to be normalized.
	/// @see gtx_vector_angle extension.
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL ComponentType angle(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& y);

	//! Returns the oriented angle between two 2d vectors.
	//! Parameters need to be normalized.
	/// @see gtx_vector_angle extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL ComponentType orientedAngle(vec<2, ComponentType, Q> const& x, vec<2, ComponentType, Q> const& y);

	//! Returns the oriented angle between two 3d vectors based from a reference axis.
	//! Parameters need to be normalized.
	/// @see gtx_vector_angle extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL ComponentType orientedAngle(vec<3, ComponentType, Q> const& x, vec<3, ComponentType, Q> const& y, vec<3, ComponentType, Q> const& ref);

	/// @}
}// namespace glm

#include "vector_angle.inl"
