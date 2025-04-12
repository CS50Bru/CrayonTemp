/// @ref gtc_matrix_inverse

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> affineInverse(mat<3, 3, ComponentType, Q> const& m)
	{
		mat<2, 2, ComponentType, Q> const Inv(inverse(mat<2, 2, ComponentType, Q>(m)));

		return mat<3, 3, ComponentType, Q>(
			vec<3, ComponentType, Q>(Inv[0], static_cast<ComponentType>(0)),
			vec<3, ComponentType, Q>(Inv[1], static_cast<ComponentType>(0)),
			vec<3, ComponentType, Q>(-Inv * vec<2, ComponentType, Q>(m[2]), static_cast<ComponentType>(1)));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> affineInverse(mat<4, 4, ComponentType, Q> const& m)
	{
		mat<3, 3, ComponentType, Q> const Inv(inverse(mat<3, 3, ComponentType, Q>(m)));

		return mat<4, 4, ComponentType, Q>(
			vec<4, ComponentType, Q>(Inv[0], static_cast<ComponentType>(0)),
			vec<4, ComponentType, Q>(Inv[1], static_cast<ComponentType>(0)),
			vec<4, ComponentType, Q>(Inv[2], static_cast<ComponentType>(0)),
			vec<4, ComponentType, Q>(-Inv * vec<3, ComponentType, Q>(m[3]), static_cast<ComponentType>(1)));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 2, ComponentType, Q> inverseTranspose(mat<2, 2, ComponentType, Q> const& m)
	{
		ComponentType Determinant = m[0][0] * m[1][1] - m[1][0] * m[0][1];

		mat<2, 2, ComponentType, Q> Inverse(
			+ m[1][1] / Determinant,
			- m[0][1] / Determinant,
			- m[1][0] / Determinant,
			+ m[0][0] / Determinant);

		return Inverse;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> inverseTranspose(mat<3, 3, ComponentType, Q> const& m)
	{
		ComponentType Determinant =
			+ m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
			- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
			+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

		mat<3, 3, ComponentType, Q> Inverse;
		Inverse[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
		Inverse[0][1] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]);
		Inverse[0][2] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
		Inverse[1][0] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]);
		Inverse[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
		Inverse[1][2] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]);
		Inverse[2][0] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
		Inverse[2][1] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]);
		Inverse[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
		Inverse /= Determinant;

		return Inverse;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> inverseTranspose(mat<4, 4, ComponentType, Q> const& m)
	{
		ComponentType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		ComponentType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		ComponentType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		ComponentType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		ComponentType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		ComponentType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		ComponentType SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		ComponentType SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		ComponentType SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		ComponentType SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		ComponentType SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		ComponentType SubFactor11 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		ComponentType SubFactor12 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
		ComponentType SubFactor13 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
		ComponentType SubFactor14 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
		ComponentType SubFactor15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
		ComponentType SubFactor16 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
		ComponentType SubFactor17 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		mat<4, 4, ComponentType, Q> Inverse;
		Inverse[0][0] = + (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02);
		Inverse[0][1] = - (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04);
		Inverse[0][2] = + (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05);
		Inverse[0][3] = - (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05);

		Inverse[1][0] = - (m[0][1] * SubFactor00 - m[0][2] * SubFactor01 + m[0][3] * SubFactor02);
		Inverse[1][1] = + (m[0][0] * SubFactor00 - m[0][2] * SubFactor03 + m[0][3] * SubFactor04);
		Inverse[1][2] = - (m[0][0] * SubFactor01 - m[0][1] * SubFactor03 + m[0][3] * SubFactor05);
		Inverse[1][3] = + (m[0][0] * SubFactor02 - m[0][1] * SubFactor04 + m[0][2] * SubFactor05);

		Inverse[2][0] = + (m[0][1] * SubFactor06 - m[0][2] * SubFactor07 + m[0][3] * SubFactor08);
		Inverse[2][1] = - (m[0][0] * SubFactor06 - m[0][2] * SubFactor09 + m[0][3] * SubFactor10);
		Inverse[2][2] = + (m[0][0] * SubFactor07 - m[0][1] * SubFactor09 + m[0][3] * SubFactor11);
		Inverse[2][3] = - (m[0][0] * SubFactor08 - m[0][1] * SubFactor10 + m[0][2] * SubFactor11);

		Inverse[3][0] = - (m[0][1] * SubFactor12 - m[0][2] * SubFactor13 + m[0][3] * SubFactor14);
		Inverse[3][1] = + (m[0][0] * SubFactor12 - m[0][2] * SubFactor15 + m[0][3] * SubFactor16);
		Inverse[3][2] = - (m[0][0] * SubFactor13 - m[0][1] * SubFactor15 + m[0][3] * SubFactor17);
		Inverse[3][3] = + (m[0][0] * SubFactor14 - m[0][1] * SubFactor16 + m[0][2] * SubFactor17);

		ComponentType Determinant =
			+ m[0][0] * Inverse[0][0]
			+ m[0][1] * Inverse[0][1]
			+ m[0][2] * Inverse[0][2]
			+ m[0][3] * Inverse[0][3];

		Inverse /= Determinant;

		return Inverse;
	}
}//namespace glm
