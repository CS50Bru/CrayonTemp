#include "../trigonometric.hpp"
#include "../geometric.hpp"
#include "../exponential.hpp"
#include "epsilon.hpp"
#include <limits>

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> eulerAngles(qua<ComponentType, Q> const& x)
	{
		return vec<3, ComponentType, Q>(pitch(x), yaw(x), roll(x));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType roll(qua<ComponentType, Q> const& q)
	{
		return static_cast<ComponentType>(atan(static_cast<ComponentType>(2) * (q.x * q.y + q.w * q.z), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType pitch(qua<ComponentType, Q> const& q)
	{
		//return ComponentType(atan(ComponentType(2) * (q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z));
		ComponentType const y = static_cast<ComponentType>(2) * (q.y * q.z + q.w * q.x);
		ComponentType const x = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;

		if(all(equal(vec<2, ComponentType, Q>(x, y), vec<2, ComponentType, Q>(0), epsilon<ComponentType>()))) //avoid atan2(0,0) - handle singularity - Matiis
			return static_cast<ComponentType>(static_cast<ComponentType>(2) * atan(q.x, q.w));

		return static_cast<ComponentType>(atan(y, x));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType yaw(qua<ComponentType, Q> const& q)
	{
		return asin(clamp(static_cast<ComponentType>(-2) * (q.x * q.z - q.w * q.y), static_cast<ComponentType>(-1), static_cast<ComponentType>(1)));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> mat3_cast(qua<ComponentType, Q> const& q)
	{
		mat<3, 3, ComponentType, Q> Result(ComponentType(1));
		ComponentType qxx(q.x * q.x);
		ComponentType qyy(q.y * q.y);
		ComponentType qzz(q.z * q.z);
		ComponentType qxz(q.x * q.z);
		ComponentType qxy(q.x * q.y);
		ComponentType qyz(q.y * q.z);
		ComponentType qwx(q.w * q.x);
		ComponentType qwy(q.w * q.y);
		ComponentType qwz(q.w * q.z);

		Result[0][0] = ComponentType(1) - ComponentType(2) * (qyy +  qzz);
		Result[0][1] = ComponentType(2) * (qxy + qwz);
		Result[0][2] = ComponentType(2) * (qxz - qwy);

		Result[1][0] = ComponentType(2) * (qxy - qwz);
		Result[1][1] = ComponentType(1) - ComponentType(2) * (qxx +  qzz);
		Result[1][2] = ComponentType(2) * (qyz + qwx);

		Result[2][0] = ComponentType(2) * (qxz + qwy);
		Result[2][1] = ComponentType(2) * (qyz - qwx);
		Result[2][2] = ComponentType(1) - ComponentType(2) * (qxx +  qyy);
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> mat4_cast(qua<ComponentType, Q> const& q)
	{
		return mat<4, 4, ComponentType, Q>(mat3_cast(q));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> quat_cast(mat<3, 3, ComponentType, Q> const& m)
	{
		ComponentType fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
		ComponentType fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
		ComponentType fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
		ComponentType fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

		int biggestIndex = 0;
		ComponentType fourBiggestSquaredMinus1 = fourWSquaredMinus1;
		if(fourXSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if(fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if(fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		ComponentType biggestVal = sqrt(fourBiggestSquaredMinus1 + static_cast<ComponentType>(1)) * static_cast<ComponentType>(0.5);
		ComponentType mult = static_cast<ComponentType>(0.25) / biggestVal;

		switch(biggestIndex)
		{
		case 0:
			return qua<ComponentType, Q>(biggestVal, (m[1][2] - m[2][1]) * mult, (m[2][0] - m[0][2]) * mult, (m[0][1] - m[1][0]) * mult);
		case 1:
			return qua<ComponentType, Q>((m[1][2] - m[2][1]) * mult, biggestVal, (m[0][1] + m[1][0]) * mult, (m[2][0] + m[0][2]) * mult);
		case 2:
			return qua<ComponentType, Q>((m[2][0] - m[0][2]) * mult, (m[0][1] + m[1][0]) * mult, biggestVal, (m[1][2] + m[2][1]) * mult);
		case 3:
			return qua<ComponentType, Q>((m[0][1] - m[1][0]) * mult, (m[2][0] + m[0][2]) * mult, (m[1][2] + m[2][1]) * mult, biggestVal);
		default: // Silence a -Wswitch-default warning in GCC. Should never actually get here. Assert is just for sanity.
			assert(false);
			return qua<ComponentType, Q>(1, 0, 0, 0);
		}
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> quat_cast(mat<4, 4, ComponentType, Q> const& m4)
	{
		return quat_cast(mat<3, 3, ComponentType, Q>(m4));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> lessThan(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] < y[i];
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> lessThanEqual(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] <= y[i];
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> greaterThan(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] > y[i];
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> greaterThanEqual(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y)
	{
		vec<4, bool, Q> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = x[i] >= y[i];
		return Result;
	}


	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> quatLookAt(vec<3, ComponentType, Q> const& direction, vec<3, ComponentType, Q> const& up)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return quatLookAtLH(direction, up);
#		else
			return quatLookAtRH(direction, up);
# 		endif
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> quatLookAtRH(vec<3, ComponentType, Q> const& direction, vec<3, ComponentType, Q> const& up)
	{
		mat<3, 3, ComponentType, Q> Result;

		Result[2] = -direction;
		Result[0] = normalize(cross(up, Result[2]));
		Result[1] = cross(Result[2], Result[0]);

		return quat_cast(Result);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> quatLookAtLH(vec<3, ComponentType, Q> const& direction, vec<3, ComponentType, Q> const& up)
	{
		mat<3, 3, ComponentType, Q> Result;

		Result[2] = direction;
		Result[0] = normalize(cross(up, Result[2]));
		Result[1] = cross(Result[2], Result[0]);

		return quat_cast(Result);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "quaternion_simd.inl"
#endif

