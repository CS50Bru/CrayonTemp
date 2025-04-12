/// @ref gtx_vector_angle

namespace glm
{
	template<typename genType>
	GLM_FUNC_QUALIFIER genType angle
	(
		genType const& x,
		genType const& y
	)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'angle' only accept floating-point inputs");
		return acos(clamp(dot(x, y), genType(-1), genType(1)));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType angle(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'angle' only accept floating-point inputs");
		return acos(clamp(dot(x, y), ComponentType(-1), ComponentType(1)));
	}

	//! \todo epsilon is hard coded to 0.01
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType orientedAngle(vec<2, ComponentType, Q> const& x, vec<2, ComponentType, Q> const& y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'orientedAngle' only accept floating-point inputs");
		ComponentType const Angle(acos(clamp(dot(x, y), ComponentType(-1), ComponentType(1))));

		if(all(epsilonEqual(y, glm::rotate(x, Angle), ComponentType(0.0001))))
			return Angle;
		else
			return -Angle;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType orientedAngle(vec<3, ComponentType, Q> const& x, vec<3, ComponentType, Q> const& y, vec<3, ComponentType, Q> const& ref)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'orientedAngle' only accept floating-point inputs");

		ComponentType const Angle(acos(clamp(dot(x, y), ComponentType(-1), ComponentType(1))));
		return mix(Angle, -Angle, dot(ref, cross(x, y)) < ComponentType(0));
	}
}//namespace glm
