/// @ref ext_quaternion_transform
/// @file glm/ext/quaternion_transform.hpp
///
/// @defgroup ext_quaternion_transform GLM_EXT_quaternion_transform
/// @ingroup ext
///
/// Provides transformation functions for quaternion types
///
/// Include <glm/ext/quaternion_transform.hpp> to use the features of this extension.
///
/// @see ext_quaternion_float
/// @see ext_quaternion_double
/// @see ext_quaternion_exponential
/// @see ext_quaternion_geometric
/// @see ext_quaternion_relational
/// @see ext_quaternion_trigonometric

#pragma once

// Dependency:
#include "../common.hpp"
#include "../trigonometric.hpp"
#include "../geometric.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_transform extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_transform
	/// @{

	/// Rotates a quaternion from a vector of 3 components axis and an angle.
	///
	/// @param q Source orientation
	/// @param angle Angle expressed in radians.
	/// @param axis Axis of the rotation
	///
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> rotate(qua<ComponentType, Q> const& q, ComponentType const& angle, vec<3, ComponentType, Q> const& axis);
	/// @}
} //namespace glm

#include "quaternion_transform.inl"
