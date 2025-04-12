/// @ref core
/// @file glm/trigonometric.hpp
///
/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
///
/// @defgroup core_func_trigonometric Angle and Trigonometry Functions
/// @ingroup core
///
/// Function parameters specified as angle are assumed to be in units of radians.
/// In no case will any of these functions result in a divide by zero error. If
/// the divisor of a ratio is 0, then results will be undefined.
///
/// These all operate component-wise. The description is per component.
///
/// Include <glm/trigonometric.hpp> to use these core features.
///
/// @see ext_vector_trigonometric

#pragma once

#include "detail/setup.hpp"
#include "detail/qualifier.hpp"

namespace glm
{
	/// @addtogroup core_func_trigonometric
	/// @{

	/// Converts degrees to radians and returns the result.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/radians.xml">GLSL radians man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, ComponentType, Q> radians(vec<L, ComponentType, Q> const& degrees);

	/// Converts radians to degrees and returns the result.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/degrees.xml">GLSL degrees man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, ComponentType, Q> degrees(vec<L, ComponentType, Q> const& radians);

	/// The standard trigonometric sine function.
	/// The values returned by this function will range from [-1, 1].
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/sin.xml">GLSL sin man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> sin(vec<L, ComponentType, Q> const& angle);

	/// The standard trigonometric cosine function.
	/// The values returned by this function will range from [-1, 1].
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/cos.xml">GLSL cos man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> cos(vec<L, ComponentType, Q> const& angle);

	/// The standard trigonometric tangent function.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/tan.xml">GLSL tan man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> tan(vec<L, ComponentType, Q> const& angle);

	/// Arc sine. Returns an angle whose sine is x.
	/// The range of values returned by this function is [-PI/2, PI/2].
	/// Results are undefined if |x| > 1.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/asin.xml">GLSL asin man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> asin(vec<L, ComponentType, Q> const& x);

	/// Arc cosine. Returns an angle whose sine is x.
	/// The range of values returned by this function is [0, PI].
	/// Results are undefined if |x| > 1.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/acos.xml">GLSL acos man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> acos(vec<L, ComponentType, Q> const& x);

	/// Arc tangent. Returns an angle whose tangent is y/x.
	/// The signs of x and y are used to determine what
	/// quadrant the angle is in. The range of values returned
	/// by this function is [-PI, PI]. Results are undefined
	/// if x and y are both 0.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/atan.xml">GLSL atan man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> atan(vec<L, ComponentType, Q> const& y, vec<L, ComponentType, Q> const& x);

	/// Arc tangent. Returns an angle whose tangent is y_over_x.
	/// The range of values returned by this function is [-PI/2, PI/2].
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/atan.xml">GLSL atan man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> atan(vec<L, ComponentType, Q> const& y_over_x);

	/// Returns the hyperbolic sine function, (exp(x) - exp(-x)) / 2
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/sinh.xml">GLSL sinh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> sinh(vec<L, ComponentType, Q> const& angle);

	/// Returns the hyperbolic cosine function, (exp(x) + exp(-x)) / 2
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/cosh.xml">GLSL cosh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> cosh(vec<L, ComponentType, Q> const& angle);

	/// Returns the hyperbolic tangent function, sinh(angle) / cosh(angle)
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/tanh.xml">GLSL tanh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> tanh(vec<L, ComponentType, Q> const& angle);

	/// Arc hyperbolic sine; returns the inverse of sinh.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/asinh.xml">GLSL asinh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> asinh(vec<L, ComponentType, Q> const& x);

	/// Arc hyperbolic cosine; returns the non-negative inverse
	/// of cosh. Results are undefined if x < 1.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/acosh.xml">GLSL acosh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> acosh(vec<L, ComponentType, Q> const& x);

	/// Arc hyperbolic tangent; returns the inverse of tanh.
	/// Results are undefined if abs(x) >= 1.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/atanh.xml">GLSL atanh man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.1 Angle and Trigonometry Functions</a>
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> atanh(vec<L, ComponentType, Q> const& x);

	/// @}
}//namespace glm

#include "detail/func_trigonometric.inl"
