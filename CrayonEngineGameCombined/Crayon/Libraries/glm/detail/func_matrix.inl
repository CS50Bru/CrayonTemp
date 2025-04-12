#include "../geometric.hpp"
#include <limits>

namespace glm{
namespace detail
{
	template<length_t C, length_t R, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_matrixCompMult
	{
		GLM_FUNC_QUALIFIER static mat<C, R, ComponentType, Q> call(mat<C, R, ComponentType, Q> const& x, mat<C, R, ComponentType, Q> const& y)
		{
			mat<C, R, ComponentType, Q> Result;
			for(length_t i = 0; i < Result.length(); ++i)
				Result[i] = x[i] * y[i];
			return Result;
		}
	};

	template<length_t C, length_t R, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_transpose{};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_transpose<2, 2, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<2, 2, ComponentType, Q> call(mat<2, 2, ComponentType, Q> const& m)
		{
			mat<2, 2, ComponentType, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			return Result;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_transpose<2, 3, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<3, 2, ComponentType, Q> call(mat<2, 3, ComponentType, Q> const& m)
		{
			mat<3,2, ComponentType, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			return Result;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_transpose<2, 4, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<4, 2, ComponentType, Q> call(mat<2, 4, ComponentType, Q> const& m)
		{
			mat<4, 2, ComponentType, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			Result[3][0] = m[0][3];
			Result[3][1] = m[1][3];
			return Result;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_transpose<3, 2, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<2, 3, ComponentType, Q> call(mat<3, 2, ComponentType, Q> const& m)
		{
			mat<2, 3, ComponentType, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];
			return Result;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_transpose<3, 3, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<3, 3, ComponentType, Q> call(mat<3, 3, ComponentType, Q> const& m)
		{
			mat<3, 3, ComponentType, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];

			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];

			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			Result[2][2] = m[2][2];
			return Result;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_transpose<3, 4, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<4, 3, ComponentType, Q> call(mat<3, 4, ComponentType, Q> const& m)
		{
			mat<4, 3, ComponentType, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];
			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			Result[2][2] = m[2][2];
			Result[3][0] = m[0][3];
			Result[3][1] = m[1][3];
			Result[3][2] = m[2][3];
			return Result;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_transpose<4, 2, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<2, 4, ComponentType, Q> call(mat<4, 2, ComponentType, Q> const& m)
		{
			mat<2, 4, ComponentType, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];
			Result[0][3] = m[3][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];
			Result[1][3] = m[3][1];
			return Result;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_transpose<4, 3, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<3, 4, ComponentType, Q> call(mat<4, 3, ComponentType, Q> const& m)
		{
			mat<3, 4, ComponentType, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];
			Result[0][3] = m[3][0];
			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];
			Result[1][3] = m[3][1];
			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			Result[2][2] = m[2][2];
			Result[2][3] = m[3][2];
			return Result;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_transpose<4, 4, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<4, 4, ComponentType, Q> call(mat<4, 4, ComponentType, Q> const& m)
		{
			mat<4, 4, ComponentType, Q> Result;
			Result[0][0] = m[0][0];
			Result[0][1] = m[1][0];
			Result[0][2] = m[2][0];
			Result[0][3] = m[3][0];

			Result[1][0] = m[0][1];
			Result[1][1] = m[1][1];
			Result[1][2] = m[2][1];
			Result[1][3] = m[3][1];

			Result[2][0] = m[0][2];
			Result[2][1] = m[1][2];
			Result[2][2] = m[2][2];
			Result[2][3] = m[3][2];

			Result[3][0] = m[0][3];
			Result[3][1] = m[1][3];
			Result[3][2] = m[2][3];
			Result[3][3] = m[3][3];
			return Result;
		}
	};

