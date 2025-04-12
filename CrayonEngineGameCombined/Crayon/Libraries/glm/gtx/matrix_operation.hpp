/// @ref gtx_matrix_operation
/// @file glm/gtx/matrix_operation.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_matrix_operation GLM_GTX_matrix_operation
/// @ingroup gtx
///
/// Include <glm/gtx/matrix_operation.hpp> to use the features of this extension.
///
/// Build diagonal matrices from vectors.

#pragma once

// Dependency:
#include "../glm.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	ifndef GLM_ENABLE_EXPERIMENTAL
#		pragma message("GLM: GLM_GTX_matrix_operation is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("GLM: GLM_GTX_matrix_operation extension included")
#	endif
#endif

namespace glm
{
	/// @addtogroup gtx_matrix_operation
	/// @{

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, ComponentType, Q> diagonal2x2(
		vec<2, ComponentType, Q> const& v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 3, ComponentType, Q> diagonal2x3(
		vec<2, ComponentType, Q> const& v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> diagonal2x4(
		vec<2, ComponentType, Q> const& v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<3, 2, ComponentType, Q> diagonal3x2(
		vec<2, ComponentType, Q> const& v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, ComponentType, Q> diagonal3x3(
		vec<3, ComponentType, Q> const& v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, ComponentType, Q> diagonal3x4(
		vec<3, ComponentType, Q> const& v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 2, ComponentType, Q> diagonal4x2(
		vec<2, ComponentType, Q> const& v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 3, ComponentType, Q> diagonal4x3(
		vec<3, ComponentType, Q> const& v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> diagonal4x4(
		vec<4, ComponentType, Q> const& v);

	/// Build an adjugate  matrix.
	/// From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 2, ComponentType, Q> adjugate(mat<2, 2, ComponentType, Q> const& m);

	/// Build an adjugate  matrix.
	/// From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, ComponentType, Q> adjugate(mat<3, 3, ComponentType, Q> const& m);

	/// Build an adjugate  matrix.
	/// From GLM_GTX_matrix_operation extension.
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> adjugate(mat<4, 4, ComponentType, Q> const& m);

	/// @}
}//namespace glm

#include "matrix_operation.inl"
