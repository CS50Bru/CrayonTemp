/// @ref gtx_quaternion
/// @file glm/gtx/quaternion.hpp
///
/// @see core (dependence)
/// @see gtx_extented_min_max (dependence)
///
/// @defgroup gtx_quaternion GLM_GTX_quaternion
/// @ingroup gtx
///
/// Include <glm/gtx/quaternion.hpp> to use the features of this extension.
///
/// Extented quaternion types and functions

#pragma once

// Dependency:
#include "../glm.hpp"
#include "../gtc/constants.hpp"
#include "../gtc/quaternion.hpp"
#include "../ext/quaternion_exponential.hpp"
#include "../gtx/norm.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	ifndef GLM_ENABLE_EXPERIMENTAL
#		pragma message("GLM: GLM_GTX_quaternion is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("GLM: GLM_GTX_quaternion extension included")
#	endif
#endif

namespace glm
{
	/// @addtogroup gtx_quaternion
	/// @{

	/// Create an identity quaternion.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR qua<ComponentType, Q> quat_identity();

	/// Compute a cross product between a quaternion and a vector.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<3, ComponentType, Q> cross(
		qua<ComponentType, Q> const& q,
		vec<3, ComponentType, Q> const& v);

	//! Compute a cross product between a vector and a quaternion.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<3, ComponentType, Q> cross(
		vec<3, ComponentType, Q> const& v,
		qua<ComponentType, Q> const& q);

	//! Compute a point on a path according squad equation.
	//! q1 and q2 are control points; s1 and s2 are intermediate control points.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> squad(
		qua<ComponentType, Q> const& q1,
		qua<ComponentType, Q> const& q2,
		qua<ComponentType, Q> const& s1,
		qua<ComponentType, Q> const& s2,
		ComponentType const& h);

	//! Returns an intermediate control point for squad interpolation.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> intermediate(
		qua<ComponentType, Q> const& prev,
		qua<ComponentType, Q> const& curr,
		qua<ComponentType, Q> const& next);

	//! Returns quarternion square root.
	///
	/// @see gtx_quaternion
	//template<typename ComponentType, qualifier Q>
	//qua<ComponentType, Q> sqrt(
	//	qua<ComponentType, Q> const& q);

	//! Rotates a 3 components vector by a quaternion.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<3, ComponentType, Q> rotate(
		qua<ComponentType, Q> const& q,
		vec<3, ComponentType, Q> const& v);

	/// Rotates a 4 components vector by a quaternion.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<4, ComponentType, Q> rotate(
		qua<ComponentType, Q> const& q,
		vec<4, ComponentType, Q> const& v);

	/// Extract the real component of a quaternion.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL ComponentType extractRealComponent(
		qua<ComponentType, Q> const& q);

	/// Converts a quaternion to a 3 * 3 matrix.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<3, 3, ComponentType, Q> toMat3(
		qua<ComponentType, Q> const& x){return mat3_cast(x);}

	/// Converts a quaternion to a 4 * 4 matrix.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> toMat4(
		qua<ComponentType, Q> const& x){return mat4_cast(x);}

	/// Converts a 3 * 3 matrix to a quaternion.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> toQuat(
		mat<3, 3, ComponentType, Q> const& x){return quat_cast(x);}

	/// Converts a 4 * 4 matrix to a quaternion.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> toQuat(
		mat<4, 4, ComponentType, Q> const& x){return quat_cast(x);}

	/// Quaternion interpolation using the rotation short path.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> shortMix(
		qua<ComponentType, Q> const& x,
		qua<ComponentType, Q> const& y,
		ComponentType const& a);

	/// Quaternion normalized linear interpolation.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> fastMix(
		qua<ComponentType, Q> const& x,
		qua<ComponentType, Q> const& y,
		ComponentType const& a);

	/// Compute the rotation between two vectors.
	/// @param orig vector, needs to be normalized
	/// @param dest vector, needs to be normalized
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL qua<ComponentType, Q> rotation(
		vec<3, ComponentType, Q> const& orig,
		vec<3, ComponentType, Q> const& dest);

	/// Returns the squared length of x.
	///
	/// @see gtx_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR ComponentType length2(qua<ComponentType, Q> const& q);

	/// @}
}//namespace glm

#include "quaternion.inl"
