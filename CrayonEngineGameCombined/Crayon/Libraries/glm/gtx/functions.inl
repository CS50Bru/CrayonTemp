/// @ref gtx_functions

#include "../exponential.hpp"

namespace glm
{
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType gauss
	(
		ComponentType x,
		ComponentType ExpectedValue,
		ComponentType StandardDeviation
	)
	{
		return exp(-((x - ExpectedValue) * (x - ExpectedValue)) / (static_cast<ComponentType>(2) * StandardDeviation * StandardDeviation)) / (StandardDeviation * sqrt(static_cast<ComponentType>(6.28318530717958647692528676655900576)));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType gauss
	(
		vec<2, ComponentType, Q> const& Coord,
		vec<2, ComponentType, Q> const& ExpectedValue,
		vec<2, ComponentType, Q> const& StandardDeviation
	)
	{
		vec<2, ComponentType, Q> const Squared = ((Coord - ExpectedValue) * (Coord - ExpectedValue)) / (static_cast<ComponentType>(2) * StandardDeviation * StandardDeviation);
		return exp(-(Squared.x + Squared.y));
	}
}//namespace glm

