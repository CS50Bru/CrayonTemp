#include "scalar_constants.hpp"

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> exp(qua<ComponentType, Q> const& q)
	{
		vec<3, ComponentType, Q> u(q.x, q.y, q.z);
		ComponentType const Angle = glm::length(u);
		if (Angle < epsilon<ComponentType>())
			return qua<ComponentType, Q>();

		vec<3, ComponentType, Q> const v(u / Angle);
		return qua<ComponentType, Q>(cos(Angle), sin(Angle) * v);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> log(qua<ComponentType, Q> const& q)
	{
		vec<3, ComponentType, Q> u(q.x, q.y, q.z);
		ComponentType Vec3Len = length(u);

		if (Vec3Len < epsilon<ComponentType>())
		{
			if(q.w > static_cast<ComponentType>(0))
				return qua<ComponentType, Q>(log(q.w), static_cast<ComponentType>(0), static_cast<ComponentType>(0), static_cast<ComponentType>(0));
			else if(q.w < static_cast<ComponentType>(0))
				return qua<ComponentType, Q>(log(-q.w), pi<ComponentType>(), static_cast<ComponentType>(0), static_cast<ComponentType>(0));
			else
				return qua<ComponentType, Q>(std::numeric_limits<ComponentType>::infinity(), std::numeric_limits<ComponentType>::infinity(), std::numeric_limits<ComponentType>::infinity(), std::numeric_limits<ComponentType>::infinity());
		}
		else
		{
			ComponentType t = atan(Vec3Len, ComponentType(q.w)) / Vec3Len;
			ComponentType QuatLen2 = Vec3Len * Vec3Len + q.w * q.w;
			return qua<ComponentType, Q>(static_cast<ComponentType>(0.5) * log(QuatLen2), t * q.x, t * q.y, t * q.z);
		}
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> pow(qua<ComponentType, Q> const& x, ComponentType y)
	{
		//Raising to the power of 0 should yield 1
		//Needed to prevent a division by 0 error later on
		if(y > -epsilon<ComponentType>() && y < epsilon<ComponentType>())
			return qua<ComponentType, Q>(1,0,0,0);

		//To deal with non-unit quaternions
		ComponentType magnitude = sqrt(x.x * x.x + x.y * x.y + x.z * x.z + x.w *x.w);

		ComponentType Angle;
		if(abs(x.w / magnitude) > cos_one_over_two<ComponentType>())
		{
			//Scalar component is close to 1; using it to recover angle would lose precision
			//Instead, we use the non-scalar components since sin() is accurate around 0

			//Prevent a division by 0 error later on
			ComponentType VectorMagnitude = x.x * x.x + x.y * x.y + x.z * x.z;
			if (glm::abs(VectorMagnitude - static_cast<ComponentType>(0)) < glm::epsilon<ComponentType>()) {
				//Equivalent to raising a real number to a power
				return qua<ComponentType, Q>(pow(x.w, y), 0, 0, 0);
			}

			Angle = asin(sqrt(VectorMagnitude) / magnitude);
		}
		else
		{
			//Scalar component is small, shouldn't cause loss of precision
			Angle = acos(x.w / magnitude);
		}

		ComponentType NewAngle = Angle * y;
		ComponentType Div = sin(NewAngle) / sin(Angle);
		ComponentType Mag = pow(magnitude, y - static_cast<ComponentType>(1));
		return qua<ComponentType, Q>(cos(NewAngle) * magnitude * Mag, x.x * Div * Mag, x.y * Div * Mag, x.z * Div * Mag);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> sqrt(qua<ComponentType, Q> const& x)
	{
		return pow(x, static_cast<ComponentType>(0.5));
	}
}//namespace glm


