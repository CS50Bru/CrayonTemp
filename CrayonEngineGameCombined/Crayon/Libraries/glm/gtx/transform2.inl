/// @ref gtx_transform2

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> shearX2D(mat<3, 3, ComponentType, Q> const& m, ComponentType s)
	{
		mat<3, 3, ComponentType, Q> r(1);
		r[1][0] = s;
		return m * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> shearY2D(mat<3, 3, ComponentType, Q> const& m, ComponentType s)
	{
		mat<3, 3, ComponentType, Q> r(1);
		r[0][1] = s;
		return m * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> shearX3D(mat<4, 4, ComponentType, Q> const& m, ComponentType s, ComponentType t)
	{
		mat<4, 4, ComponentType, Q> r(1);
		r[0][1] = s;
		r[0][2] = t;
		return m * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> shearY3D(mat<4, 4, ComponentType, Q> const& m, ComponentType s, ComponentType t)
	{
		mat<4, 4, ComponentType, Q> r(1);
		r[1][0] = s;
		r[1][2] = t;
		return m * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> shearZ3D(mat<4, 4, ComponentType, Q> const& m, ComponentType s, ComponentType t)
	{
		mat<4, 4, ComponentType, Q> r(1);
		r[2][0] = s;
		r[2][1] = t;
		return m * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> reflect2D(mat<3, 3, ComponentType, Q> const& m, vec<3, ComponentType, Q> const& normal)
	{
		mat<3, 3, ComponentType, Q> r(static_cast<ComponentType>(1));
		r[0][0] = static_cast<ComponentType>(1) - static_cast<ComponentType>(2) * normal.x * normal.x;
		r[0][1] = -static_cast<ComponentType>(2) * normal.x * normal.y;
		r[1][0] = -static_cast<ComponentType>(2) * normal.x * normal.y;
		r[1][1] = static_cast<ComponentType>(1) - static_cast<ComponentType>(2) * normal.y * normal.y;
		return m * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> reflect3D(mat<4, 4, ComponentType, Q> const& m, vec<3, ComponentType, Q> const& normal)
	{
		mat<4, 4, ComponentType, Q> r(static_cast<ComponentType>(1));
		r[0][0] = static_cast<ComponentType>(1) - static_cast<ComponentType>(2) * normal.x * normal.x;
		r[0][1] = -static_cast<ComponentType>(2) * normal.x * normal.y;
		r[0][2] = -static_cast<ComponentType>(2) * normal.x * normal.z;

		r[1][0] = -static_cast<ComponentType>(2) * normal.x * normal.y;
		r[1][1] = static_cast<ComponentType>(1) - static_cast<ComponentType>(2) * normal.y * normal.y;
		r[1][2] = -static_cast<ComponentType>(2) * normal.y * normal.z;

		r[2][0] = -static_cast<ComponentType>(2) * normal.x * normal.z;
		r[2][1] = -static_cast<ComponentType>(2) * normal.y * normal.z;
		r[2][2] = static_cast<ComponentType>(1) - static_cast<ComponentType>(2) * normal.z * normal.z;
		return m * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> proj2D(
		const mat<3, 3, ComponentType, Q>& m,
		const vec<3, ComponentType, Q>& normal)
	{
		mat<3, 3, ComponentType, Q> r(static_cast<ComponentType>(1));
		r[0][0] = static_cast<ComponentType>(1) - normal.x * normal.x;
		r[0][1] = - normal.x * normal.y;
		r[1][0] = - normal.x * normal.y;
		r[1][1] = static_cast<ComponentType>(1) - normal.y * normal.y;
		return m * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> proj3D(
		const mat<4, 4, ComponentType, Q>& m,
		const vec<3, ComponentType, Q>& normal)
	{
		mat<4, 4, ComponentType, Q> r(static_cast<ComponentType>(1));
		r[0][0] = static_cast<ComponentType>(1) - normal.x * normal.x;
		r[0][1] = - normal.x * normal.y;
		r[0][2] = - normal.x * normal.z;
		r[1][0] = - normal.x * normal.y;
		r[1][1] = static_cast<ComponentType>(1) - normal.y * normal.y;
		r[1][2] = - normal.y * normal.z;
		r[2][0] = - normal.x * normal.z;
		r[2][1] = - normal.y * normal.z;
		r[2][2] = static_cast<ComponentType>(1) - normal.z * normal.z;
		return m * r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> scaleBias(ComponentType scale, ComponentType bias)
	{
		mat<4, 4, ComponentType, Q> result;
		result[3] = vec<4, ComponentType, Q>(vec<3, ComponentType, Q>(bias), static_cast<ComponentType>(1));
		result[0][0] = scale;
		result[1][1] = scale;
		result[2][2] = scale;
		return result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> scaleBias(mat<4, 4, ComponentType, Q> const& m, ComponentType scale, ComponentType bias)
	{
		return m * scaleBias(scale, bias);
	}
}//namespace glm

