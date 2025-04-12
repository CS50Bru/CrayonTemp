/// @ref core

#include "./compute_vector_relational.hpp"

namespace glm
{
	// -- Implicit basic constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec()
#			if GLM_CONFIG_CTOR_INIT != GLM_CTOR_INIT_DISABLE
				: x(0), y(0)
#			endif
		{}

		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q>::vec(vec<2, T, Q> const& v)
			: x(v.x), y(v.y)
		{}
#	endif

	template<typename ComponentType, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(vec<2, ComponentType, P> const& v)
		: x(v.x), y(v.y)
	{}

	// -- Explicit basic constructors --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(ComponentType scalar)
		: x(scalar), y(scalar)
	{}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(ComponentType _x, ComponentType _y)
		: x(_x), y(_y)
	{}

	// -- Conversion scalar constructors --

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(vec<1, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
		, y(static_cast<ComponentType>(v.x))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename A, typename B>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(A _x, B _y)
		: x(static_cast<ComponentType>(_x))
		, y(static_cast<ComponentType>(_y))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename A, typename B>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(vec<1, A, Q> const& _x, B _y)
		: x(static_cast<ComponentType>(_x.x))
		, y(static_cast<ComponentType>(_y))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename A, typename B>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(A _x, vec<1, B, Q> const& _y)
		: x(static_cast<ComponentType>(_x))
		, y(static_cast<ComponentType>(_y.x))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename A, typename B>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(vec<1, A, Q> const& _x, vec<1, B, Q> const& _y)
		: x(static_cast<ComponentType>(_x.x))
		, y(static_cast<ComponentType>(_y.x))
	{}

	// -- Conversion vector constructors --

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(vec<2, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
		, y(static_cast<ComponentType>(v.y))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(vec<3, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
		, y(static_cast<ComponentType>(v.y))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q>::vec(vec<4, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
		, y(static_cast<ComponentType>(v.y))
	{}

	// -- ComponentIdentifier accesses --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR ComponentType & vec<2, ComponentType, Q>::operator[](typename vec<2, ComponentType, Q>::length_type i)
	{
		assert(i >= 0 && i < this->length());
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		}
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR ComponentType const& vec<2, ComponentType, Q>::operator[](typename vec<2, ComponentType, Q>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		}
	}

	// -- Unary arithmetic operators --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, T, Q> & vec<2, T, Q>::operator=(vec<2, T, Q> const& v)
		{
			this->x = v.x;
			this->y = v.y;
			return *this;
		}
#	endif

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator=(vec<2, U, Q> const& v)
	{
		this->x = static_cast<ComponentType>(v.x);
		this->y = static_cast<ComponentType>(v.y);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator+=(U scalar)
	{
		this->x += static_cast<ComponentType>(scalar);
		this->y += static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator+=(vec<1, U, Q> const& v)
	{
		this->x += static_cast<ComponentType>(v.x);
		this->y += static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator+=(vec<2, U, Q> const& v)
	{
		this->x += static_cast<ComponentType>(v.x);
		this->y += static_cast<ComponentType>(v.y);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator-=(U scalar)
	{
		this->x -= static_cast<ComponentType>(scalar);
		this->y -= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator-=(vec<1, U, Q> const& v)
	{
		this->x -= static_cast<ComponentType>(v.x);
		this->y -= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator-=(vec<2, U, Q> const& v)
	{
		this->x -= static_cast<ComponentType>(v.x);
		this->y -= static_cast<ComponentType>(v.y);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator*=(U scalar)
	{
		this->x *= static_cast<ComponentType>(scalar);
		this->y *= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator*=(vec<1, U, Q> const& v)
	{
		this->x *= static_cast<ComponentType>(v.x);
		this->y *= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator*=(vec<2, U, Q> const& v)
	{
		this->x *= static_cast<ComponentType>(v.x);
		this->y *= static_cast<ComponentType>(v.y);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator/=(U scalar)
	{
		this->x /= static_cast<ComponentType>(scalar);
		this->y /= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator/=(vec<1, U, Q> const& v)
	{
		this->x /= static_cast<ComponentType>(v.x);
		this->y /= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator/=(vec<2, U, Q> const& v)
	{
		this->x /= static_cast<ComponentType>(v.x);
		this->y /= static_cast<ComponentType>(v.y);
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator++()
	{
		++this->x;
		++this->y;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator--()
	{
		--this->x;
		--this->y;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> vec<2, ComponentType, Q>::operator++(int)
	{
		vec<2, ComponentType, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> vec<2, ComponentType, Q>::operator--(int)
	{
		vec<2, ComponentType, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator%=(U scalar)
	{
		this->x %= static_cast<ComponentType>(scalar);
		this->y %= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator%=(vec<1, U, Q> const& v)
	{
		this->x %= static_cast<ComponentType>(v.x);
		this->y %= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator%=(vec<2, U, Q> const& v)
	{
		this->x %= static_cast<ComponentType>(v.x);
		this->y %= static_cast<ComponentType>(v.y);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator&=(U scalar)
	{
		this->x &= static_cast<ComponentType>(scalar);
		this->y &= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator&=(vec<1, U, Q> const& v)
	{
		this->x &= static_cast<ComponentType>(v.x);
		this->y &= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator&=(vec<2, U, Q> const& v)
	{
		this->x &= static_cast<ComponentType>(v.x);
		this->y &= static_cast<ComponentType>(v.y);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator|=(U scalar)
	{
		this->x |= static_cast<ComponentType>(scalar);
		this->y |= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator|=(vec<1, U, Q> const& v)
	{
		this->x |= static_cast<ComponentType>(v.x);
		this->y |= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator|=(vec<2, U, Q> const& v)
	{
		this->x |= static_cast<ComponentType>(v.x);
		this->y |= static_cast<ComponentType>(v.y);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator^=(U scalar)
	{
		this->x ^= static_cast<ComponentType>(scalar);
		this->y ^= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator^=(vec<1, U, Q> const& v)
	{
		this->x ^= static_cast<ComponentType>(v.x);
		this->y ^= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator^=(vec<2, U, Q> const& v)
	{
		this->x ^= static_cast<ComponentType>(v.x);
		this->y ^= static_cast<ComponentType>(v.y);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator<<=(U scalar)
	{
		this->x <<= static_cast<ComponentType>(scalar);
		this->y <<= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator<<=(vec<1, U, Q> const& v)
	{
		this->x <<= static_cast<ComponentType>(v.x);
		this->y <<= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator<<=(vec<2, U, Q> const& v)
	{
		this->x <<= static_cast<ComponentType>(v.x);
		this->y <<= static_cast<ComponentType>(v.y);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator>>=(U scalar)
	{
		this->x >>= static_cast<ComponentType>(scalar);
		this->y >>= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator>>=(vec<1, U, Q> const& v)
	{
		this->x >>= static_cast<ComponentType>(v.x);
		this->y >>= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> & vec<2, ComponentType, Q>::operator>>=(vec<2, U, Q> const& v)
	{
		this->x >>= static_cast<ComponentType>(v.x);
		this->y >>= static_cast<ComponentType>(v.y);
		return *this;
	}

	// -- Unary arithmetic operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(vec<2, ComponentType, Q> const& v)
	{
		return v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			-v.x,
			-v.y);
	}

	// -- Binary arithmetic operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(vec<2, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<2, ComponentType, Q>(
			v.x + scalar,
			v.y + scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x + v2.x,
			v1.y + v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(ComponentType scalar, vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			scalar + v.x,
			scalar + v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x + v2.x,
			v1.x + v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator+(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x + v2.x,
			v1.y + v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(vec<2, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<2, ComponentType, Q>(
			v.x - scalar,
			v.y - scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x - v2.x,
			v1.y - v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(ComponentType scalar, vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			scalar - v.x,
			scalar - v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x - v2.x,
			v1.x - v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator-(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x - v2.x,
			v1.y - v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator*(vec<2, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<2, ComponentType, Q>(
			v.x * scalar,
			v.y * scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator*(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x * v2.x,
			v1.y * v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator*(ComponentType scalar, vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			scalar * v.x,
			scalar * v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator*(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x * v2.x,
			v1.x * v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator*(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x * v2.x,
			v1.y * v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator/(vec<2, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<2, ComponentType, Q>(
			v.x / scalar,
			v.y / scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator/(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x / v2.x,
			v1.y / v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator/(ComponentType scalar, vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			scalar / v.x,
			scalar / v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator/(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x / v2.x,
			v1.x / v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator/(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x / v2.x,
			v1.y / v2.y);
	}

	// -- Binary bit operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator%(vec<2, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<2, ComponentType, Q>(
			v.x % scalar,
			v.y % scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator%(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x % v2.x,
			v1.y % v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator%(ComponentType scalar, vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			scalar % v.x,
			scalar % v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator%(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x % v2.x,
			v1.x % v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator%(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x % v2.x,
			v1.y % v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator&(vec<2, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<2, ComponentType, Q>(
			v.x & scalar,
			v.y & scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator&(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x & v2.x,
			v1.y & v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator&(ComponentType scalar, vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			scalar & v.x,
			scalar & v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator&(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x & v2.x,
			v1.x & v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator&(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x & v2.x,
			v1.y & v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator|(vec<2, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<2, ComponentType, Q>(
			v.x | scalar,
			v.y | scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator|(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x | v2.x,
			v1.y | v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator|(ComponentType scalar, vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			scalar | v.x,
			scalar | v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator|(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x | v2.x,
			v1.x | v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator|(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x | v2.x,
			v1.y | v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator^(vec<2, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<2, ComponentType, Q>(
			v.x ^ scalar,
			v.y ^ scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator^(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x ^ v2.x,
			v1.y ^ v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator^(ComponentType scalar, vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			scalar ^ v.x,
			scalar ^ v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator^(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x ^ v2.x,
			v1.x ^ v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator^(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x ^ v2.x,
			v1.y ^ v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator<<(vec<2, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<2, ComponentType, Q>(
			v.x << scalar,
			v.y << scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator<<(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x << v2.x,
			v1.y << v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator<<(ComponentType scalar, vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			scalar << v.x,
			scalar << v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator<<(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x << v2.x,
			v1.x << v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator<<(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x << v2.x,
			v1.y << v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator>>(vec<2, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<2, ComponentType, Q>(
			v.x >> scalar,
			v.y >> scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator>>(vec<2, ComponentType, Q> const& v1, vec<1, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x >> v2.x,
			v1.y >> v2.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator>>(ComponentType scalar, vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			scalar >> v.x,
			scalar >> v.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator>>(vec<1, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x >> v2.x,
			v1.x >> v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator>>(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return vec<2, ComponentType, Q>(
			v1.x >> v2.x,
			v1.y >> v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, ComponentType, Q> operator~(vec<2, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(
			~v.x,
			~v.y);
	}

	// -- Boolean operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return
			detail::compute_equal<ComponentType, std::numeric_limits<ComponentType>::is_iec559>::call(v1.x, v2.x) &&
			detail::compute_equal<ComponentType, std::numeric_limits<ComponentType>::is_iec559>::call(v1.y, v2.y);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(vec<2, ComponentType, Q> const& v1, vec<2, ComponentType, Q> const& v2)
	{
		return !(v1 == v2);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, bool, Q> operator&&(vec<2, bool, Q> const& v1, vec<2, bool, Q> const& v2)
	{
		return vec<2, bool, Q>(v1.x && v2.x, v1.y && v2.y);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<2, bool, Q> operator||(vec<2, bool, Q> const& v1, vec<2, bool, Q> const& v2)
	{
		return vec<2, bool, Q>(v1.x || v2.x, v1.y || v2.y);
	}
}//namespace glm
