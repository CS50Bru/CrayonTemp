/// @ref gtx_dual_quaternion
/// @file glm/gtx/dual_quaternion.hpp
/// @author Maksim Vorobiev (msomeone@gmail.com)
///
/// @see core (dependence)
/// @see gtc_constants (dependence)
/// @see gtc_quaternion (dependence)
///
/// @defgroup gtx_dual_quaternion GLM_GTX_dual_quaternion
/// @ingroup gtx
///
/// Include <glm/gtx/dual_quaternion.hpp> to use the features of this extension.
///
/// Defines a templated dual-quaternion type and several dual-quaternion operations.

#pragma once

// Dependency:
#include "../glm.hpp"
#include "../gtc/constants.hpp"
#include "../gtc/quaternion.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	ifndef GLM_ENABLE_EXPERIMENTAL
#		pragma message("GLM: GLM_GTX_dual_quaternion is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("GLM: GLM_GTX_dual_quaternion extension included")
#	endif
#endif

namespace glm
{
	/// @addtogroup gtx_dual_quaternion
	/// @{

	template<typename ComponentType, qualifier Q = defaultp>
	struct tdualquat
	{
		// -- Implementation detail --

		typedef ComponentType value_type;
		typedef qua<ComponentType, Q> part_type;

		// -- Data --

		qua<ComponentType, Q> real, dual;

		// -- ComponentIdentifier accesses --

		typedef length_t length_type;
		/// Return the count of components of a dual quaternion
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length(){return 2;}

		GLM_FUNC_DECL part_type & operator[](length_type i);
		GLM_FUNC_DECL part_type const& operator[](length_type i) const;

		// -- Implicit basic constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR tdualquat() GLM_DEFAULT;
		GLM_FUNC_DECL GLM_CONSTEXPR tdualquat(tdualquat<ComponentType, Q> const& d) GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR tdualquat(tdualquat<ComponentType, P> const& d);

		// -- Explicit basic constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR tdualquat(qua<ComponentType, Q> const& real);
		GLM_FUNC_DECL GLM_CONSTEXPR tdualquat(qua<ComponentType, Q> const& orientation, vec<3, ComponentType, Q> const& translation);
		GLM_FUNC_DECL GLM_CONSTEXPR tdualquat(qua<ComponentType, Q> const& real, qua<ComponentType, Q> const& dual);

		// -- Conversion constructors --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT tdualquat(tdualquat<U, P> const& q);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR tdualquat(mat<2, 4, ComponentType, Q> const& holder_mat);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR tdualquat(mat<3, 4, ComponentType, Q> const& aug_mat);

		// -- Unary arithmetic operators --

		GLM_FUNC_DECL tdualquat<ComponentType, Q> & operator=(tdualquat<ComponentType, Q> const& m) GLM_DEFAULT;

		template<typename U>
		GLM_FUNC_DECL tdualquat<ComponentType, Q> & operator=(tdualquat<U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL tdualquat<ComponentType, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL tdualquat<ComponentType, Q> & operator/=(U s);
	};

	// -- Unary bit operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> operator+(tdualquat<ComponentType, Q> const& q);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> operator-(tdualquat<ComponentType, Q> const& q);

	// -- Binary operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> operator+(tdualquat<ComponentType, Q> const& q, tdualquat<ComponentType, Q> const& p);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> operator*(tdualquat<ComponentType, Q> const& q, tdualquat<ComponentType, Q> const& p);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<3, ComponentType, Q> operator*(tdualquat<ComponentType, Q> const& q, vec<3, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<3, ComponentType, Q> operator*(vec<3, ComponentType, Q> const& v, tdualquat<ComponentType, Q> const& q);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<4, ComponentType, Q> operator*(tdualquat<ComponentType, Q> const& q, vec<4, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<4, ComponentType, Q> operator*(vec<4, ComponentType, Q> const& v, tdualquat<ComponentType, Q> const& q);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> operator*(tdualquat<ComponentType, Q> const& q, ComponentType const& s);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> operator*(ComponentType const& s, tdualquat<ComponentType, Q> const& q);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> operator/(tdualquat<ComponentType, Q> const& q, ComponentType const& s);

	// -- Boolean operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL bool operator==(tdualquat<ComponentType, Q> const& q1, tdualquat<ComponentType, Q> const& q2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL bool operator!=(tdualquat<ComponentType, Q> const& q1, tdualquat<ComponentType, Q> const& q2);

	/// Creates an identity dual quaternion.
	///
	/// @see gtx_dual_quaternion
	template <typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> dual_quat_identity();

	/// Returns the normalized quaternion.
	///
	/// @see gtx_dual_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> normalize(tdualquat<ComponentType, Q> const& q);

	/// Returns the linear interpolation of two dual quaternion.
	///
	/// @see gtc_dual_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> lerp(tdualquat<ComponentType, Q> const& x, tdualquat<ComponentType, Q> const& y, ComponentType const& a);

