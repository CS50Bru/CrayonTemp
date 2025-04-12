/// @ref gtx_common

#include <cmath>
#include "../gtc/epsilon.hpp"
#include "../gtc/constants.hpp"

namespace glm{
namespace detail
{
	template<length_t L, typename ComponentType, qualifier Q, bool isFloat = true>
	struct compute_fmod
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, ComponentType, Q> const& a, vec<L, ComponentType, Q> const& b)
		{
			return detail::functor2<vec, L, ComponentType, Q>::call(std::fmod, a, b);
		}
	};

	template<length_t L, typename ComponentType, qualifier Q>
	struct compute_fmod<L, ComponentType, Q, false>
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, ComponentType, Q> const& a, vec<L, ComponentType, Q> const& b)
		{
			return a % b;
		}
	};
}//namespace detail

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER bool isdenormal(ComponentType const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'isdenormal' only accept floating-point inputs");

#		if GLM_HAS_CXX11_STL
			return std::fpclassify(x) == FP_SUBNORMAL;
#		else
			return epsilonNotEqual(x, static_cast<T>(0), epsilon<T>()) && std::fabs(x) < std::numeric_limits<T>::min();
#		endif
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER typename vec<1, ComponentType, Q>::bool_type isdenormal
	(
		vec<1, ComponentType, Q> const& x
	)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'isdenormal' only accept floating-point inputs");

		return typename vec<1, ComponentType, Q>::bool_type(
			isdenormal(x.x));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER typename vec<2, ComponentType, Q>::bool_type isdenormal
	(
		vec<2, ComponentType, Q> const& x
	)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'isdenormal' only accept floating-point inputs");

		return typename vec<2, ComponentType, Q>::bool_type(
			isdenormal(x.x),
			isdenormal(x.y));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER typename vec<3, ComponentType, Q>::bool_type isdenormal
	(
		vec<3, ComponentType, Q> const& x
	)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'isdenormal' only accept floating-point inputs");

		return typename vec<3, ComponentType, Q>::bool_type(
			isdenormal(x.x),
			isdenormal(x.y),
			isdenormal(x.z));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER typename vec<4, ComponentType, Q>::bool_type isdenormal
	(
		vec<4, ComponentType, Q> const& x
	)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'isdenormal' only accept floating-point inputs");

		return typename vec<4, ComponentType, Q>::bool_type(
			isdenormal(x.x),
			isdenormal(x.y),
			isdenormal(x.z),
			isdenormal(x.w));
	}

	// fmod
	template<typename genType>
	GLM_FUNC_QUALIFIER genType fmod(genType x, genType y)
	{
		return fmod(vec<1, genType>(x), y).x;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmod(vec<L, ComponentType, Q> const& x, ComponentType y)
	{
		return detail::compute_fmod<L, ComponentType, Q, std::numeric_limits<ComponentType>::is_iec559>::call(x, vec<L, ComponentType, Q>(y));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmod(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& y)
	{
		return detail::compute_fmod<L, ComponentType, Q, std::numeric_limits<ComponentType>::is_iec559>::call(x, y);
	}

	template <length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> openBounded(vec<L, ComponentType, Q> const& Value, vec<L, ComponentType, Q> const& Min, vec<L, ComponentType, Q> const& Max)
	{
		return greaterThan(Value, Min) && lessThan(Value, Max);
	}

	template <length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> closeBounded(vec<L, ComponentType, Q> const& Value, vec<L, ComponentType, Q> const& Min, vec<L, ComponentType, Q> const& Max)
	{
		return greaterThanEqual(Value, Min) && lessThanEqual(Value, Max);
	}
}//namespace glm
