namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> rotate(qua<ComponentType, Q> const& q, ComponentType const& angle, vec<3, ComponentType, Q> const& v)
	{
		vec<3, ComponentType, Q> Tmp = v;

		// Axis of rotation must be normalised
		ComponentType len = glm::length(Tmp);
		if(abs(len - static_cast<ComponentType>(1)) > static_cast<ComponentType>(0.001))
		{
			ComponentType oneOverLen = static_cast<ComponentType>(1) / len;
			Tmp.x *= oneOverLen;
			Tmp.y *= oneOverLen;
			Tmp.z *= oneOverLen;
		}

		ComponentType const AngleRad(angle);
		ComponentType const Sin = sin(AngleRad * static_cast<ComponentType>(0.5));

		return q * qua<ComponentType, Q>(cos(AngleRad * static_cast<ComponentType>(0.5)), Tmp.x * Sin, Tmp.y * Sin, Tmp.z * Sin);
	}
}//namespace glm