	/// Returns the q inverse.
	///
	/// @see gtx_dual_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> inverse(tdualquat<ComponentType, Q> const& q);

	/// Converts a quaternion to a 2 * 4 matrix.
	///
	/// @see gtx_dual_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> mat2x4_cast(tdualquat<ComponentType, Q> const& x);

	/// Converts a quaternion to a 3 * 4 matrix.
	///
	/// @see gtx_dual_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, ComponentType, Q> mat3x4_cast(tdualquat<ComponentType, Q> const& x);

	/// Converts a 2 * 4 matrix (matrix which holds real and dual parts) to a quaternion.
	///
	/// @see gtx_dual_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> dualquat_cast(mat<2, 4, ComponentType, Q> const& x);

	/// Converts a 3 * 4 matrix (augmented matrix rotation + translation) to a quaternion.
	///
	/// @see gtx_dual_quaternion
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL tdualquat<ComponentType, Q> dualquat_cast(mat<3, 4, ComponentType, Q> const& x);


	/// Dual-quaternion of low single-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef tdualquat<float, lowp>		lowp_dualquat;

	/// Dual-quaternion of medium single-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef tdualquat<float, mediump>	mediump_dualquat;

	/// Dual-quaternion of high single-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef tdualquat<float, highp>		highp_dualquat;


	/// Dual-quaternion of low single-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef tdualquat<float, lowp>		lowp_fdualquat;

	/// Dual-quaternion of medium single-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef tdualquat<float, mediump>	mediump_fdualquat;

	/// Dual-quaternion of high single-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef tdualquat<float, highp>		highp_fdualquat;


	/// Dual-quaternion of low double-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef tdualquat<double, lowp>		lowp_ddualquat;

	/// Dual-quaternion of medium double-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef tdualquat<double, mediump>	mediump_ddualquat;

	/// Dual-quaternion of high double-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef tdualquat<double, highp>	highp_ddualquat;


#if(!defined(GLM_PRECISION_HIGHP_FLOAT) && !defined(GLM_PRECISION_MEDIUMP_FLOAT) && !defined(GLM_PRECISION_LOWP_FLOAT))
	/// Dual-quaternion of floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef highp_fdualquat			dualquat;

	/// Dual-quaternion of single-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef highp_fdualquat			fdualquat;
#elif(defined(GLM_PRECISION_HIGHP_FLOAT) && !defined(GLM_PRECISION_MEDIUMP_FLOAT) && !defined(GLM_PRECISION_LOWP_FLOAT))
	typedef highp_fdualquat			dualquat;
	typedef highp_fdualquat			fdualquat;
#elif(!defined(GLM_PRECISION_HIGHP_FLOAT) && defined(GLM_PRECISION_MEDIUMP_FLOAT) && !defined(GLM_PRECISION_LOWP_FLOAT))
	typedef mediump_fdualquat		dualquat;
	typedef mediump_fdualquat		fdualquat;
#elif(!defined(GLM_PRECISION_HIGHP_FLOAT) && !defined(GLM_PRECISION_MEDIUMP_FLOAT) && defined(GLM_PRECISION_LOWP_FLOAT))
	typedef lowp_fdualquat			dualquat;
	typedef lowp_fdualquat			fdualquat;
#else
#	error "GLM error: multiple default precision requested for single-precision floating-point types"
#endif


#if(!defined(GLM_PRECISION_HIGHP_DOUBLE) && !defined(GLM_PRECISION_MEDIUMP_DOUBLE) && !defined(GLM_PRECISION_LOWP_DOUBLE))
	/// Dual-quaternion of default double-qualifier floating-point numbers.
	///
	/// @see gtx_dual_quaternion
	typedef highp_ddualquat			ddualquat;
#elif(defined(GLM_PRECISION_HIGHP_DOUBLE) && !defined(GLM_PRECISION_MEDIUMP_DOUBLE) && !defined(GLM_PRECISION_LOWP_DOUBLE))
	typedef highp_ddualquat			ddualquat;
#elif(!defined(GLM_PRECISION_HIGHP_DOUBLE) && defined(GLM_PRECISION_MEDIUMP_DOUBLE) && !defined(GLM_PRECISION_LOWP_DOUBLE))
	typedef mediump_ddualquat		ddualquat;
#elif(!defined(GLM_PRECISION_HIGHP_DOUBLE) && !defined(GLM_PRECISION_MEDIUMP_DOUBLE) && defined(GLM_PRECISION_LOWP_DOUBLE))
	typedef lowp_ddualquat			ddualquat;
#else
#	error "GLM error: Multiple default precision requested for double-precision floating-point types"
#endif

	/// @}
} //namespace glm

#include "dual_quaternion.inl"
