/// @ref core
/// @file glm/matrix.hpp
///
/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
///
/// @defgroup core_func_matrix Matrix functions
/// @ingroup core
///
/// Provides GLSL matrix functions.
///
/// Include <glm/matrix.hpp> to use these core features.

#pragma once

// Dependencies
#include "detail/qualifier.hpp"
#include "detail/setup.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat2x2.hpp"
#include "mat2x3.hpp"
#include "mat2x4.hpp"
#include "mat3x2.hpp"
#include "mat3x3.hpp"
#include "mat3x4.hpp"
#include "mat4x2.hpp"
#include "mat4x3.hpp"
#include "mat4x4.hpp"

namespace glm {
namespace detail
{
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	struct outerProduct_trait{};

	template<typename ComponentType, qualifier Q>
	struct outerProduct_trait<2, 2, ComponentType, Q>
	{
		typedef mat<2, 2, ComponentType, Q> type;
	};

	template<typename ComponentType, qualifier Q>
	struct outerProduct_trait<2, 3, ComponentType, Q>
	{
		typedef mat<3, 2, ComponentType, Q> type;
	};

	template<typename ComponentType, qualifier Q>
	struct outerProduct_trait<2, 4, ComponentType, Q>
	{
		typedef mat<4, 2, ComponentType, Q> type;
	};

	template<typename ComponentType, qualifier Q>
	struct outerProduct_trait<3, 2, ComponentType, Q>
	{
		typedef mat<2, 3, ComponentType, Q> type;
	};

	template<typename ComponentType, qualifier Q>
	struct outerProduct_trait<3, 3, ComponentType, Q>
	{
		typedef mat<3, 3, ComponentType, Q> type;
	};

	template<typename ComponentType, qualifier Q>
	struct outerProduct_trait<3, 4, ComponentType, Q>
	{
		typedef mat<4, 3, ComponentType, Q> type;
	};

	template<typename ComponentType, qualifier Q>
	struct outerProduct_trait<4, 2, ComponentType, Q>
	{
		typedef mat<2, 4, ComponentType, Q> type;
	};

	template<typename ComponentType, qualifier Q>
	struct outerProduct_trait<4, 3, ComponentType, Q>
	{
		typedef mat<3, 4, ComponentType, Q> type;
	};

	template<typename ComponentType, qualifier Q>
	struct outerProduct_trait<4, 4, ComponentType, Q>
	{
		typedef mat<4, 4, ComponentType, Q> type;
	};
}//namespace detail

	 /// @addtogroup core_func_matrix
	 /// @{

	 /// Multiply matrix x by matrix y component-wise, i.e.,
	 /// result[i][j] is the scalar product of x[i][j] and y[i][j].
	 ///
	 /// @tparam C Integer between 1 and 4 included that qualify the number a column
	 /// @tparam R Integer between 1 and 4 included that qualify the number a row
	 /// @tparam ComponentType Floating-point or signed integer scalar types
	 /// @tparam Q Value from qualifier enum
	 ///
	 /// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/matrixCompMult.xml">GLSL matrixCompMult man page</a>
	 /// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<C, R, ComponentType, Q> matrixCompMult(mat<C, R, ComponentType, Q> const& x, mat<C, R, ComponentType, Q> const& y);

	/// Treats the first parameter c as a column vector
	/// and the second parameter r as a row vector
	/// and does a linear algebraic matrix multiply c * r.
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number a column
	/// @tparam R Integer between 1 and 4 included that qualify the number a row
	/// @tparam ComponentType Floating-point or signed integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/outerProduct.xml">GLSL outerProduct man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL typename detail::outerProduct_trait<C, R, ComponentType, Q>::type outerProduct(vec<C, ComponentType, Q> const& c, vec<R, ComponentType, Q> const& r);

	/// Returns the transposed matrix of x
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number a column
	/// @tparam R Integer between 1 and 4 included that qualify the number a row
	/// @tparam ComponentType Floating-point or signed integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/transpose.xml">GLSL transpose man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL typename mat<C, R, ComponentType, Q>::transpose_type transpose(mat<C, R, ComponentType, Q> const& x);

	/// Return the determinant of a squared matrix.
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number a column
	/// @tparam R Integer between 1 and 4 included that qualify the number a row
	/// @tparam ComponentType Floating-point or signed integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/determinant.xml">GLSL determinant man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL ComponentType determinant(mat<C, R, ComponentType, Q> const& m);

	/// Return the inverse of a squared matrix.
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number a column
	/// @tparam R Integer between 1 and 4 included that qualify the number a row
	/// @tparam ComponentType Floating-point or signed integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/inverse.xml">GLSL inverse man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<C, R, ComponentType, Q> inverse(mat<C, R, ComponentType, Q> const& m);

	/// @}
}//namespace glm

#include "detail/func_matrix.inl"
