/// @ref core
/// @file glm/detail/type_mat4x4.hpp

#pragma once

#include "type_vec4.hpp"
#include <limits>
#include <cstddef>

namespace glm
{
	template<typename ComponentType, qualifier Q>
	struct mat<4, 4, ComponentType, Q>
	{
		typedef vec<4, ComponentType, Q> col_type;
		typedef vec<4, ComponentType, Q> row_type;
		typedef mat<4, 4, ComponentType, Q> type;
		typedef mat<4, 4, ComponentType, Q> transpose_type;
		typedef ComponentType value_type;

	private:
		col_type value[4];

	public:
		// -- Accesses --

		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length(){return 4;}

		GLM_FUNC_DECL col_type & operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR col_type const& operator[](length_type i) const;

		// -- Constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR mat() GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(mat<4, 4, ComponentType, P> const& m);

		GLM_FUNC_DECL explicit GLM_CONSTEXPR mat(ComponentType const& x);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			ComponentType const& x0, ComponentType const& y0, ComponentType const& z0, ComponentType const& w0,
			ComponentType const& x1, ComponentType const& y1, ComponentType const& z1, ComponentType const& w1,
			ComponentType const& x2, ComponentType const& y2, ComponentType const& z2, ComponentType const& w2,
			ComponentType const& x3, ComponentType const& y3, ComponentType const& z3, ComponentType const& w3);
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			col_type const& v0,
			col_type const& v1,
			col_type const& v2,
			col_type const& v3);

		// -- Conversions --

		template<
			typename X1, typename Y1, typename Z1, typename W1,
			typename X2, typename Y2, typename Z2, typename W2,
			typename X3, typename Y3, typename Z3, typename W3,
			typename X4, typename Y4, typename Z4, typename W4>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			X1 const& x1, Y1 const& y1, Z1 const& z1, W1 const& w1,
			X2 const& x2, Y2 const& y2, Z2 const& z2, W2 const& w2,
			X3 const& x3, Y3 const& y3, Z3 const& z3, W3 const& w3,
			X4 const& x4, Y4 const& y4, Z4 const& z4, W4 const& w4);

		template<typename V1, typename V2, typename V3, typename V4>
		GLM_FUNC_DECL GLM_CONSTEXPR mat(
			vec<4, V1, Q> const& v1,
			vec<4, V2, Q> const& v2,
			vec<4, V3, Q> const& v3,
			vec<4, V4, Q> const& v4);

		// -- Matrix conversions --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 4, U, P> const& m);

		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 2, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 3, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 3, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 2, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<2, 4, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 2, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<3, 4, ComponentType, Q> const& x);
		GLM_FUNC_DECL GLM_EXPLICIT GLM_CONSTEXPR mat(mat<4, 3, ComponentType, Q> const& x);

		// -- Unary arithmetic operators --

		template<typename U>
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator=(mat<4, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator+=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator+=(mat<4, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator-=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator-=(mat<4, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator*=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator*=(mat<4, 4, U, Q> const& m);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator/=(U s);
		template<typename U>
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator/=(mat<4, 4, U, Q> const& m);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator++();
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> & operator--();
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator++(int);
		GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator--(int);
	};

	// -- Unary operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator+(mat<4, 4, ComponentType, Q> const& m);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator-(mat<4, 4, ComponentType, Q> const& m);

	// -- Binary operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator+(mat<4, 4, ComponentType, Q> const& m, ComponentType const& s);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator+(ComponentType const& s, mat<4, 4, ComponentType, Q> const& m);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator+(mat<4, 4, ComponentType, Q> const& m1, mat<4, 4, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator-(mat<4, 4, ComponentType, Q> const& m, ComponentType const& s);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator-(ComponentType const& s, mat<4, 4, ComponentType, Q> const& m);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator-(mat<4, 4, ComponentType, Q> const& m1,	mat<4, 4, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator*(mat<4, 4, ComponentType, Q> const& m, ComponentType const& s);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator*(ComponentType const& s, mat<4, 4, ComponentType, Q> const& m);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 4, ComponentType, Q>::col_type operator*(mat<4, 4, ComponentType, Q> const& m, typename mat<4, 4, ComponentType, Q>::row_type const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 4, ComponentType, Q>::row_type operator*(typename mat<4, 4, ComponentType, Q>::col_type const& v, mat<4, 4, ComponentType, Q> const& m);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<2, 4, ComponentType, Q> operator*(mat<4, 4, ComponentType, Q> const& m1, mat<2, 4, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<3, 4, ComponentType, Q> operator*(mat<4, 4, ComponentType, Q> const& m1, mat<3, 4, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator*(mat<4, 4, ComponentType, Q> const& m1, mat<4, 4, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator/(mat<4, 4, ComponentType, Q> const& m, ComponentType const& s);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator/(ComponentType const& s, mat<4, 4, ComponentType, Q> const& m);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 4, ComponentType, Q>::col_type operator/(mat<4, 4, ComponentType, Q> const& m, typename mat<4, 4, ComponentType, Q>::row_type const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL typename mat<4, 4, ComponentType, Q>::row_type operator/(typename mat<4, 4, ComponentType, Q>::col_type const& v, mat<4, 4, ComponentType, Q> const& m);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, ComponentType, Q> operator/(mat<4, 4, ComponentType, Q> const& m1,	mat<4, 4, ComponentType, Q> const& m2);

	// -- Boolean operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL bool operator==(mat<4, 4, ComponentType, Q> const& m1, mat<4, 4, ComponentType, Q> const& m2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL bool operator!=(mat<4, 4, ComponentType, Q> const& m1, mat<4, 4, ComponentType, Q> const& m2);
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_mat4x4.inl"
#endif//GLM_EXTERNAL_TEMPLATE
