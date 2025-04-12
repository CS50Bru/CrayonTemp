/// @ref gtx_gradient_paint

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType radialGradient
	(
		vec<2, ComponentType, Q> const& Center,
		ComponentType const& Radius,
		vec<2, ComponentType, Q> const& Focal,
		vec<2, ComponentType, Q> const& Position
	)
	{
		vec<2, ComponentType, Q> F = Focal - Center;
		vec<2, ComponentType, Q> D = Position - Focal;
		ComponentType Radius2 = pow2(Radius);
		ComponentType Fx2 = pow2(F.x);
		ComponentType Fy2 = pow2(F.y);

		ComponentType Numerator = (D.x * F.x + D.y * F.y) + sqrt(Radius2 * (pow2(D.x) + pow2(D.y)) - pow2(D.x * F.y - D.y * F.x));
		ComponentType Denominator = Radius2 - (Fx2 + Fy2);
		return Numerator / Denominator;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType linearGradient
	(
		vec<2, ComponentType, Q> const& Point0,
		vec<2, ComponentType, Q> const& Point1,
		vec<2, ComponentType, Q> const& Position
	)
	{
		vec<2, ComponentType, Q> Dist = Point1 - Point0;
		return (Dist.x * (Position.x - Point0.x) + Dist.y * (Position.y - Point0.y)) / glm::dot(Dist, Dist);
	}
}//namespace glm
