/// @ref gtx_exterior_product

#include <limits>

namespace glm {
namespace detail
{
	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_cross_vec2
	{
		GLM_FUNC_QUALIFIER static ComponentType call(vec<2, ComponentType, Q> const& v, vec<2, ComponentType, Q> const& u)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'cross' accepts only floating-point inputs");

			return v.x * u.y - u.x * v.y;
		}
	};
}//namespace detail

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType cross(vec<2, ComponentType, Q> const& x, vec<2, ComponentType, Q> const& y)
	{
		return detail::compute_cross_vec2<ComponentType, Q, detail::is_aligned<Q>::value>::call(x, y);
	}
}//namespace glm

