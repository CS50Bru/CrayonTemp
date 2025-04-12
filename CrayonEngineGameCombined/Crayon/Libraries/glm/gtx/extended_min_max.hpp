/// @ref gtx_extended_min_max
/// @file glm/gtx/extended_min_max.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_extended_min_max GLM_GTX_extented_min_max
/// @ingroup gtx
///
/// Include <glm/gtx/extented_min_max.hpp> to use the features of this extension.
///
/// Min and max functions for 3 to 4 parameters.

#pragma once

// Dependency:
#include "../glm.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	ifndef GLM_ENABLE_EXPERIMENTAL
#		pragma message("GLM: GLM_GTX_extented_min_max is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("GLM: GLM_GTX_extented_min_max extension included")
#	endif
#endif

namespace glm
{
	/// @addtogroup gtx_extended_min_max
	/// @{

	/// Return the minimum component-wise values of 3 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType min(
		ComponentType const& x,
		ComponentType const& y,
		ComponentType const& z);

	/// Return the minimum component-wise values of 3 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_DECL C<ComponentType> min(
		C<ComponentType> const& x,
		typename C<ComponentType>::ComponentType const& y,
		typename C<ComponentType>::ComponentType const& z);

	/// Return the minimum component-wise values of 3 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_DECL C<ComponentType> min(
		C<ComponentType> const& x,
		C<ComponentType> const& y,
		C<ComponentType> const& z);

	/// Return the minimum component-wise values of 4 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType min(
		ComponentType const& x,
		ComponentType const& y,
		ComponentType const& z,
		ComponentType const& w);

	/// Return the minimum component-wise values of 4 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_DECL C<ComponentType> min(
		C<ComponentType> const& x,
		typename C<ComponentType>::ComponentType const& y,
		typename C<ComponentType>::ComponentType const& z,
		typename C<ComponentType>::ComponentType const& w);

	/// Return the minimum component-wise values of 4 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_DECL C<ComponentType> min(
		C<ComponentType> const& x,
		C<ComponentType> const& y,
		C<ComponentType> const& z,
		C<ComponentType> const& w);

	/// Return the maximum component-wise values of 3 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType max(
		ComponentType const& x,
		ComponentType const& y,
		ComponentType const& z);

	/// Return the maximum component-wise values of 3 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_DECL C<ComponentType> max(
		C<ComponentType> const& x,
		typename C<ComponentType>::ComponentType const& y,
		typename C<ComponentType>::ComponentType const& z);

	/// Return the maximum component-wise values of 3 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_DECL C<ComponentType> max(
		C<ComponentType> const& x,
		C<ComponentType> const& y,
		C<ComponentType> const& z);

	/// Return the maximum component-wise values of 4 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType max(
		ComponentType const& x,
		ComponentType const& y,
		ComponentType const& z,
		ComponentType const& w);

	/// Return the maximum component-wise values of 4 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_DECL C<ComponentType> max(
		C<ComponentType> const& x,
		typename C<ComponentType>::ComponentType const& y,
		typename C<ComponentType>::ComponentType const& z,
		typename C<ComponentType>::ComponentType const& w);

	/// Return the maximum component-wise values of 4 inputs
	/// @see gtx_extented_min_max
	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_DECL C<ComponentType> max(
		C<ComponentType> const& x,
		C<ComponentType> const& y,
		C<ComponentType> const& z,
		C<ComponentType> const& w);

	/// Returns y if y < x; otherwise, it returns x. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam genType Floating-point or integer; scalar or vector types.
	///
	/// @see gtx_extented_min_max
	template<typename genType>
	GLM_FUNC_DECL genType fmin(genType x, genType y);

	/// Returns y if x < y; otherwise, it returns x. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam genType Floating-point; scalar or vector types.
	///
	/// @see gtx_extented_min_max
	/// @see <a href="http://en.cppreference.com/w/cpp/numeric/math/fmax">std::fmax documentation</a>
	template<typename genType>
	GLM_FUNC_DECL genType fmax(genType x, genType y);

	/// Returns min(max(x, minVal), maxVal) for each component in x. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see gtx_extented_min_max
	template<typename genType>
	GLM_FUNC_DECL genType fclamp(genType x, genType minVal, genType maxVal);

	/// Returns min(max(x, minVal), maxVal) for each component in x. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see gtx_extented_min_max
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> fclamp(vec<L, ComponentType, Q> const& x, ComponentType minVal, ComponentType maxVal);

	/// Returns min(max(x, minVal), maxVal) for each component in x. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see gtx_extented_min_max
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> fclamp(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& minVal, vec<L, ComponentType, Q> const& maxVal);


	/// @}
}//namespace glm

#include "extended_min_max.inl"
