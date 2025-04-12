/// @ref core
/// @file glm/detail/type_mat2x4.hpp

#pragma once

#include "type_vec2.hpp"
#include "type_vec4.hpp"
#include <limits>
#include <cstddef>

namespace glm
{
	template<typename ComponentType, qualifier Q>
	struct mat<2, 4, ComponentType, Q>
	{
		typedef vec<4, ComponentType, Q> col_type;
		typedef vec<2, ComponentType, Q> row_type;
		typedef mat<2, 4, ComponentType, Q> type;
		typedef mat<4, 2, ComponentType, Q> transpose_type;
		typedef ComponentType value_type;

	private:
		col_type value[2];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length() { return 2; }

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<2, 4, ComponentType, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(ComponentType scalar);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			ComponentType x0, ComponentType y0, ComponentType z0, ComponentType w0,
			ComponentType x1, ComponentType y1, ComponentType z1, ComponentType w1);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v0,
			col_type const& v1);

		// -- Conversions --

		template<
			typename X1, typename Y1, typename Z1, typename W1,
			typename X2, typename Y2, typename Z2, typename W2>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			X1 x1, Y1 y1, Z1 z1, W1 w1,
			X2 x2, Y2 y2, Z2 z2, W2 w2);

		template<typename U, typename V>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<4, U, Q> const& v1,
			vec<4, V, Q> const& v2);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, ComponentType, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> & operator=(mat<2, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> & operator+=(mat<2, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> & operator-=(mat<2, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> & operator/=(U s);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> & operator++ ();
		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> & operator-- ();
		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator++(int);
		GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator+(mat<2, 4, ComponentType, Q> const& m);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator-(mat<2, 4, ComponentType, Q> const& m);

	// -- Binary operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator+(mat<2, 4, ComponentType, Q> const& m, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator+(mat<2, 4, ComponentType, Q> const& m1, mat<2, 4, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator-(mat<2, 4, ComponentType, Q> const& m, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator-(mat<2, 4, ComponentType, Q> const& m1, mat<2, 4, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator*(mat<2, 4, ComponentType, Q> const& m, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator*(ComponentType scalar, mat<2, 4, ComponentType, Q> const& m);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL typename mat<2, 4, ComponentType, Q>::col_type operator*(mat<2, 4, ComponentType, Q> const& m, typename mat<2, 4, ComponentType, Q>::row_type const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL typename mat<2, 4, ComponentType, Q>::row_type operator*(typename mat<2, 4, ComponentType, Q>::col_type const& v, mat<2, 4, ComponentType, Q> const& m);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator*(mat<2, 4, ComponentType, Q> const& m1, mat<4, 2, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator*(mat<2, 4, ComponentType, Q> const& m1, mat<2, 2, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, ComponentType, Q> operator*(mat<2, 4, ComponentType, Q> const& m1, mat<3, 2, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator/(mat<2, 4, ComponentType, Q> const& m, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator/(ComponentType scalar, mat<2, 4, ComponentType, Q> const& m);

	// -- Boolean operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL bool operator==(mat<2, 4, ComponentType, Q> const& m1, mat<2, 4, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<2, 4, ComponentType, Q> const& m1, mat<2, 4, ComponentType, Q> const& m2);
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_mat2x4.inl"
#endif
