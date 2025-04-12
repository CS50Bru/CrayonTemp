namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> equal(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] == y[i];
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> equal(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType epsilon)
	{
		vec<4, ComponentType, Q> v(x.x - y.x, x.y - y.y, x.z - y.z, x.w - y.w);
		return lessThan(abs(v), vec<4, ComponentType, Q>(epsilon));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> notEqual(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] != y[i];
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> notEqual(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType epsilon)
	{
		vec<4, ComponentType, Q> v(x.x - y.x, x.y - y.y, x.z - y.z, x.w - y.w);
		return greaterThanEqual(abs(v), vec<4, ComponentType, Q>(epsilon));
	}
}//namespace glm

