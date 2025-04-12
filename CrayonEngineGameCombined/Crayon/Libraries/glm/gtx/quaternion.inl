/// @ref gtx_quaternion

#include <limits>
#include "../gtc/constants.hpp"

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> quat_identity()
	{
		return qua<ComponentType, Q>(static_cast<ComponentType>(1), static_cast<ComponentType>(0), static_cast<ComponentType>(0), static_cast<ComponentType>(0));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> cross(vec<3, ComponentType, Q> const& v, qua<ComponentType, Q> const& q)
	{
		return inverse(q) * v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> cross(qua<ComponentType, Q> const& q, vec<3, ComponentType, Q> const& v)
	{
		return q * v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> squad
	(
		qua<ComponentType, Q> const& q1,
		qua<ComponentType, Q> const& q2,
		qua<ComponentType, Q> const& s1,
		qua<ComponentType, Q> const& s2,
		ComponentType const& h)
	{
		return mix(mix(q1, q2, h), mix(s1, s2, h), static_cast<ComponentType>(2) * (static_cast<ComponentType>(1) - h) * h);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> intermediate
	(
		qua<ComponentType, Q> const& prev,
		qua<ComponentType, Q> const& curr,
		qua<ComponentType, Q> const& next
	)
	{
		qua<ComponentType, Q> invQuat = inverse(curr);
		return exp((log(next * invQuat) + log(prev * invQuat)) / static_cast<ComponentType>(-4)) * curr;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rotate(qua<ComponentType, Q> const& q, vec<3, ComponentType, Q> const& v)
	{
		return q * v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> rotate(qua<ComponentType, Q> const& q, vec<4, ComponentType, Q> const& v)
	{
		return q * v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType extractRealComponent(qua<ComponentType, Q> const& q)
	{
		ComponentType w = static_cast<ComponentType>(1) - q.x * q.x - q.y * q.y - q.z * q.z;
		if(w < ComponentType(0))
			return ComponentType(0);
		else
			return -sqrt(w);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR ComponentType length2(qua<ComponentType, Q> const& q)
	{
		return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> shortMix(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType const& a)
	{
		if(a <= static_cast<ComponentType>(0)) return x;
		if(a >= static_cast<ComponentType>(1)) return y;

		ComponentType fCos = dot(x, y);
		qua<ComponentType, Q> y2(y); //BUG!!! qua<ComponentType> y2;
		if(fCos < static_cast<ComponentType>(0))
		{
			y2 = -y;
			fCos = -fCos;
		}

		//if(fCos > 1.0f) // problem
		ComponentType k0, k1;
		if(fCos > (static_cast<ComponentType>(1) - epsilon<ComponentType>()))
		{
			k0 = static_cast<ComponentType>(1) - a;
			k1 = static_cast<ComponentType>(0) + a; //BUG!!! 1.0f + a;
		}
		else
		{
			ComponentType fSin = sqrt(ComponentType(1) - fCos * fCos);
			ComponentType fAngle = atan(fSin, fCos);
			ComponentType fOneOverSin = static_cast<ComponentType>(1) / fSin;
			k0 = sin((static_cast<ComponentType>(1) - a) * fAngle) * fOneOverSin;
			k1 = sin((static_cast<ComponentType>(0) + a) * fAngle) * fOneOverSin;
		}

		return qua<ComponentType, Q>(
			k0 * x.w + k1 * y2.w,
			k0 * x.x + k1 * y2.x,
			k0 * x.y + k1 * y2.y,
			k0 * x.z + k1 * y2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> fastMix(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType const& a)
	{
		return glm::normalize(x * (static_cast<ComponentType>(1) - a) + (y * a));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> rotation(vec<3, ComponentType, Q> const& orig, vec<3, ComponentType, Q> const& dest)
	{
		ComponentType cosTheta = dot(orig, dest);
		vec<3, ComponentType, Q> rotationAxis;

		if(cosTheta >= static_cast<ComponentType>(1) - epsilon<ComponentType>()) {
			// orig and dest point in the same direction
			return quat_identity<ComponentType,Q>();
		}

		if(cosTheta < static_cast<ComponentType>(-1) + epsilon<ComponentType>())
		{
			// special case when vectors in opposite directions :
			// there is no "ideal" rotation axis
			// So guess one; any will do as long as it's perpendicular to start
			// This implementation favors a rotation around the Up axis (Y),
			// since it's often what you want to do.
			rotationAxis = cross(vec<3, ComponentType, Q>(0, 0, 1), orig);
			if(length2(rotationAxis) < epsilon<ComponentType>()) // bad luck, they were parallel, try again!
				rotationAxis = cross(vec<3, ComponentType, Q>(1, 0, 0), orig);

			rotationAxis = normalize(rotationAxis);
			return angleAxis(pi<ComponentType>(), rotationAxis);
		}

		// Implementation from Stan Melax's Game Programming Gems 1 article
		rotationAxis = cross(orig, dest);

		ComponentType s = sqrt((ComponentType(1) + cosTheta) * static_cast<ComponentType>(2));
		ComponentType invs = static_cast<ComponentType>(1) / s;

		return qua<ComponentType, Q>(
			s * static_cast<ComponentType>(0.5f),
			rotationAxis.x * invs,
			rotationAxis.y * invs,
			rotationAxis.z * invs);
	}
}//namespace glm
