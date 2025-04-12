/// @ref gtx_matrix_transform_2d
/// @author Miguel Ángel Pérez Martínez

#include "../trigonometric.hpp"

namespace glm
{

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> translate(
		mat<3, 3, ComponentType, Q> const& m,
		vec<2, ComponentType, Q> const& v)
	{
		mat<3, 3, ComponentType, Q> Result(m);
		Result[2] = m[0] * v[0] + m[1] * v[1] + m[2];
		return Result;
	}


	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> rotate(
		mat<3, 3, ComponentType, Q> const& m,
		ComponentType angle)
	{
		ComponentType const a = angle;
		ComponentType const c = cos(a);
		ComponentType const s = sin(a);

		mat<3, 3, ComponentType, Q> Result;
		Result[0] = m[0] * c + m[1] * s;
		Result[1] = m[0] * -s + m[1] * c;
		Result[2] = m[2];
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> scale(
		mat<3, 3, ComponentType, Q> const& m,
		vec<2, ComponentType, Q> const& v)
	{
		mat<3, 3, ComponentType, Q> Result;
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2];
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> shearX(
		mat<3, 3, ComponentType, Q> const& m,
		ComponentType y)
	{
		mat<3, 3, ComponentType, Q> Result(1);
		Result[0][1] = y;
		return m * Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> shearY(
		mat<3, 3, ComponentType, Q> const& m,
		ComponentType x)
	{
		mat<3, 3, ComponentType, Q> Result(1);
		Result[1][0] = x;
		return m * Result;
	}

}//namespace glm
