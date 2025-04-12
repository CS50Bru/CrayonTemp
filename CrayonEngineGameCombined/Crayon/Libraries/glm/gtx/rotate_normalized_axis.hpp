/// @ref gtx_rotate_normalized_axis
/// @file glm/gtx/rotate_normalized_axis.hpp
///
/// @see core (dependence)
/// @see gtc_matrix_transform
/// @see gtc_quaternion
///
/// @defgroup gtx_rotate_normalized_axis GLM_GTX_rotate_normalized_axis
/// @ingroup gtx
///
/// Include <glm/gtx/rotate_normalized_axis.hpp> to use the features of this extension.
///
/// Quaternions and matrices rotations around normalized axis.

#pragma once

// Dependency:
#include "../glm.hpp"
#include "../gtc/epsilon.hpp"
#include "../gtc/quaternion.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	ifndef GLM_ENABLE_EXPERIMENTAL
#		pragma message("GLM: GLM_GTX_rotate_normalized_axis is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("GLM: GLM_GTX_rotate_normalized_axis extension included")
#	endif
#endif

namespace glm
{
	/// @addtogroup gtx_rotate_normalized_axis
	/// @{

	/// Builds a rotation 4 * 4 matrix created from a normalized axis and an angle.
	///
	/// @param m Input matrix multiplied by this rotation matrix.
	/// @param angle Rotation angle expressed in radians.
	/// @param axis Rotation axis, must be normalized.
	/// @tparam ComponentType Value type used to build the matrix. Currently supported: half (not recommended), float or double.
	///
	/// @see gtx_rotate_normalized_axis
	/// @see - rotate(ComponentType angle, ComponentType x, ComponentType y, ComponentType z)
	/// @see - rotate(mat<4, 4, ComponentType, Q> const& m, ComponentType angle, ComponentType x, ComponentType y, ComponentType z)
	/// @see - rotate(ComponentType angle, vec<3, ComponentType, Q> const& v)
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> rotateNormalizedAxis(
		mat<4, 4, ComponentType, Q> const& m,
		ComponentType const& angle,
		vec<3, ComponentType, Q> const& axis);

	/// Rotates a quaternion from a vector of 3 components normalized axis and an angle.
	///
	/// @param q Source orientation
	/// @param angle Angle expressed in radians.
	/// @param axis Normalized axis of the rotation, must be normalized.
	///
	/// @see gtx_rotate_normalized_axis
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> rotateNormalizedAxis(
		qua<ComponentType, Q> const& q,
		ComponentType const& angle,
		vec<3, ComponentType, Q> const& axis);

	/// @}
}//namespace glm

#include "rotate_normalized_axis.inl"
