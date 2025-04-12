/// @ref ext_vector_relational
/// @file glm/ext/vector_relational.inl

// Dependency:
#include "../ext/vector_relational.hpp"
#include "../common.hpp"

namespace glm
{
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<C, bool, Q> equal(mat<C, R, ComponentType, Q> const& a, mat<C, R, ComponentType, Q> const& b)
	{
		return equal(a, b, static_cast<ComponentType>(0));
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<C, bool, Q> equal(mat<C, R, ComponentType, Q> const& a, mat<C, R, ComponentType, Q> const& b, ComponentType Epsilon)
	{
		return equal(a, b, vec<C, ComponentType, Q>(Epsilon));
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<C, bool, Q> equal(mat<C, R, ComponentType, Q> const& a, mat<C, R, ComponentType, Q> const& b, vec<C, ComponentType, Q> const& Epsilon)
	{
		vec<C, bool, Q> Result(true);
		for(length_t i = 0; i < C; ++i)
			Result[i] = all(equal(a[i], b[i], Epsilon[i]));
		return Result;
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<C, bool, Q> notEqual(mat<C, R, ComponentType, Q> const& x, mat<C, R, ComponentType, Q> const& y)
	{
		return notEqual(x, y, static_cast<ComponentType>(0));
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<C, bool, Q> notEqual(mat<C, R, ComponentType, Q> const& x, mat<C, R, ComponentType, Q> const& y, ComponentType Epsilon)
	{
		return notEqual(x, y, vec<C, ComponentType, Q>(Epsilon));
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<C, bool, Q> notEqual(mat<C, R, ComponentType, Q> const& a, mat<C, R, ComponentType, Q> const& b, vec<C, ComponentType, Q> const& Epsilon)
	{
		vec<C, bool, Q> Result(true);
		for(length_t i = 0; i < C; ++i)
			Result[i] = any(notEqual(a[i], b[i], Epsilon[i]));
		return Result;
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<C, bool, Q> equal(mat<C, R, ComponentType, Q> const& a, mat<C, R, ComponentType, Q> const& b, int MaxULPs)
	{
		return equal(a, b, vec<C, int, Q>(MaxULPs));
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<C, bool, Q> equal(mat<C, R, ComponentType, Q> const& a, mat<C, R, ComponentType, Q> const& b, vec<C, int, Q> const& MaxULPs)
	{
		vec<C, bool, Q> Result(true);
		for(length_t i = 0; i < C; ++i)
			Result[i] = all(equal(a[i], b[i], MaxULPs[i]));
		return Result;
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<C, bool, Q> notEqual(mat<C, R, ComponentType, Q> const& x, mat<C, R, ComponentType, Q> const& y, int MaxULPs)
	{
		return notEqual(x, y, vec<C, int, Q>(MaxULPs));
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<C, bool, Q> notEqual(mat<C, R, ComponentType, Q> const& a, mat<C, R, ComponentType, Q> const& b, vec<C, int, Q> const& MaxULPs)
	{
		vec<C, bool, Q> Result(true);
		for(length_t i = 0; i < C; ++i)
			Result[i] = any(notEqual(a[i], b[i], MaxULPs[i]));
		return Result;
	}

}//namespace glm
