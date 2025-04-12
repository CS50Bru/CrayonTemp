/// @ref core

#include "./compute_vector_relational.hpp"

namespace glm
{
	// -- Implicit basic constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q>::vec()
#			if GLM_CONFIG_CTOR_INIT != GLM_CTOR_INIT_DISABLE
				: x(0)
#			endif
		{}

		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q>::vec(vec<1, T, Q> const& v)
			: x(v.x)
		{}
#	endif

	template<typename ComponentType, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q>::vec(vec<1, ComponentType, P> const& v)
		: x(v.x)
	{}

	// -- Explicit basic constructors --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q>::vec(ComponentType scalar)
		: x(scalar)
	{}

	// -- Conversion vector constructors --

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q>::vec(vec<1, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q>::vec(vec<2, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q>::vec(vec<3, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q>::vec(vec<4, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
	{}

	// -- ComponentIdentifier accesses --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR ComponentType & vec<1, ComponentType, Q>::operator[](typename vec<1, ComponentType, Q>::length_type)
	{
		return x;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR ComponentType const& vec<1, ComponentType, Q>::operator[](typename vec<1, ComponentType, Q>::length_type) const
	{
		return x;
	}

	// -- Unary arithmetic operators --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, T, Q> & vec<1, T, Q>::operator=(vec<1, T, Q> const& v)
		{
			this->x = v.x;
			return *this;
		}
#	endif

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator=(vec<1, U, Q> const& v)
	{
		this->x = static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator+=(U scalar)
	{
		this->x += static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator+=(vec<1, U, Q> const& v)
	{
		this->x += static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator-=(U scalar)
	{
		this->x -= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator-=(vec<1, U, Q> const& v)
	{
		this->x -= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator*=(U scalar)
	{
		this->x *= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator*=(vec<1, U, Q> const& v)
	{
		this->x *= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator/=(U scalar)
	{
		this->x /= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator/=(vec<1, U, Q> const& v)
	{
		this->x /= static_cast<ComponentType>(v.x);
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator++()
	{
		++this->x;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator--()
	{
		--this->x;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> vec<1, ComponentType, Q>::operator++(int)
	{
		vec<1, ComponentType, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> vec<1, ComponentType, Q>::operator--(int)
	{
		vec<1, ComponentType, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator%=(U scalar)
	{
		this->x %= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator%=(vec<1, U, Q> const& v)
	{
		this->x %= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator&=(U scalar)
	{
		this->x &= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator&=(vec<1, U, Q> const& v)
	{
		this->x &= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator|=(U scalar)
	{
		this->x |= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator|=(vec<1, U, Q> const& v)
	{
		this->x |= U(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator^=(U scalar)
	{
		this->x ^= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator^=(vec<1, U, Q> const& v)
	{
		this->x ^= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator<<=(U scalar)
	{
		this->x <<= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator<<=(vec<1, U, Q> const& v)
	{
		this->x <<= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator>>=(U scalar)
	{
		this->x >>= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> & vec<1, ComponentType, Q>::operator>>=(vec<1, U, Q> const& v)
	{
		this->x >>= static_cast<ComponentType>(v.x);
		return *this;
	}

	// -- Unary constant operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator+(vec<1, ComponentType, Q> const& v)
	{
		return v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator-(vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			-v.x);
	}

	// -- Binary arithmetic operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator+(vec<1, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<1, ComponentType, Q>(
			v.x + scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator+(ComponentType scalar, vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			scalar + v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator+(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<1, ComponentType, Q>(
			v1.x + v2.x);
	}

	//operator-
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator-(vec<1, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<1, ComponentType, Q>(
			v.x - scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator-(ComponentType scalar, vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			scalar - v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator-(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<1, ComponentType, Q>(
			v1.x - v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator*(vec<1, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<1, ComponentType, Q>(
			v.x * scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator*(ComponentType scalar, vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			scalar * v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator*(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<1, ComponentType, Q>(
			v1.x * v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator/(vec<1, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<1, ComponentType, Q>(
			v.x / scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator/(ComponentType scalar, vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			scalar / v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator/(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<1, ComponentType, Q>(
			v1.x / v2.x);
	}

	// -- Binary bit operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator%(vec<1, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<1, ComponentType, Q>(
			v.x % scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator%(ComponentType scalar, vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			scalar % v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator%(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<1, ComponentType, Q>(
			v1.x % v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator&(vec<1, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<1, ComponentType, Q>(
			v.x & scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator&(ComponentType scalar, vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			scalar & v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator&(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<1, ComponentType, Q>(
			v1.x & v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator|(vec<1, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<1, ComponentType, Q>(
			v.x | scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator|(ComponentType scalar, vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			scalar | v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator|(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<1, ComponentType, Q>(
			v1.x | v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator^(vec<1, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<1, ComponentType, Q>(
			v.x ^ scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator^(ComponentType scalar, vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			scalar ^ v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator^(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<1, ComponentType, Q>(
			v1.x ^ v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator<<(vec<1, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<1, ComponentType, Q>(
			static_cast<ComponentType>(v.x << scalar));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator<<(ComponentType scalar, vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			scalar << v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator<<(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<1, ComponentType, Q>(
			v1.x << v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator>>(vec<1, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<1, ComponentType, Q>(
			v.x >> scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator>>(ComponentType scalar, vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			scalar >> v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator>>(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<1, ComponentType, Q>(
			v1.x >> v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, ComponentType, Q> operator~(vec<1, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(
			~v.x);
	}

	// -- Boolean operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return detail::compute_equal<ComponentType, std::numeric_limits<ComponentType>::is_iec559>::call(v1.x, v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(vec<1, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return !(v1 == v2);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, bool, Q> operator&&(vec<1, bool, Q> const& v1, vec<1, bool, Q> const& v2)
	{
		return vec<1, bool, Q>(v1.x && v2.x);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<1, bool, Q> operator||(vec<1, bool, Q> const& v1, vec<1, bool, Q> const& v2)
	{
		return vec<1, bool, Q>(v1.x || v2.x);
	}
}//namespace glm
