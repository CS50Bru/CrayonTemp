#include "../matrix.hpp"

namespace glm
{
	template<length_t C, length_t R, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER mat<C, R, ComponentType, Q> mix(mat<C, R, ComponentType, Q> const& x, mat<C, R, ComponentType, Q> const& y, U a)
	{
		return mat<C, R, U, Q>(x) * (static_cast<U>(1) - a) + mat<C, R, U, Q>(y) * a;
	}

	template<length_t C, length_t R, typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER mat<C, R, ComponentType, Q> mix(mat<C, R, ComponentType, Q> const& x, mat<C, R, ComponentType, Q> const& y, mat<C, R, U, Q> const& a)
	{
		return matrixCompMult(mat<C, R, U, Q>(x), static_cast<U>(1) - a) + matrixCompMult(mat<C, R, U, Q>(y), a);
	}
}//namespace glm
