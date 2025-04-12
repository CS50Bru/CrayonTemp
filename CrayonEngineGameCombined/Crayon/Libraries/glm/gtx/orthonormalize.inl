/// @ref gtx_orthonormalize

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> orthonormalize(mat<3, 3, ComponentType, Q> const& m)
	{
		mat<3, 3, ComponentType, Q> r = m;

		r[0] = normalize(r[0]);

		ComponentType d0 = dot(r[0], r[1]);
		r[1] -= r[0] * d0;
		r[1] = normalize(r[1]);

		ComponentType d1 = dot(r[1], r[2]);
		d0 = dot(r[0], r[2]);
		r[2] -= r[0] * d0 + r[1] * d1;
		r[2] = normalize(r[2]);

		return r;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> orthonormalize(vec<3, ComponentType, Q> const& x, vec<3, ComponentType, Q> const& y)
	{
		return normalize(x - y * dot(y, x));
	}
}//namespace glm
