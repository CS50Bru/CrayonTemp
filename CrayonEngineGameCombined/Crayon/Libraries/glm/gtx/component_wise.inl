/// @ref gtx_component_wise

#include <limits>

namespace glm{
namespace detail
{
	template<length_t L, typename ComponentType, typename floatType, qualifier Q, bool isInteger, bool signedType>
	struct compute_compNormalize
	{};

	template<length_t L, typename ComponentType, typename floatType, qualifier Q>
	struct compute_compNormalize<L, ComponentType, floatType, Q, true, true>
	{
		GLM_FUNC_QUALIFIER static vec<L, floatType, Q> call(vec<L, ComponentType, Q> const& v)
		{
			floatType const Min = static_cast<floatType>(std::numeric_limits<ComponentType>::min());
			floatType const Max = static_cast<floatType>(std::numeric_limits<ComponentType>::max());
			return (vec<L, floatType, Q>(v) - Min) / (Max - Min) * static_cast<floatType>(2) - static_cast<floatType>(1);
		}
	};

	template<length_t L, typename ComponentType, typename floatType, qualifier Q>
	struct compute_compNormalize<L, ComponentType, floatType, Q, true, false>
	{
		GLM_FUNC_QUALIFIER static vec<L, floatType, Q> call(vec<L, ComponentType, Q> const& v)
		{
			return vec<L, floatType, Q>(v) / static_cast<floatType>(std::numeric_limits<ComponentType>::max());
		}
	};

	template<length_t L, typename ComponentType, typename floatType, qualifier Q>
	struct compute_compNormalize<L, ComponentType, floatType, Q, false, true>
	{
		GLM_FUNC_QUALIFIER static vec<L, floatType, Q> call(vec<L, ComponentType, Q> const& v)
		{
			return v;
		}
	};

	template<length_t L, typename ComponentType, typename floatType, qualifier Q, bool isInteger, bool signedType>
	struct compute_compScale
	{};

	template<length_t L, typename ComponentType, typename floatType, qualifier Q>
	struct compute_compScale<L, ComponentType, floatType, Q, true, true>
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, floatType, Q> const& v)
		{
			floatType const Max = static_cast<floatType>(std::numeric_limits<ComponentType>::max()) + static_cast<floatType>(0.5);
			vec<L, floatType, Q> const Scaled(v * Max);
			vec<L, ComponentType, Q> const Result(Scaled - static_cast<floatType>(0.5));
			return Result;
		}
	};

	template<length_t L, typename ComponentType, typename floatType, qualifier Q>
	struct compute_compScale<L, ComponentType, floatType, Q, true, false>
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, floatType, Q> const& v)
		{
			return vec<L, ComponentType, Q>(vec<L, floatType, Q>(v) * static_cast<floatType>(std::numeric_limits<ComponentType>::max()));
		}
	};

	template<length_t L, typename ComponentType, typename floatType, qualifier Q>
	struct compute_compScale<L, ComponentType, floatType, Q, false, true>
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, floatType, Q> const& v)
		{
			return v;
		}
	};
}//namespace detail

	template<typename floatType, length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, floatType, Q> compNormalize(vec<L, ComponentType, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<floatType>::is_iec559, "'compNormalize' accepts only floating-point types for 'floatType' template parameter");

		return detail::compute_compNormalize<L, ComponentType, floatType, Q, std::numeric_limits<ComponentType>::is_integer, std::numeric_limits<ComponentType>::is_signed>::call(v);
	}

	template<typename ComponentType, length_t L, typename floatType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> compScale(vec<L, floatType, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<floatType>::is_iec559, "'compScale' accepts only floating-point types for 'floatType' template parameter");

		return detail::compute_compScale<L, ComponentType, floatType, Q, std::numeric_limits<ComponentType>::is_integer, std::numeric_limits<ComponentType>::is_signed>::call(v);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType compAdd(vec<L, ComponentType, Q> const& v)
	{
		ComponentType Result(0);
		for(length_t i = 0, n = v.length(); i < n; ++i)
			Result += v[i];
		return Result;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType compMul(vec<L, ComponentType, Q> const& v)
	{
		ComponentType Result(1);
		for(length_t i = 0, n = v.length(); i < n; ++i)
			Result *= v[i];
		return Result;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType compMin(vec<L, ComponentType, Q> const& v)
	{
		ComponentType Result(v[0]);
		for(length_t i = 1, n = v.length(); i < n; ++i)
			Result = min(Result, v[i]);
		return Result;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType compMax(vec<L, ComponentType, Q> const& v)
	{
		ComponentType Result(v[0]);
		for(length_t i = 1, n = v.length(); i < n; ++i)
			Result = max(Result, v[i]);
		return Result;
	}
}//namespace glm
