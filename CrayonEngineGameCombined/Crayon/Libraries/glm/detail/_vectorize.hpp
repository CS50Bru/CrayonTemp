#pragma once

namespace glm{
namespace detail
{
	template<template<length_t L, typename ComponentType, qualifier Q> class vec, length_t L, typename R, typename ComponentType, qualifier Q>
	struct functor1{};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename R, typename ComponentType, qualifier Q>
	struct functor1<vec, 1, R, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<1, R, Q> call(R (*Func) (ComponentType x), vec<1, ComponentType, Q> const& v)
		{
			return vec<1, R, Q>(Func(v.x));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename R, typename ComponentType, qualifier Q>
	struct functor1<vec, 2, R, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<2, R, Q> call(R (*Func) (ComponentType x), vec<2, ComponentType, Q> const& v)
		{
			return vec<2, R, Q>(Func(v.x), Func(v.y));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename R, typename ComponentType, qualifier Q>
	struct functor1<vec, 3, R, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<3, R, Q> call(R (*Func) (ComponentType x), vec<3, ComponentType, Q> const& v)
		{
			return vec<3, R, Q>(Func(v.x), Func(v.y), Func(v.z));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename R, typename ComponentType, qualifier Q>
	struct functor1<vec, 4, R, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, R, Q> call(R (*Func) (ComponentType x), vec<4, ComponentType, Q> const& v)
		{
			return vec<4, R, Q>(Func(v.x), Func(v.y), Func(v.z), Func(v.w));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, length_t L, typename ComponentType, qualifier Q>
	struct functor2{};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename ComponentType, qualifier Q>
	struct functor2<vec, 1, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<1, ComponentType, Q> call(ComponentType (*Func) (ComponentType x, ComponentType y), vec<1, ComponentType, Q> const& a, vec<1, ComponentType, Q> const& b)
		{
			return vec<1, ComponentType, Q>(Func(a.x, b.x));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename ComponentType, qualifier Q>
	struct functor2<vec, 2, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<2, ComponentType, Q> call(ComponentType (*Func) (ComponentType x, ComponentType y), vec<2, ComponentType, Q> const& a, vec<2, ComponentType, Q> const& b)
		{
			return vec<2, ComponentType, Q>(Func(a.x, b.x), Func(a.y, b.y));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename ComponentType, qualifier Q>
	struct functor2<vec, 3, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<3, ComponentType, Q> call(ComponentType (*Func) (ComponentType x, ComponentType y), vec<3, ComponentType, Q> const& a, vec<3, ComponentType, Q> const& b)
		{
			return vec<3, ComponentType, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename ComponentType, qualifier Q>
	struct functor2<vec, 4, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, ComponentType, Q> call(ComponentType (*Func) (ComponentType x, ComponentType y), vec<4, ComponentType, Q> const& a, vec<4, ComponentType, Q> const& b)
		{
			return vec<4, ComponentType, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z), Func(a.w, b.w));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, length_t L, typename ComponentType, qualifier Q>
	struct functor2_vec_sca{};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename ComponentType, qualifier Q>
	struct functor2_vec_sca<vec, 1, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<1, ComponentType, Q> call(ComponentType (*Func) (ComponentType x, ComponentType y), vec<1, ComponentType, Q> const& a, ComponentType b)
		{
			return vec<1, ComponentType, Q>(Func(a.x, b));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename ComponentType, qualifier Q>
	struct functor2_vec_sca<vec, 2, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<2, ComponentType, Q> call(ComponentType (*Func) (ComponentType x, ComponentType y), vec<2, ComponentType, Q> const& a, ComponentType b)
		{
			return vec<2, ComponentType, Q>(Func(a.x, b), Func(a.y, b));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename ComponentType, qualifier Q>
	struct functor2_vec_sca<vec, 3, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<3, ComponentType, Q> call(ComponentType (*Func) (ComponentType x, ComponentType y), vec<3, ComponentType, Q> const& a, ComponentType b)
		{
			return vec<3, ComponentType, Q>(Func(a.x, b), Func(a.y, b), Func(a.z, b));
		}
	};

	template<template<length_t L, typename ComponentType, qualifier Q> class vec, typename ComponentType, qualifier Q>
	struct functor2_vec_sca<vec, 4, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, ComponentType, Q> call(ComponentType (*Func) (ComponentType x, ComponentType y), vec<4, ComponentType, Q> const& a, ComponentType b)
		{
			return vec<4, ComponentType, Q>(Func(a.x, b), Func(a.y, b), Func(a.z, b), Func(a.w, b));
		}
	};

	template<length_t L, typename ComponentType, qualifier Q>
	struct functor2_vec_int {};

	template<typename ComponentType, qualifier Q>
	struct functor2_vec_int<1, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<1, int, Q> call(int (*Func) (ComponentType x, int y), vec<1, ComponentType, Q> const& a, vec<1, int, Q> const& b)
		{
			return vec<1, int, Q>(Func(a.x, b.x));
		}
	};

	template<typename ComponentType, qualifier Q>
	struct functor2_vec_int<2, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<2, int, Q> call(int (*Func) (ComponentType x, int y), vec<2, ComponentType, Q> const& a, vec<2, int, Q> const& b)
		{
			return vec<2, int, Q>(Func(a.x, b.x), Func(a.y, b.y));
		}
	};

	template<typename ComponentType, qualifier Q>
	struct functor2_vec_int<3, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<3, int, Q> call(int (*Func) (ComponentType x, int y), vec<3, ComponentType, Q> const& a, vec<3, int, Q> const& b)
		{
			return vec<3, int, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z));
		}
	};

	template<typename ComponentType, qualifier Q>
	struct functor2_vec_int<4, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, int, Q> call(int (*Func) (ComponentType x, int y), vec<4, ComponentType, Q> const& a, vec<4, int, Q> const& b)
		{
			return vec<4, int, Q>(Func(a.x, b.x), Func(a.y, b.y), Func(a.z, b.z), Func(a.w, b.w));
		}
	};
}//namespace detail
}//namespace glm