	template<length_t C, length_t R, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_determinant{};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_determinant<2, 2, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static ComponentType call(mat<2, 2, ComponentType, Q> const& m)
		{
			return m[0][0] * m[1][1] - m[1][0] * m[0][1];
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_determinant<3, 3, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static ComponentType call(mat<3, 3, ComponentType, Q> const& m)
		{
			return
				+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
				- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
				+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_determinant<4, 4, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static ComponentType call(mat<4, 4, ComponentType, Q> const& m)
		{
			ComponentType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			ComponentType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			ComponentType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			ComponentType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			ComponentType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			ComponentType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

			vec<4, ComponentType, Q> DetCof(
				+ (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02),
				- (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04),
				+ (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05),
				- (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05));

			return
				m[0][0] * DetCof[0] + m[0][1] * DetCof[1] +
				m[0][2] * DetCof[2] + m[0][3] * DetCof[3];
		}
	};

	template<length_t C, length_t R, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_inverse{};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_inverse<2, 2, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<2, 2, ComponentType, Q> call(mat<2, 2, ComponentType, Q> const& m)
		{
			ComponentType OneOverDeterminant = static_cast<ComponentType>(1) / (
				+ m[0][0] * m[1][1]
				- m[1][0] * m[0][1]);

			mat<2, 2, ComponentType, Q> Inverse(
				+ m[1][1] * OneOverDeterminant,
				- m[0][1] * OneOverDeterminant,
				- m[1][0] * OneOverDeterminant,
				+ m[0][0] * OneOverDeterminant);

			return Inverse;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_inverse<3, 3, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<3, 3, ComponentType, Q> call(mat<3, 3, ComponentType, Q> const& m)
		{
			ComponentType OneOverDeterminant = static_cast<ComponentType>(1) / (
				+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
				- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
				+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));

			mat<3, 3, ComponentType, Q> Inverse;
			Inverse[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * OneOverDeterminant;
			Inverse[1][0] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]) * OneOverDeterminant;
			Inverse[2][0] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * OneOverDeterminant;
			Inverse[0][1] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]) * OneOverDeterminant;
			Inverse[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * OneOverDeterminant;
			Inverse[2][1] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]) * OneOverDeterminant;
			Inverse[0][2] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * OneOverDeterminant;
			Inverse[1][2] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]) * OneOverDeterminant;
			Inverse[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * OneOverDeterminant;

			return Inverse;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_inverse<4, 4, ComponentType, Q, Aligned>
	{
		GLM_FUNC_QUALIFIER static mat<4, 4, ComponentType, Q> call(mat<4, 4, ComponentType, Q> const& m)
		{
			ComponentType Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			ComponentType Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
			ComponentType Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

			ComponentType Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			ComponentType Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
			ComponentType Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

			ComponentType Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			ComponentType Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
			ComponentType Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

			ComponentType Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			ComponentType Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
			ComponentType Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

			ComponentType Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			ComponentType Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
			ComponentType Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

			ComponentType Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
			ComponentType Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
			ComponentType Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

			vec<4, ComponentType, Q> Fac0(Coef00, Coef00, Coef02, Coef03);
			vec<4, ComponentType, Q> Fac1(Coef04, Coef04, Coef06, Coef07);
			vec<4, ComponentType, Q> Fac2(Coef08, Coef08, Coef10, Coef11);
			vec<4, ComponentType, Q> Fac3(Coef12, Coef12, Coef14, Coef15);
			vec<4, ComponentType, Q> Fac4(Coef16, Coef16, Coef18, Coef19);
			vec<4, ComponentType, Q> Fac5(Coef20, Coef20, Coef22, Coef23);

			vec<4, ComponentType, Q> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
			vec<4, ComponentType, Q> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
			vec<4, ComponentType, Q> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
			vec<4, ComponentType, Q> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

			vec<4, ComponentType, Q> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
			vec<4, ComponentType, Q> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
			vec<4, ComponentType, Q> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
			vec<4, ComponentType, Q> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

			vec<4, ComponentType, Q> SignA(+1, -1, +1, -1);
			vec<4, ComponentType, Q> SignB(-1, +1, -1, +1);
			mat<4, 4, ComponentType, Q> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

			vec<4, ComponentType, Q> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

			vec<4, ComponentType, Q> Dot0(m[0] * Row0);
			ComponentType Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

			ComponentType OneOverDeterminant = static_cast<ComponentType>(1) / Dot1;

			return Inverse * OneOverDeterminant;
		}
	};
}//namespace detail

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<C, R, ComponentType, Q> matrixCompMult(mat<C, R, ComponentType, Q> const& x, mat<C, R, ComponentType, Q> const& y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'matrixCompMult' only accept floating-point inputs");
		return detail::compute_matrixCompMult<C, R, ComponentType, Q, detail::is_aligned<Q>::value>::call(x, y);
	}

	template<length_t DA, length_t DB, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER typename detail::outerProduct_trait<DA, DB, ComponentType, Q>::type outerProduct(vec<DA, ComponentType, Q> const& c, vec<DB, ComponentType, Q> const& r)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'outerProduct' only accept floating-point inputs");

		typename detail::outerProduct_trait<DA, DB, ComponentType, Q>::type m;
		for(length_t i = 0; i < m.length(); ++i)
			m[i] = c * r[i];
		return m;
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER typename mat<C, R, ComponentType, Q>::transpose_type transpose(mat<C, R, ComponentType, Q> const& m)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'transpose' only accept floating-point inputs");
		return detail::compute_transpose<C, R, ComponentType, Q, detail::is_aligned<Q>::value>::call(m);
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType determinant(mat<C, R, ComponentType, Q> const& m)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'determinant' only accept floating-point inputs");
		return detail::compute_determinant<C, R, ComponentType, Q, detail::is_aligned<Q>::value>::call(m);
	}

	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<C, R, ComponentType, Q> inverse(mat<C, R, ComponentType, Q> const& m)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559 || GLM_CONFIG_UNRESTRICTED_GENTYPE, "'inverse' only accept floating-point inputs");
		return detail::compute_inverse<C, R, ComponentType, Q, detail::is_aligned<Q>::value>::call(m);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "func_matrix_simd.inl"
#endif

