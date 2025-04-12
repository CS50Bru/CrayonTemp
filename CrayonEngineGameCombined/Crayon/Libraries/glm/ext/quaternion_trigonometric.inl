#include "scalar_constants.hpp"

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType angle(qua<ComponentType, Q> const& x)
	{
		if (abs(x.w) > cos_one_over_two<ComponentType>())
		{
			return asin(sqrt(x.x * x.x + x.y * x.y + x.z * x.z)) * static_cast<ComponentType>(2);
		}

		return acos(x.w) * static_cast<ComponentType>(2);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> axis(qua<ComponentType, Q> const& x)
	{
		ComponentType const tmp1 = static_cast<ComponentType>(1) - x.w * x.w;
		if(tmp1 <= static_cast<ComponentType>(0))
			return vec<3, ComponentType, Q>(0, 0, 1);
		ComponentType const tmp2 = static_cast<ComponentType>(1) / sqrt(tmp1);
		return vec<3, ComponentType, Q>(x.x * tmp2, x.y * tmp2, x.z * tmp2);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q> angleAxis(ComponentType const& angle, vec<3, ComponentType, Q> const& v)
	{
		ComponentType const a(angle);
		ComponentType const s = glm::sin(a * static_cast<ComponentType>(0.5));

		return qua<ComponentType, Q>(glm::cos(a * static_cast<ComponentType>(0.5)), v * s);
	}
}//namespace glm
