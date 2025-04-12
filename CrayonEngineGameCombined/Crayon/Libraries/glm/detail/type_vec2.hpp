/// @ref core
/// @file glm/detail/type_vec2.hpp

#pragma once

#include "qualifier.hpp"
#if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
#	include "_swizzle.hpp"
#elif GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
#	include "_swizzle_func.hpp"
#endif
#include <cstddef>

namespace glm
{
	template<typename ComponentType, qualifier Q>
	struct vec<2, ComponentType, Q>
	{
		// -- Implementation detail --

		typedef ComponentType value_type;
		typedef vec<2, ComponentType, Q> type;
		typedef vec<2, bool, Q> bool_type;

		// -- Data --

#		if GLM_SILENT_WARNINGS == GLM_ENABLE
#			if GLM_COMPILER & GLM_COMPILER_GCC
#				pragma GCC diagnostic push
#				pragma GCC diagnostic ignored "-Wpedantic"
#			elif GLM_COMPILER & GLM_COMPILER_CLANG
#				pragma clang diagnostic push
#				pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#				pragma clang diagnostic ignored "-Wnested-anon-types"
#			elif GLM_COMPILER & GLM_COMPILER_VC
#				pragma warning(push)
#				pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#			endif
#		endif

#		if GLM_CONFIG_XYZW_ONLY
			T x, y;
#		elif GLM_CONFIG_ANONYMOUS_STRUCT == GLM_ENABLE
			union
			{
				struct{ T x, y; };
				struct{ T r, g; };
				struct{ T s, t; };

				typename detail::storage<2, T, detail::is_aligned<Q>::value>::type data;

#				if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
					GLM_SWIZZLE2_2_MEMBERS(T, Q, x, y)
					GLM_SWIZZLE2_2_MEMBERS(T, Q, r, g)
					GLM_SWIZZLE2_2_MEMBERS(T, Q, s, t)
					GLM_SWIZZLE2_3_MEMBERS(T, Q, x, y)
					GLM_SWIZZLE2_3_MEMBERS(T, Q, r, g)
					GLM_SWIZZLE2_3_MEMBERS(T, Q, s, t)
					GLM_SWIZZLE2_4_MEMBERS(T, Q, x, y)
					GLM_SWIZZLE2_4_MEMBERS(T, Q, r, g)
					GLM_SWIZZLE2_4_MEMBERS(T, Q, s, t)
#				endif
			};
#		else
			union {ComponentType x, r, s;};
			union {ComponentType y, g, t;};

#			if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_FUNCTION
				GLM_SWIZZLE_GEN_VEC_FROM_VEC2(T, Q)
#			endif//GLM_CONFIG_SWIZZLE
#		endif

#		if GLM_SILENT_WARNINGS == GLM_ENABLE
#			if GLM_COMPILER & GLM_COMPILER_CLANG
#				pragma clang diagnostic pop
#			elif GLM_COMPILER & GLM_COMPILER_GCC
#				pragma GCC diagnostic pop
#			elif GLM_COMPILER & GLM_COMPILER_VC
#				pragma warning(pop)
#			endif
#		endif

		// -- ComponentIdentifier accesses --

		/// Return the count of components of the vector
		typedef length_t length_type;
		GLM_FUNC_DECL static GLM_CONSTEXPR length_type length(){return 2;}

		GLM_FUNC_DECL GLM_CONSTEXPR ComponentType& operator[](length_type i);
		GLM_FUNC_DECL GLM_CONSTEXPR ComponentType const& operator[](length_type i) const;

		// -- Implicit basic constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR vec() GLM_DEFAULT;
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec const& v) GLM_DEFAULT;
		template<qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<2, ComponentType, P> const& v);

		// -- Explicit basic constructors --

		GLM_FUNC_DECL GLM_CONSTEXPR explicit vec(ComponentType scalar);
		GLM_FUNC_DECL GLM_CONSTEXPR vec(ComponentType x, ComponentType y);

		// -- Conversion constructors --

		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR explicit vec(vec<1, U, P> const& v);

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename A, typename B>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(A x, B y);
		template<typename A, typename B>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, A, Q> const& x, B y);
		template<typename A, typename B>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(A x, vec<1, B, Q> const& y);
		template<typename A, typename B>
		GLM_FUNC_DECL GLM_CONSTEXPR vec(vec<1, A, Q> const& x, vec<1, B, Q> const& y);

		// -- Conversion vector constructors --

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<3, U, P> const& v);
		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<4, U, P> const& v);

		/// Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template<typename U, qualifier P>
		GLM_FUNC_DECL GLM_CONSTEXPR GLM_EXPLICIT vec(vec<2, U, P> const& v);

		// -- Swizzle constructors --
#		if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
			template<int E0, int E1>
			GLM_FUNC_DECL GLM_CONSTEXPR vec(detail::_swizzle<2, T, Q, E0, E1,-1,-2> const& that)
			{
				*this = that();
			}
#		endif//GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR

		// -- Unary arithmetic operators --

		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator=(vec const& v) GLM_DEFAULT;

		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator=(vec<2, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator+=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator+=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator+=(vec<2, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator-=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator-=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator-=(vec<2, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator*=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator*=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator*=(vec<2, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator/=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator/=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator/=(vec<2, U, Q> const& v);

		// -- Increment and decrement operators --

		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator++();
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator--();
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator++(int);
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator--(int);

		// -- Unary bit operators --

		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator%=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator%=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator%=(vec<2, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator&=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator&=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator&=(vec<2, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator|=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator|=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator|=(vec<2, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator^=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator^=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator^=(vec<2, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator<<=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator<<=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator<<=(vec<2, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator>>=(U scalar);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator>>=(vec<1, U, Q> const& v);
		template<typename U>
		GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> & operator>>=(vec<2, U, Q> const& v);
	};

	// -- Unary operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(vec<2, ComponentType, Q> const& v);

	// -- Binary operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(vec<2, ComponentType, Q> const& v, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(ComponentType scalar, vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(vec<2, ComponentType, Q> const& v, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(ComponentType scalar, vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator*(vec<2, ComponentType, Q> const& v, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator*(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator*(ComponentType scalar, vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator*(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator*(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator/(vec<2, ComponentType, Q> const& v, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator/(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator/(ComponentType scalar, vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator/(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator/(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator%(vec<2, ComponentType, Q> const& v, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator%(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator%(ComponentType scalar, vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator%(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator%(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator&(vec<2, ComponentType, Q> const& v, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator&(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator&(ComponentType scalar, vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator&(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator&(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator|(vec<2, ComponentType, Q> const& v, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator|(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator|(ComponentType scalar, vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator|(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator|(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator^(vec<2, ComponentType, Q> const& v, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator^(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator^(ComponentType scalar, vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator^(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator^(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator<<(vec<2, ComponentType, Q> const& v, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator<<(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator<<(ComponentType scalar, vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator<<(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator<<(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator>>(vec<2, ComponentType, Q> const& v, ComponentType scalar);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator>>(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator>>(ComponentType scalar, vec<2, ComponentType, Q> const& v);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator>>(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator>>(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, ComponentType, Q> operator~(vec<2, ComponentType, Q> const& v);

	// -- Boolean operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool operator==(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR bool operator!=(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2);

	template<qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, bool, Q> operator&&(vec<2, bool, Q> const& v1, vec<2, bool, Q> const& v2);

	template<qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<2, bool, Q> operator||(vec<2, bool, Q> const& v1, vec<2, bool, Q> const& v2);
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_vec2.inl"
#endif//GLM_EXTERNAL_TEMPLATE
