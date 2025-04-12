/// @ref gtx_vec_swizzle
/// @file glm/gtx/vec_swizzle.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_vec_swizzle GLM_GTX_vec_swizzle
/// @ingroup gtx
///
/// Include <glm/gtx/vec_swizzle.hpp> to use the features of this extension.
///
/// Functions to perform swizzle operation.

#pragma once

#include "../glm.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	ifndef GLM_ENABLE_EXPERIMENTAL
#		pragma message("GLM: GLM_GTX_vec_swizzle is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("GLM: GLM_GTX_vec_swizzle extension included")
#	endif
#endif

namespace glm {
	// xx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> xx(const glm::vec<1, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> xx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> xx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> xx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.x, v.x);
	}

	// xy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> xy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> xy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> xy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.x, v.y);
	}

	// xz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> xz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> xz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.x, v.z);
	}

	// xw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> xw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.x, v.w);
	}

	// yx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> yx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> yx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> yx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.y, v.x);
	}

	// yy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> yy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> yy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> yy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.y, v.y);
	}

	// yz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> yz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> yz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.y, v.z);
	}

	// yw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> yw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.y, v.w);
	}

	// zx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> zx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> zx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.z, v.x);
	}

	// zy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> zy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> zy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.z, v.y);
	}

	// zz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> zz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> zz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.z, v.z);
	}

	// zw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> zw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.z, v.w);
	}

	// wx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> wx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.w, v.x);
	}

	// wy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> wy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.w, v.y);
	}

	// wz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> wz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.w, v.z);
	}

	// ww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<2, ComponentType, Q> ww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<2, ComponentType, Q>(v.w, v.w);
	}

	// xxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xxx(const glm::vec<1, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xxx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.x, v.x);
	}

	// xxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xxy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.x, v.y);
	}

	// xxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.x, v.z);
	}

	// xxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.x, v.w);
	}

	// xyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xyx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.y, v.x);
	}

	// xyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xyy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.y, v.y);
	}

	// xyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.y, v.z);
	}

	// xyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.y, v.w);
	}

	// xzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.z, v.x);
	}

	// xzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.z, v.y);
	}

	// xzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.z, v.z);
	}

	// xzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.z, v.w);
	}

	// xwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.w, v.x);
	}

	// xwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.w, v.y);
	}

	// xwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.w, v.z);
	}

	// xww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> xww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.x, v.w, v.w);
	}

	// yxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yxx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.x, v.x);
	}

	// yxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yxy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.x, v.y);
	}

	// yxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.x, v.z);
	}

	// yxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.x, v.w);
	}

	// yyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yyx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.y, v.x);
	}

	// yyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yyy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.y, v.y);
	}

	// yyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.y, v.z);
	}

	// yyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.y, v.w);
	}

	// yzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.z, v.x);
	}

	// yzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.z, v.y);
	}

	// yzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.z, v.z);
	}

	// yzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.z, v.w);
	}

	// ywx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> ywx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.w, v.x);
	}

	// ywy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> ywy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.w, v.y);
	}

	// ywz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> ywz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.w, v.z);
	}

	// yww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> yww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.y, v.w, v.w);
	}

	// zxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.x, v.x);
	}

	// zxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.x, v.y);
	}

	// zxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.x, v.z);
	}

	// zxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.x, v.w);
	}

	// zyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.y, v.x);
	}

	// zyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.y, v.y);
	}

	// zyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.y, v.z);
	}

	// zyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.y, v.w);
	}

	// zzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.z, v.x);
	}

	// zzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.z, v.y);
	}

	// zzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.z, v.z);
	}

	// zzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.z, v.w);
	}

	// zwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.w, v.x);
	}

	// zwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.w, v.y);
	}

	// zwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.w, v.z);
	}

	// zww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> zww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.z, v.w, v.w);
	}

	// wxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.x, v.x);
	}

	// wxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.x, v.y);
	}

	// wxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.x, v.z);
	}

	// wxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.x, v.w);
	}

	// wyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.y, v.x);
	}

	// wyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.y, v.y);
	}

	// wyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.y, v.z);
	}

	// wyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.y, v.w);
	}

	// wzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.z, v.x);
	}

	// wzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.z, v.y);
	}

	// wzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.z, v.z);
	}

	// wzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.z, v.w);
	}

	// wwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.w, v.x);
	}

	// wwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.w, v.y);
	}

	// wwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> wwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.w, v.z);
	}

	// www
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<3, ComponentType, Q> www(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<3, ComponentType, Q>(v.w, v.w, v.w);
	}

	// xxxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxxx(const glm::vec<1, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxxx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.x, v.x);
	}

	// xxxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxxy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.x, v.y);
	}

	// xxxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.x, v.z);
	}

	// xxxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.x, v.w);
	}

	// xxyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxyx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.y, v.x);
	}

	// xxyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxyy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.y, v.y);
	}

	// xxyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.y, v.z);
	}

	// xxyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.y, v.w);
	}

	// xxzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.z, v.x);
	}

	// xxzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.z, v.y);
	}

	// xxzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.z, v.z);
	}

	// xxzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.z, v.w);
	}

	// xxwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.w, v.x);
	}

	// xxwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.w, v.y);
	}

	// xxwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.w, v.z);
	}

	// xxww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xxww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.x, v.w, v.w);
	}

	// xyxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyxx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.x, v.x);
	}

	// xyxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyxy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.x, v.y);
	}

	// xyxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.x, v.z);
	}

	// xyxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.x, v.w);
	}

	// xyyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyyx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.y, v.x);
	}

	// xyyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyyy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.y, v.y);
	}

	// xyyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.y, v.z);
	}

	// xyyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.y, v.w);
	}

	// xyzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.z, v.x);
	}

	// xyzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.z, v.y);
	}

	// xyzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.z, v.z);
	}

	// xyzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.z, v.w);
	}

	// xywx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xywx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.w, v.x);
	}

	// xywy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xywy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.w, v.y);
	}

	// xywz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xywz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.w, v.z);
	}

	// xyww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xyww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.y, v.w, v.w);
	}

	// xzxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.x, v.x);
	}

	// xzxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.x, v.y);
	}

	// xzxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.x, v.z);
	}

	// xzxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.x, v.w);
	}

	// xzyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.y, v.x);
	}

	// xzyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.y, v.y);
	}

	// xzyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.y, v.z);
	}

	// xzyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.y, v.w);
	}

	// xzzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.z, v.x);
	}

	// xzzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.z, v.y);
	}

	// xzzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.z, v.z);
	}

	// xzzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.z, v.w);
	}

	// xzwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.w, v.x);
	}

	// xzwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.w, v.y);
	}

	// xzwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.w, v.z);
	}

	// xzww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xzww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.z, v.w, v.w);
	}

	// xwxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.x, v.x);
	}

	// xwxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.x, v.y);
	}

	// xwxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.x, v.z);
	}

	// xwxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.x, v.w);
	}

	// xwyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.y, v.x);
	}

	// xwyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.y, v.y);
	}

	// xwyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.y, v.z);
	}

	// xwyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.y, v.w);
	}

	// xwzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.z, v.x);
	}

	// xwzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.z, v.y);
	}

	// xwzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.z, v.z);
	}

	// xwzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.z, v.w);
	}

	// xwwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.w, v.x);
	}

	// xwwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.w, v.y);
	}

	// xwwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.w, v.z);
	}

	// xwww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> xwww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.x, v.w, v.w, v.w);
	}

	// yxxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxxx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.x, v.x);
	}

	// yxxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxxy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.x, v.y);
	}

	// yxxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.x, v.z);
	}

	// yxxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.x, v.w);
	}

	// yxyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxyx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.y, v.x);
	}

	// yxyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxyy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.y, v.y);
	}

	// yxyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.y, v.z);
	}

	// yxyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.y, v.w);
	}

	// yxzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.z, v.x);
	}

	// yxzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.z, v.y);
	}

	// yxzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.z, v.z);
	}

	// yxzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.z, v.w);
	}

	// yxwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.w, v.x);
	}

	// yxwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.w, v.y);
	}

	// yxwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.w, v.z);
	}

	// yxww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yxww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.x, v.w, v.w);
	}

	// yyxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyxx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.x, v.x);
	}

	// yyxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyxy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.x, v.y);
	}

	// yyxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.x, v.z);
	}

	// yyxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.x, v.w);
	}

	// yyyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyyx(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.y, v.x);
	}

	// yyyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyyy(const glm::vec<2, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.y, v.y);
	}

	// yyyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.y, v.z);
	}

	// yyyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.y, v.w);
	}

	// yyzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.z, v.x);
	}

	// yyzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.z, v.y);
	}

	// yyzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.z, v.z);
	}

	// yyzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.z, v.w);
	}

	// yywx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yywx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.w, v.x);
	}

	// yywy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yywy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.w, v.y);
	}

	// yywz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yywz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.w, v.z);
	}

	// yyww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yyww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.y, v.w, v.w);
	}

	// yzxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.x, v.x);
	}

	// yzxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.x, v.y);
	}

	// yzxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.x, v.z);
	}

	// yzxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.x, v.w);
	}

	// yzyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.y, v.x);
	}

	// yzyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.y, v.y);
	}

	// yzyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.y, v.z);
	}

	// yzyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.y, v.w);
	}

	// yzzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.z, v.x);
	}

	// yzzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.z, v.y);
	}

	// yzzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.z, v.z);
	}

	// yzzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.z, v.w);
	}

	// yzwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.w, v.x);
	}

	// yzwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.w, v.y);
	}

	// yzwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.w, v.z);
	}

	// yzww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> yzww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.z, v.w, v.w);
	}

	// ywxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.x, v.x);
	}

	// ywxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.x, v.y);
	}

	// ywxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.x, v.z);
	}

	// ywxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.x, v.w);
	}

	// ywyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.y, v.x);
	}

	// ywyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.y, v.y);
	}

	// ywyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.y, v.z);
	}

	// ywyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.y, v.w);
	}

	// ywzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.z, v.x);
	}

	// ywzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.z, v.y);
	}

	// ywzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.z, v.z);
	}

	// ywzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.z, v.w);
	}

	// ywwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.w, v.x);
	}

	// ywwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.w, v.y);
	}

	// ywwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.w, v.z);
	}

	// ywww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> ywww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.y, v.w, v.w, v.w);
	}

	// zxxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.x, v.x);
	}

	// zxxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.x, v.y);
	}

	// zxxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.x, v.z);
	}

	// zxxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.x, v.w);
	}

	// zxyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.y, v.x);
	}

	// zxyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.y, v.y);
	}

	// zxyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.y, v.z);
	}

	// zxyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.y, v.w);
	}

	// zxzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.z, v.x);
	}

	// zxzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.z, v.y);
	}

	// zxzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.z, v.z);
	}

	// zxzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.z, v.w);
	}

	// zxwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.w, v.x);
	}

	// zxwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.w, v.y);
	}

	// zxwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.w, v.z);
	}

	// zxww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zxww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.x, v.w, v.w);
	}

	// zyxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.x, v.x);
	}

	// zyxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.x, v.y);
	}

	// zyxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.x, v.z);
	}

	// zyxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.x, v.w);
	}

	// zyyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.y, v.x);
	}

	// zyyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.y, v.y);
	}

	// zyyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.y, v.z);
	}

	// zyyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.y, v.w);
	}

	// zyzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.z, v.x);
	}

	// zyzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.z, v.y);
	}

	// zyzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.z, v.z);
	}

	// zyzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.z, v.w);
	}

	// zywx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zywx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.w, v.x);
	}

	// zywy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zywy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.w, v.y);
	}

	// zywz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zywz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.w, v.z);
	}

	// zyww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zyww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.y, v.w, v.w);
	}

	// zzxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzxx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.x, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.x, v.x);
	}

	// zzxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzxy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.x, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.x, v.y);
	}

	// zzxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzxz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.x, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.x, v.z);
	}

	// zzxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.x, v.w);
	}

	// zzyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzyx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.y, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.y, v.x);
	}

	// zzyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzyy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.y, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.y, v.y);
	}

	// zzyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzyz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.y, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.y, v.z);
	}

	// zzyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.y, v.w);
	}

	// zzzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzzx(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.z, v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.z, v.x);
	}

	// zzzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzzy(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.z, v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.z, v.y);
	}

	// zzzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzzz(const glm::vec<3, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.z, v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.z, v.z);
	}

	// zzzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.z, v.w);
	}

	// zzwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.w, v.x);
	}

	// zzwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.w, v.y);
	}

	// zzwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.w, v.z);
	}

	// zzww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zzww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.z, v.w, v.w);
	}

	// zwxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.x, v.x);
	}

	// zwxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.x, v.y);
	}

	// zwxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.x, v.z);
	}

	// zwxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.x, v.w);
	}

	// zwyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.y, v.x);
	}

	// zwyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.y, v.y);
	}

	// zwyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.y, v.z);
	}

	// zwyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.y, v.w);
	}

	// zwzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.z, v.x);
	}

	// zwzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.z, v.y);
	}

	// zwzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.z, v.z);
	}

	// zwzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.z, v.w);
	}

	// zwwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.w, v.x);
	}

	// zwwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.w, v.y);
	}

	// zwwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.w, v.z);
	}

	// zwww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> zwww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.z, v.w, v.w, v.w);
	}

	// wxxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.x, v.x);
	}

	// wxxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.x, v.y);
	}

	// wxxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.x, v.z);
	}

	// wxxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.x, v.w);
	}

	// wxyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.y, v.x);
	}

	// wxyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.y, v.y);
	}

	// wxyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.y, v.z);
	}

	// wxyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.y, v.w);
	}

	// wxzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.z, v.x);
	}

	// wxzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.z, v.y);
	}

	// wxzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.z, v.z);
	}

	// wxzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.z, v.w);
	}

	// wxwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.w, v.x);
	}

	// wxwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.w, v.y);
	}

	// wxwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.w, v.z);
	}

	// wxww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wxww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.x, v.w, v.w);
	}

	// wyxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.x, v.x);
	}

	// wyxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.x, v.y);
	}

	// wyxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.x, v.z);
	}

	// wyxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.x, v.w);
	}

	// wyyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.y, v.x);
	}

	// wyyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.y, v.y);
	}

	// wyyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.y, v.z);
	}

	// wyyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.y, v.w);
	}

	// wyzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.z, v.x);
	}

	// wyzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.z, v.y);
	}

	// wyzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.z, v.z);
	}

	// wyzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.z, v.w);
	}

	// wywx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wywx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.w, v.x);
	}

	// wywy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wywy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.w, v.y);
	}

	// wywz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wywz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.w, v.z);
	}

	// wyww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wyww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.y, v.w, v.w);
	}

	// wzxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.x, v.x);
	}

	// wzxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.x, v.y);
	}

	// wzxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.x, v.z);
	}

	// wzxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.x, v.w);
	}

	// wzyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.y, v.x);
	}

	// wzyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.y, v.y);
	}

	// wzyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.y, v.z);
	}

	// wzyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.y, v.w);
	}

	// wzzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.z, v.x);
	}

	// wzzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.z, v.y);
	}

	// wzzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.z, v.z);
	}

	// wzzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.z, v.w);
	}

	// wzwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.w, v.x);
	}

	// wzwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.w, v.y);
	}

	// wzwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.w, v.z);
	}

	// wzww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wzww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.z, v.w, v.w);
	}

	// wwxx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwxx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.x, v.x);
	}

	// wwxy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwxy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.x, v.y);
	}

	// wwxz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwxz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.x, v.z);
	}

	// wwxw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwxw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.x, v.w);
	}

	// wwyx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwyx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.y, v.x);
	}

	// wwyy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwyy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.y, v.y);
	}

	// wwyz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwyz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.y, v.z);
	}

	// wwyw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwyw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.y, v.w);
	}

	// wwzx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwzx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.z, v.x);
	}

	// wwzy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwzy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.z, v.y);
	}

	// wwzz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwzz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.z, v.z);
	}

	// wwzw
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwzw(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.z, v.w);
	}

	// wwwx
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwwx(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.w, v.x);
	}

	// wwwy
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwwy(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.w, v.y);
	}

	// wwwz
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwwz(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.w, v.z);
	}

	// wwww
	template<typename ComponentType, qualifier Q>
	GLM_INLINE glm::vec<4, ComponentType, Q> wwww(const glm::vec<4, ComponentType, Q> &v) {
		return glm::vec<4, ComponentType, Q>(v.w, v.w, v.w, v.w);
	}

}
