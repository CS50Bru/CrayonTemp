namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType dot(qua<ComponentType, Q> const& x, qua<ComponentType, Q> const& y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'dot' accepts only floating-point inputs");
		return detail::compute_dot<qua<ComponentType, Q>, ComponentType, detail::is_aligned<Q>::value>::call(x, y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType length(qua<ComponentType, Q> const& q)
	{
		return glm::sqrt(dot(q, q));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> normalize(qua<ComponentType, Q> const& q)
	{
		ComponentType len = length(q);
		if(len <= static_cast<ComponentType>(0)) // Problem
			return qua<ComponentType, Q>(static_cast<ComponentType>(1), static_cast<ComponentType>(0), static_cast<ComponentType>(0), static_cast<ComponentType>(0));
		ComponentType oneOverLen = static_cast<ComponentType>(1) / len;
		return qua<ComponentType, Q>(q.w * oneOverLen, q.x * oneOverLen, q.y * oneOverLen, q.z * oneOverLen);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> cross(qua<ComponentType, Q> const& q1, qua<ComponentType, Q> const& q2)
	{
		return qua<ComponentType, Q>(
			q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
			q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
			q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
			q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x);
	}
}//namespace glm

