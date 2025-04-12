/// @ref ext_quaternion_common
/// @file glm/ext/quaternion_common.hpp
///
/// @defgroup ext_quaternion_common GLM_EXT_quaternion_common
/// @ingroup ext
///
/// Provides common functions for quaternion types
///
/// Include <glm/ext/quaternion_common.hpp> to use the features of this extension.
///
/// @see ext_scalar_common
/// @see ext_vector_common
/// @see ext_quaternion_float
/// @see ext_quaternion_double
/// @see ext_quaternion_exponential
/// @see ext_quaternion_geometric
/// @see ext_quaternion_relational
/// @see ext_quaternion_trigonometric
/// @see ext_quaternion_transform

#pragma once

// Dependency:
#include "../ext/scalar_constants.hpp"
#include "../ext/quaternion_geometric.hpp"
#include "../common.hpp"
#include "../trigonometric.hpp"
#include "../exponential.hpp"
#include <limits>

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_common extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_common
	/// @{

	/// Spherical linear interpolation of two quaternions.
	/// The interpolation is oriented and the rotation is performed at constant speed.
	/// For short path spherical linear interpolation, use the slerp function.
	///
	/// @param x A quaternion
	/// @param y A quaternion
	/// @param a Interpolation factor. The interpolation is defined beyond the range [0, 1].
	///
	/// @tparam ComponentType A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	///
	/// @see - slerp(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType const& a)
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> mix(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType a);

	/// Linear interpolation of two quaternions.
	/// The interpolation is oriented.
	///
	/// @param x A quaternion
	/// @param y A quaternion
	/// @param a Interpolation factor. The interpolation is defined in the range [0, 1].
	///
	/// @tparam ComponentType A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> lerp(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType a);

	/// Spherical linear interpolation of two quaternions.
	/// The interpolation always take the short path and the rotation is performed at constant speed.
	///
	/// @param x A quaternion
	/// @param y A quaternion
	/// @param a Interpolation factor. The interpolation is defined beyond the range [0, 1].
	///
	/// @tparam ComponentType A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> slerp(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType a);

	/// Returns the q conjugate.
	///
	/// @tparam ComponentType A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> conjugate(qua<ComponentType, Q> const& q);

	/// Returns the q inverse.
	///
	/// @tparam ComponentType A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> inverse(qua<ComponentType, Q> const& q);

	/// Returns true if x holds a NaN (not a number)
	/// representation in the underlying implementation's set of
	/// floating point representations. Returns false otherwise,
	/// including for implementations with no NaN
	/// representations.
	///
	/// /!\ When using compiler fast math, this function may fail.
	///
	/// @tparam ComponentType A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> isnan(qua<ComponentType, Q> const& x);

	/// Returns true if x holds a positive infinity or negative
	/// infinity representation in the underlying implementation's
	/// set of floating point representations. Returns false
	/// otherwise, including for implementations with no infinity
	/// representations.
	///
	/// @tparam ComponentType A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> isinf(qua<ComponentType, Q> const& x);

	/// @}
} //namespace glm

#include "quaternion_common.inl"
