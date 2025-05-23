/// @ref gtx_associated_min_max
/// @file glm/gtx/associated_min_max.hpp
///
/// @see core (dependence)
/// @see gtx_extented_min_max (dependence)
///
/// @defgroup gtx_associated_min_max GLM_GTX_associated_min_max
/// @ingroup gtx
///
/// Include <glm/gtx/associated_min_max.hpp> to use the features of this extension.
///
/// @brief Min and max functions that return associated values not the compared onces.

#pragma once

// Dependency:
#include "../glm.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	ifndef GLM_ENABLE_EXPERIMENTAL
#		pragma message("GLM: GLM_GTX_associated_min_max is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("GLM: GLM_GTX_associated_min_max extension included")
#	endif
#endif

namespace glm
{
	/// @addtogroup gtx_associated_min_max
	/// @{

	/// Minimum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL U associatedMin(ComponentType x, U a, ComponentType y, U b);

	/// Minimum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<2, U, Q> associatedMin(
		vec<L, ComponentType, Q> const& x, vec<L, U, Q> const& a,
		vec<L, ComponentType, Q> const& y, vec<L, U, Q> const& b);

	/// Minimum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMin(
		ComponentType x, const vec<L, U, Q>& a,
		ComponentType y, const vec<L, U, Q>& b);

	/// Minimum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMin(
		vec<L, ComponentType, Q> const& x, U a,
		vec<L, ComponentType, Q> const& y, U b);

	/// Minimum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<typename ComponentType, typename U>
	GLM_FUNC_DECL U associatedMin(
		ComponentType x, U a,
		ComponentType y, U b,
		ComponentType z, U c);

	/// Minimum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMin(
		vec<L, ComponentType, Q> const& x, vec<L, U, Q> const& a,
		vec<L, ComponentType, Q> const& y, vec<L, U, Q> const& b,
		vec<L, ComponentType, Q> const& z, vec<L, U, Q> const& c);

	/// Minimum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<typename ComponentType, typename U>
	GLM_FUNC_DECL U associatedMin(
		ComponentType x, U a,
		ComponentType y, U b,
		ComponentType z, U c,
		ComponentType w, U d);

	/// Minimum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMin(
		vec<L, ComponentType, Q> const& x, vec<L, U, Q> const& a,
		vec<L, ComponentType, Q> const& y, vec<L, U, Q> const& b,
		vec<L, ComponentType, Q> const& z, vec<L, U, Q> const& c,
		vec<L, ComponentType, Q> const& w, vec<L, U, Q> const& d);

	/// Minimum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMin(
		ComponentType x, vec<L, U, Q> const& a,
		ComponentType y, vec<L, U, Q> const& b,
		ComponentType z, vec<L, U, Q> const& c,
		ComponentType w, vec<L, U, Q> const& d);

	/// Minimum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMin(
		vec<L, ComponentType, Q> const& x, U a,
		vec<L, ComponentType, Q> const& y, U b,
		vec<L, ComponentType, Q> const& z, U c,
		vec<L, ComponentType, Q> const& w, U d);

	/// Maximum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<typename ComponentType, typename U>
	GLM_FUNC_DECL U associatedMax(ComponentType x, U a, ComponentType y, U b);

	/// Maximum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<2, U, Q> associatedMax(
		vec<L, ComponentType, Q> const& x, vec<L, U, Q> const& a,
		vec<L, ComponentType, Q> const& y, vec<L, U, Q> const& b);

	/// Maximum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> associatedMax(
		ComponentType x, vec<L, U, Q> const& a,
		ComponentType y, vec<L, U, Q> const& b);

	/// Maximum comparison between 2 variables and returns 2 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMax(
		vec<L, ComponentType, Q> const& x, U a,
		vec<L, ComponentType, Q> const& y, U b);

	/// Maximum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<typename ComponentType, typename U>
	GLM_FUNC_DECL U associatedMax(
		ComponentType x, U a,
		ComponentType y, U b,
		ComponentType z, U c);

	/// Maximum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMax(
		vec<L, ComponentType, Q> const& x, vec<L, U, Q> const& a,
		vec<L, ComponentType, Q> const& y, vec<L, U, Q> const& b,
		vec<L, ComponentType, Q> const& z, vec<L, U, Q> const& c);

	/// Maximum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> associatedMax(
		ComponentType x, vec<L, U, Q> const& a,
		ComponentType y, vec<L, U, Q> const& b,
		ComponentType z, vec<L, U, Q> const& c);

	/// Maximum comparison between 3 variables and returns 3 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMax(
		vec<L, ComponentType, Q> const& x, U a,
		vec<L, ComponentType, Q> const& y, U b,
		vec<L, ComponentType, Q> const& z, U c);

	/// Maximum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<typename ComponentType, typename U>
	GLM_FUNC_DECL U associatedMax(
		ComponentType x, U a,
		ComponentType y, U b,
		ComponentType z, U c,
		ComponentType w, U d);

	/// Maximum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMax(
		vec<L, ComponentType, Q> const& x, vec<L, U, Q> const& a,
		vec<L, ComponentType, Q> const& y, vec<L, U, Q> const& b,
		vec<L, ComponentType, Q> const& z, vec<L, U, Q> const& c,
		vec<L, ComponentType, Q> const& w, vec<L, U, Q> const& d);

	/// Maximum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMax(
		ComponentType x, vec<L, U, Q> const& a,
		ComponentType y, vec<L, U, Q> const& b,
		ComponentType z, vec<L, U, Q> const& c,
		ComponentType w, vec<L, U, Q> const& d);

	/// Maximum comparison between 4 variables and returns 4 associated variable values
	/// @see gtx_associated_min_max
	template<length_t L, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, U, Q> associatedMax(
		vec<L, ComponentType, Q> const& x, U a,
		vec<L, ComponentType, Q> const& y, U b,
		vec<L, ComponentType, Q> const& z, U c,
		vec<L, ComponentType, Q> const& w, U d);

	/// @}
} //namespace glm

#include "associated_min_max.inl"
