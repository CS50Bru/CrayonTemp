/// @ref gtx_fast_trigonometry

namespace glm{
namespace detail
{
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> taylorCos(vec<L, ComponentType, Q> const& x)
	{
		return static_cast<ComponentType>(1)
			- (x * x) * (1.f / 2.f)
			+ ((x * x) * (x * x)) * (1.f / 24.f)
			- (((x * x) * (x * x)) * (x * x)) * (1.f / 720.f)
			+ (((x * x) * (x * x)) * ((x * x) * (x * x))) * (1.f / 40320.f);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType cos_52s(ComponentType x)
	{
		ComponentType const xx(x * x);
		return (ComponentType(0.9999932946) + xx * (ComponentType(-0.4999124376) + xx * (ComponentType(0.0414877472) + xx * ComponentType(-0.0012712095))));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> cos_52s(vec<L, ComponentType, Q> const& x)
	{
		return detail::functor1<vec, L, ComponentType, ComponentType, Q>::call(cos_52s, x);
	}
}//namespace detail

	// wrapAngle
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType wrapAngle(ComponentType angle)
	{
		return abs<ComponentType>(mod<ComponentType>(angle, two_pi<ComponentType>()));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> wrapAngle(vec<L, ComponentType, Q> const& x)
	{
		return detail::functor1<vec, L, ComponentType, ComponentType, Q>::call(wrapAngle, x);
	}

	// cos
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType fastCos(ComponentType x)
	{
		ComponentType const angle(wrapAngle<ComponentType>(x));

		if(angle < half_pi<ComponentType>())
			return detail::cos_52s(angle);
		if(angle < pi<ComponentType>())
			return -detail::cos_52s(pi<ComponentType>() - angle);
		if(angle < (ComponentType(3) * half_pi<ComponentType>()))
			return -detail::cos_52s(angle - pi<ComponentType>());

		return detail::cos_52s(two_pi<ComponentType>() - angle);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fastCos(vec<L, ComponentType, Q> const& x)
	{
		return detail::functor1<vec, L, ComponentType, ComponentType, Q>::call(fastCos, x);
	}

	// sin
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType fastSin(ComponentType x)
	{
		return fastCos<ComponentType>(half_pi<ComponentType>() - x);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fastSin(vec<L, ComponentType, Q> const& x)
	{
		return detail::functor1<vec, L, ComponentType, ComponentType, Q>::call(fastSin, x);
	}

	// tan
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType fastTan(ComponentType x)
	{
		return x + (x * x * x * ComponentType(0.3333333333)) + (x * x * x * x * x * ComponentType(0.1333333333333)) + (x * x * x * x * x * x * x * ComponentType(0.0539682539));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fastTan(vec<L, ComponentType, Q> const& x)
	{
		return detail::functor1<vec, L, ComponentType, ComponentType, Q>::call(fastTan, x);
	}

	// asin
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType fastAsin(ComponentType x)
	{
		return x + (x * x * x * ComponentType(0.166666667)) + (x * x * x * x * x * ComponentType(0.075)) + (x * x * x * x * x * x * x * ComponentType(0.0446428571)) + (x * x * x * x * x * x * x * x * x * ComponentType(0.0303819444));// + (x * x * x * x * x * x * x * x * x * x * x * ComponentType(0.022372159));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fastAsin(vec<L, ComponentType, Q> const& x)
	{
		return detail::functor1<vec, L, ComponentType, ComponentType, Q>::call(fastAsin, x);
	}

	// acos
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType fastAcos(ComponentType x)
	{
		return ComponentType(1.5707963267948966192313216916398) - fastAsin(x); //(PI / 2)
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fastAcos(vec<L, ComponentType, Q> const& x)
	{
		return detail::functor1<vec, L, ComponentType, ComponentType, Q>::call(fastAcos, x);
	}

	// atan
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType fastAtan(ComponentType y, ComponentType x)
	{
		ComponentType sgn = sign(y) * sign(x);
		return abs(fastAtan(y / x)) * sgn;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fastAtan(vec<L, ComponentType, Q> const& y, vec<L, ComponentType, Q> const& x)
	{
		return detail::functor2<vec, L, ComponentType, Q>::call(fastAtan, y, x);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType fastAtan(ComponentType x)
	{
		return x - (x * x * x * ComponentType(0.333333333333)) + (x * x * x * x * x * ComponentType(0.2)) - (x * x * x * x * x * x * x * ComponentType(0.1428571429)) + (x * x * x * x * x * x * x * x * x * ComponentType(0.111111111111)) - (x * x * x * x * x * x * x * x * x * x * x * ComponentType(0.0909090909));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fastAtan(vec<L, ComponentType, Q> const& x)
	{
		return detail::functor1<vec, L, ComponentType, ComponentType, Q>::call(fastAtan, x);
	}
}//namespace glm
