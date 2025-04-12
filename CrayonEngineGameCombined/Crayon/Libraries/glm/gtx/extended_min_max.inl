/// @ref gtx_extended_min_max

namespace glm
{
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType min(
		ComponentType const& x,
		ComponentType const& y,
		ComponentType const& z)
	{
		return glm::min(glm::min(x, y), z);
	}

	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_QUALIFIER C<ComponentType> min
	(
		C<ComponentType> const& x,
		typename C<ComponentType>::ComponentType const& y,
		typename C<ComponentType>::ComponentType const& z
	)
	{
		return glm::min(glm::min(x, y), z);
	}

	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_QUALIFIER C<ComponentType> min
	(
		C<ComponentType> const& x,
		C<ComponentType> const& y,
		C<ComponentType> const& z
	)
	{
		return glm::min(glm::min(x, y), z);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType min
	(
		ComponentType const& x,
		ComponentType const& y,
		ComponentType const& z,
		ComponentType const& w
	)
	{
		return glm::min(glm::min(x, y), glm::min(z, w));
	}

	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_QUALIFIER C<ComponentType> min
	(
		C<ComponentType> const& x,
		typename C<ComponentType>::ComponentType const& y,
		typename C<ComponentType>::ComponentType const& z,
		typename C<ComponentType>::ComponentType const& w
	)
	{
		return glm::min(glm::min(x, y), glm::min(z, w));
	}

	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_QUALIFIER C<ComponentType> min
	(
		C<ComponentType> const& x,
		C<ComponentType> const& y,
		C<ComponentType> const& z,
		C<ComponentType> const& w
	)
	{
		return glm::min(glm::min(x, y), glm::min(z, w));
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType max(
		ComponentType const& x,
		ComponentType const& y,
		ComponentType const& z)
	{
		return glm::max(glm::max(x, y), z);
	}

	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_QUALIFIER C<ComponentType> max
	(
		C<ComponentType> const& x,
		typename C<ComponentType>::ComponentType const& y,
		typename C<ComponentType>::ComponentType const& z
	)
	{
		return glm::max(glm::max(x, y), z);
	}

	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_QUALIFIER C<ComponentType> max
	(
		C<ComponentType> const& x,
		C<ComponentType> const& y,
		C<ComponentType> const& z
	)
	{
		return glm::max(glm::max(x, y), z);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType max
	(
		ComponentType const& x,
		ComponentType const& y,
		ComponentType const& z,
		ComponentType const& w
	)
	{
		return glm::max(glm::max(x, y), glm::max(z, w));
	}

	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_QUALIFIER C<ComponentType> max
	(
		C<ComponentType> const& x,
		typename C<ComponentType>::ComponentType const& y,
		typename C<ComponentType>::ComponentType const& z,
		typename C<ComponentType>::ComponentType const& w
	)
	{
		return glm::max(glm::max(x, y), glm::max(z, w));
	}

	template<typename ComponentType, template<typename> class C>
	GLM_FUNC_QUALIFIER C<ComponentType> max
	(
		C<ComponentType> const& x,
		C<ComponentType> const& y,
		C<ComponentType> const& z,
		C<ComponentType> const& w
	)
	{
		return glm::max(glm::max(x, y), glm::max(z, w));
	}

	// fmin
#	if GLM_HAS_CXX11_STL
		using std::fmin;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER genType fmin(genType x, genType y)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'fmin' only accept floating-point input");

			if (isnan(x))
				return y;
			if (isnan(y))
				return x;

			return min(x, y);
		}
#	endif

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmin(vec<L, ComponentType, Q> const& a, ComponentType b)
	{
		return detail::functor2<vec, L, ComponentType, Q>::call(fmin, a, vec<L, ComponentType, Q>(b));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmin(vec<L, ComponentType, Q> const& a, vec<L, ComponentType, Q> const& b)
	{
		return detail::functor2<vec, L, ComponentType, Q>::call(fmin, a, b);
	}

	// fmax
#	if GLM_HAS_CXX11_STL
		using std::fmax;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER genType fmax(genType x, genType y)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'fmax' only accept floating-point input");

			if (isnan(x))
				return y;
			if (isnan(y))
				return x;

			return max(x, y);
		}
#	endif

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmax(vec<L, ComponentType, Q> const& a, ComponentType b)
	{
		return detail::functor2<vec, L, ComponentType, Q>::call(fmax, a, vec<L, ComponentType, Q>(b));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fmax(vec<L, ComponentType, Q> const& a, vec<L, ComponentType, Q> const& b)
	{
		return detail::functor2<vec, L, ComponentType, Q>::call(fmax, a, b);
	}

	// fclamp
	template<typename genType>
	GLM_FUNC_QUALIFIER genType fclamp(genType x, genType minVal, genType maxVal)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'fclamp' only accept floating-point or integer inputs");
		return fmin(fmax(x, minVal), maxVal);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fclamp(vec<L, ComponentType, Q> const& x, ComponentType minVal, ComponentType maxVal)
	{
		return fmin(fmax(x, vec<L, ComponentType, Q>(minVal)), vec<L, ComponentType, Q>(maxVal));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> fclamp(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& minVal, vec<L, ComponentType, Q> const& maxVal)
	{
		return fmin(fmax(x, minVal), maxVal);
	}
}//namespace glm
