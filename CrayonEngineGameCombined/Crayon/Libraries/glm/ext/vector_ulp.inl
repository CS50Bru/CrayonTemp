namespace glm
{
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> nextFloat(vec<L, ComponentType, Q> const& x)
	{
		vec<L, ComponentType, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = nextFloat(x[i]);
		return Result;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> nextFloat(vec<L, ComponentType, Q> const& x, int ULPs)
	{
		vec<L, ComponentType, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = nextFloat(x[i], ULPs);
		return Result;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> nextFloat(vec<L, ComponentType, Q> const& x, vec<L, int, Q> const& ULPs)
	{
		vec<L, ComponentType, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = nextFloat(x[i], ULPs[i]);
		return Result;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> prevFloat(vec<L, ComponentType, Q> const& x)
	{
		vec<L, ComponentType, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = prevFloat(x[i]);
		return Result;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> prevFloat(vec<L, ComponentType, Q> const& x, int ULPs)
	{
		vec<L, ComponentType, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = prevFloat(x[i], ULPs);
		return Result;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> prevFloat(vec<L, ComponentType, Q> const& x, vec<L, int, Q> const& ULPs)
	{
		vec<L, ComponentType, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = prevFloat(x[i], ULPs[i]);
		return Result;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, int, Q> floatDistance(vec<L, float, Q> const& x, vec<L, float, Q> const& y)
	{
		vec<L, int, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = floatDistance(x[i], y[i]);
		return Result;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, int64, Q> floatDistance(vec<L, double, Q> const& x, vec<L, double, Q> const& y)
	{
		vec<L, int64, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = floatDistance(x[i], y[i]);
		return Result;
	}
}//namespace glm
