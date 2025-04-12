/// @ref gtx_norm

#include "../detail/qualifier.hpp"

namespace glm{
namespace detail
{
	template<length_t L, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_length2
	{
		GLM_FUNC_QUALIFIER static ComponentType call(vec<L, ComponentType, Q> const& v)
		{
			return dot(v, v);
		}
	};
}//namespace detail

	template<typename genType>
	GLM_FUNC_QUALIFIER genType length2(genType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'length2' accepts only floating-point inputs");
		return x * x;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType length2(vec<L, ComponentType, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'length2' accepts only floating-point inputs");
		return detail::compute_length2<L, ComponentType, Q, detail::is_aligned<Q>::value>::call(v);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType distance2(ComponentType p0, ComponentType p1)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'distance2' accepts only floating-point inputs");
		return length2(p1 - p0);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType distance2(vec<L, ComponentType, Q> const& p0, vec<L, ComponentType, Q> const& p1)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'distance2' accepts only floating-point inputs");
		return length2(p1 - p0);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType l1Norm(vec<3, ComponentType, Q> const& a, vec<3, ComponentType, Q> const& b)
	{
		return abs(b.x - a.x) + abs(b.y - a.y) + abs(b.z - a.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType l1Norm(vec<3, ComponentType, Q> const& v)
	{
		return abs(v.x) + abs(v.y) + abs(v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType l2Norm(vec<3, ComponentType, Q> const& a, vec<3, ComponentType, Q> const& b
	)
	{
		return length(b - a);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType l2Norm(vec<3, ComponentType, Q> const& v)
	{
		return length(v);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType lxNorm(vec<3, ComponentType, Q> const& x, vec<3, ComponentType, Q> const& y, unsigned int Depth)
	{
		return pow(pow(abs(y.x - x.x), ComponentType(Depth)) + pow(abs(y.y - x.y), ComponentType(Depth)) + pow(abs(y.z - x.z), ComponentType(Depth)), ComponentType(1) / ComponentType(Depth));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType lxNorm(vec<3, ComponentType, Q> const& v, unsigned int Depth)
	{
		return pow(pow(abs(v.x), ComponentType(Depth)) + pow(abs(v.y), ComponentType(Depth)) + pow(abs(v.z), ComponentType(Depth)), ComponentType(1) / ComponentType(Depth));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType lMaxNorm(vec<3, ComponentType, Q> const& a, vec<3, ComponentType, Q> const& b)
	{
		return compMax(abs(b - a));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType lMaxNorm(vec<3, ComponentType, Q> const& v)
	{
		return compMax(abs(v));
	}

}//namespace glm
