/// @ref gtx_rotate_vector

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> slerp
	(
		vec<3, ComponentType, Q> const& x,
		vec<3, ComponentType, Q> const& y,
		ComponentType const& a
	)
	{
		// get cosine of angle between vectors (-1 -> 1)
		ComponentType CosAlpha = dot(x, y);
		// get angle (0 -> pi)
		ComponentType Alpha = acos(CosAlpha);
		// get sine of angle between vectors (0 -> 1)
		ComponentType SinAlpha = sin(Alpha);
		// this breaks down when SinAlpha = 0, i.e. Alpha = 0 or pi
		ComponentType t1 = sin((static_cast<ComponentType>(1) - a) * Alpha) / SinAlpha;
		ComponentType t2 = sin(a * Alpha) / SinAlpha;

		// interpolate src vectors
		return x * t1 + y * t2;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<2, ComponentType, Q> rotate
	(
		vec<2, ComponentType, Q> const& v,
		ComponentType const& angle
	)
	{
		vec<2, ComponentType, Q> Result;
		ComponentType const Cos(cos(angle));
		ComponentType const Sin(sin(angle));

		Result.x = v.x * Cos - v.y * Sin;
		Result.y = v.x * Sin + v.y * Cos;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rotate
	(
		vec<3, ComponentType, Q> const& v,
		ComponentType const& angle,
		vec<3, ComponentType, Q> const& normal
	)
	{
		return mat<3, 3, ComponentType, Q>(glm::rotate(angle, normal)) * v;
	}
	/*
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rotateGTX(
		const vec<3, ComponentType, Q>& x,
		ComponentType angle,
		const vec<3, ComponentType, Q>& normal)
	{
		const ComponentType Cos = cos(radians(angle));
		const ComponentType Sin = sin(radians(angle));
		return x * Cos + ((x * normal) * (ComponentType(1) - Cos)) * normal + cross(x, normal) * Sin;
	}
	*/
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> rotate
	(
		vec<4, ComponentType, Q> const& v,
		ComponentType const& angle,
		vec<3, ComponentType, Q> const& normal
	)
	{
		return rotate(angle, normal) * v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rotateX
	(
		vec<3, ComponentType, Q> const& v,
		ComponentType const& angle
	)
	{
		vec<3, ComponentType, Q> Result(v);
		ComponentType const Cos(cos(angle));
		ComponentType const Sin(sin(angle));

		Result.y = v.y * Cos - v.z * Sin;
		Result.z = v.y * Sin + v.z * Cos;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rotateY
	(
		vec<3, ComponentType, Q> const& v,
		ComponentType const& angle
	)
	{
		vec<3, ComponentType, Q> Result = v;
		ComponentType const Cos(cos(angle));
		ComponentType const Sin(sin(angle));

		Result.x =  v.x * Cos + v.z * Sin;
		Result.z = -v.x * Sin + v.z * Cos;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rotateZ
	(
		vec<3, ComponentType, Q> const& v,
		ComponentType const& angle
	)
	{
		vec<3, ComponentType, Q> Result = v;
		ComponentType const Cos(cos(angle));
		ComponentType const Sin(sin(angle));

		Result.x = v.x * Cos - v.y * Sin;
		Result.y = v.x * Sin + v.y * Cos;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> rotateX
	(
		vec<4, ComponentType, Q> const& v,
		ComponentType const& angle
	)
	{
		vec<4, ComponentType, Q> Result = v;
		ComponentType const Cos(cos(angle));
		ComponentType const Sin(sin(angle));

		Result.y = v.y * Cos - v.z * Sin;
		Result.z = v.y * Sin + v.z * Cos;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> rotateY
	(
		vec<4, ComponentType, Q> const& v,
		ComponentType const& angle
	)
	{
		vec<4, ComponentType, Q> Result = v;
		ComponentType const Cos(cos(angle));
		ComponentType const Sin(sin(angle));

		Result.x =  v.x * Cos + v.z * Sin;
		Result.z = -v.x * Sin + v.z * Cos;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> rotateZ
	(
		vec<4, ComponentType, Q> const& v,
		ComponentType const& angle
	)
	{
		vec<4, ComponentType, Q> Result = v;
		ComponentType const Cos(cos(angle));
		ComponentType const Sin(sin(angle));

		Result.x = v.x * Cos - v.y * Sin;
		Result.y = v.x * Sin + v.y * Cos;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> orientation
	(
		vec<3, ComponentType, Q> const& Normal,
		vec<3, ComponentType, Q> const& Up
	)
	{
		if(all(equal(Normal, Up, epsilon<ComponentType>())))
			return mat<4, 4, ComponentType, Q>(static_cast<ComponentType>(1));

		vec<3, ComponentType, Q> RotationAxis = cross(Up, Normal);
		ComponentType Angle = acos(dot(Normal, Up));

		return rotate(Angle, RotationAxis);
	}
}//namespace glm
