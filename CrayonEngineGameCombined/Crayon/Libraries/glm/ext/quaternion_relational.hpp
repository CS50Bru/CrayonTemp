/// @ref ext_quaternion_relational
/// @file glm/ext/quaternion_relational.hpp
///
/// @defgroup ext_quaternion_relational GLM_EXT_quaternion_relational
/// @ingroup ext
///
/// Exposes comparison functions for quaternion types that take a user defined epsilon values.
///
/// Include <glm/ext/quaternion_relational.hpp> to use the features of this extension.
///
/// @see core_vector_relational
/// @see ext_vector_relational
/// @see ext_matrix_relational
/// @see ext_quaternion_float
/// @see ext_quaternion_double

#pragma once

// Dependency:
#include "../vector_relational.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_relational extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_relational
	/// @{

	/// Returns the component-wise comparison of result x == y.
	///
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> equal(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y);

	/// Returns the component-wise comparison of |x - y| < epsilon.
	///
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> equal(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType epsilon);

	/// Returns the component-wise comparison of result x != y.
	///
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> notEqual(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y);

	/// Returns the component-wise comparison of |x - y| >= epsilon.
	///
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<4, bool, Q> notEqual(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType epsilon);

	/// @}
} //namespace glm

#include "quaternion_relational.inl"
