#include "../detail/_vectorize.hpp"

namespace glm
{
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, ComponentType, Q> min(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& y, vec<L, ComponentType, Q> const& z)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'min' only accept floating-point or integer inputs");
		return glm::min(glm::min(x, y), z);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, ComponentType, Q> min(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& y, vec<L, ComponentType, Q> const& z, vec<L, ComponentType, Q> const& w)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'min' only accept floating-point or integer inputs");
		return glm::min(glm::min(x, y), glm::min(z, w));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, ComponentType, Q> max(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& y, vec<L, ComponentType, Q> const& z)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'max' only accept floating-point or integer inputs");
		return glm::max(glm::max(x, y), z);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<L, ComponentType, Q> max(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& y, vec<L, ComponentType, Q> const& z, vec<L, ComponentType, Q> const& w)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'max' only accept floating-point or integer inputs");
		return glm::max(glm::max(x, y), glm::max(z, w));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmin(vec<L, ComponentType, Q> const& a, ComponentType b)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'fmin' only accept floating-point inputs");
		return detail::functor2<vec, L, ComponentType, Q>::call(fmin, a, vec<L, ComponentType, Q>(b));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmin(vec<L, ComponentType, Q> const& a, vec<L, ComponentType, Q> const& b)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'fmin' only accept floating-point inputs");
		return detail::functor2<vec, L, ComponentType, Q>::call(fmin, a, b);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmin(vec<L, ComponentType, Q> const& a, vec<L, ComponentType, Q> const& b, vec<L, ComponentType, Q> const& c)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'fmin' only accept floating-point inputs");
		return fmin(fmin(a, b), c);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmin(vec<L, ComponentType, Q> const& a, vec<L, ComponentType, Q> const& b, vec<L, ComponentType, Q> const& c, vec<L, ComponentType, Q> const& d)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'fmin' only accept floating-point inputs");
		return fmin(fmin(a, b), fmin(c, d));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmax(vec<L, ComponentType, Q> const& a, ComponentType b)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'fmax' only accept floating-point inputs");
		return detail::functor2<vec, L, ComponentType, Q>::call(fmax, a, vec<L, ComponentType, Q>(b));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmax(vec<L, ComponentType, Q> const& a, vec<L, ComponentType, Q> const& b)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'fmax' only accept floating-point inputs");
		return detail::functor2<vec, L, ComponentType, Q>::call(fmax, a, b);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmax(vec<L, ComponentType, Q> const& a, vec<L, ComponentType, Q> const& b, vec<L, ComponentType, Q> const& c)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'fmax' only accept floating-point inputs");
		return fmax(fmax(a, b), c);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmax(vec<L, ComponentType, Q> const& a, vec<L, ComponentType, Q> const& b, vec<L, ComponentType, Q> const& c, vec<L, ComponentType, Q> const& d)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'fmax' only accept floating-point inputs");
		return fmax(fmax(a, b), fmax(c, d));
	}
}//namespace glm
