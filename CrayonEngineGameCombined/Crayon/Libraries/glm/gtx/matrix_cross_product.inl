/// @ref gtx_matrix_cross_product

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> matrixCross3
	(
		vec<3, ComponentType, Q> const& x
	)
	{
		mat<3, 3, ComponentType, Q> Result(ComponentType(0));
		Result[0][1] = x.z;
		Result[1][0] = -x.z;
		Result[0][2] = -x.y;
		Result[2][0] = x.y;
		Result[1][2] = x.x;
		Result[2][1] = -x.x;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> matrixCross4
	(
		vec<3, ComponentType, Q> const& x
	)
	{
		mat<4, 4, ComponentType, Q> Result(ComponentType(0));
		Result[0][1] = x.z;
		Result[1][0] = -x.z;
		Result[0][2] = -x.y;
		Result[2][0] = x.y;
		Result[1][2] = x.x;
		Result[2][1] = -x.x;
		return Result;
	}

}//namespace glm
