namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> mix(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType a)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'mix' only accept floating-point inputs");

		ComponentType const cosTheta = dot(x, y);

		// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
		if(cosTheta > static_cast<ComponentType>(1) - epsilon<ComponentType>())
		{
			// Linear interpolation
			return qua<ComponentType, Q>(
				mix(x.w, y.w, a),
				mix(x.x, y.x, a),
				mix(x.y, y.y, a),
				mix(x.z, y.z, a));
		}
		else
		{
			// Essential Mathematics, page 467
			ComponentType angle = acos(cosTheta);
			return (sin((static_cast<ComponentType>(1) - a) * angle) * x + sin(a * angle) * y) / sin(angle);
		}
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> lerp(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType a)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'lerp' only accept floating-point inputs");

		// Lerp is only defined in [0, 1]
		assert(a >= static_cast<ComponentType>(0));
		assert(a <= static_cast<ComponentType>(1));

		return x * (static_cast<ComponentType>(1) - a) + (y * a);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> slerp(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y, ComponentType a)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'slerp' only accept floating-point inputs");

		qua<ComponentType, Q> z = y;

		ComponentType cosTheta = dot(x, y);

		// If cosTheta < 0, the interpolation will take the long way around the sphere.
		// To fix this, one quat must be negated.
		if(cosTheta < static_cast<ComponentType>(0))
		{
			z = -y;
			cosTheta = -cosTheta;
		}

		// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
		if(cosTheta > static_cast<ComponentType>(1) - epsilon<ComponentType>())
		{
			// Linear interpolation
			return qua<ComponentType, Q>(
				mix(x.w, z.w, a),
				mix(x.x, z.x, a),
				mix(x.y, z.y, a),
				mix(x.z, z.z, a));
		}
		else
		{
			// Essential Mathematics, page 467
			ComponentType angle = acos(cosTheta);
			return (sin((static_cast<ComponentType>(1) - a) * angle) * x + sin(a * angle) * z) / sin(angle);
		}
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> conjugate(qua<ComponentType, Q> const& q)
	{
		return qua<ComponentType, Q>(q.w, -q.x, -q.y, -q.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> inverse(qua<ComponentType, Q> const& q)
	{
		return conjugate(q) / dot(q, q);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> isnan(qua<ComponentType, Q> const& q)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'isnan' only accept floating-point inputs");

		return vec<4, bool, Q>(isnan(q.x), isnan(q.y), isnan(q.z), isnan(q.w));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> isinf(qua<ComponentType, Q> const& q)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'isinf' only accept floating-point inputs");

		return vec<4, bool, Q>(isinf(q.x), isinf(q.y), isinf(q.z), isinf(q.w));
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "quaternion_common_simd.inl"
#endif

