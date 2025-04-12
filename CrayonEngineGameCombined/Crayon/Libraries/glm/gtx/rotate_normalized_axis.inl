/// @ref gtx_rotate_normalized_axis

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> rotateNormalizedAxis
	(
		mat<4, 4, ComponentType, Q> const& m,
		ComponentType const& angle,
		vec<3, ComponentType, Q> const& v
	)
	{
		ComponentType const a = angle;
		ComponentType const c = cos(a);
		ComponentType const s = sin(a);

		vec<3, ComponentType, Q> const axis(v);

		vec<3, ComponentType, Q> const temp((static_cast<ComponentType>(1) - c) * axis);

		mat<4, 4, ComponentType, Q> Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		mat<4, 4, ComponentType, Q> Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> rotateNormalizedAxis
	(
		qua<ComponentType, Q> const& q,
		ComponentType const& angle,
		vec<3, ComponentType, Q> const& v
	)
	{
		vec<3, ComponentType, Q> const Tmp(v);

		ComponentType const AngleRad(angle);
		ComponentType const Sin = sin(AngleRad * ComponentType(0.5));

		return q * qua<ComponentType, Q>(cos(AngleRad * static_cast<ComponentType>(0.5)), Tmp.x * Sin, Tmp.y * Sin, Tmp.z * Sin);
		//return gtc::quaternion::cross(q, tquat<ComponentType, Q>(cos(AngleRad * ComponentType(0.5)), Tmp.x * fSin, Tmp.y * fSin, Tmp.z * fSin));
	}
}//namespace glm
