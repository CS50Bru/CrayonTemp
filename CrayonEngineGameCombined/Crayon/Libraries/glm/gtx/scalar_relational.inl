/// @ref gtx_scalar_relational

namespace glm
{
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER bool lessThan
	(
		ComponentType const& x,
		ComponentType const& y
	)
	{
		return x < y;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER bool lessThanEqual
	(
		ComponentType const& x,
		ComponentType const& y
	)
	{
		return x <= y;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER bool greaterThan
	(
		ComponentType const& x,
		ComponentType const& y
	)
	{
		return x > y;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER bool greaterThanEqual
	(
		ComponentType const& x,
		ComponentType const& y
	)
	{
		return x >= y;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER bool equal
	(
		ComponentType const& x,
		ComponentType const& y
	)
	{
		return detail::compute_equal<ComponentType, std::numeric_limits<ComponentType>::is_iec559>::call(x, y);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER bool notEqual
	(
		ComponentType const& x,
		ComponentType const& y
	)
	{
		return !detail::compute_equal<ComponentType, std::numeric_limits<ComponentType>::is_iec559>::call(x, y);
	}

	GLM_FUNC_QUALIFIER bool any
	(
		bool const& x
	)
	{
		return x;
	}

	GLM_FUNC_QUALIFIER bool all
	(
		bool const& x
	)
	{
		return x;
	}

	GLM_FUNC_QUALIFIER bool not_
	(
		bool const& x
	)
	{
		return !x;
	}
}//namespace glm
