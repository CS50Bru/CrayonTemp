/// @ref core

#include "compute_vector_relational.hpp"

namespace glm
{
	// -- Implicit basic constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec()
#			if GLM_CONFIG_CTOR_INIT != GLM_CTOR_INIT_DISABLE
				: x(0), y(0), z(0)
#			endif
		{}

		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>::vec(vec<3, T, Q> const& v)
			: x(v.x), y(v.y), z(v.z)
		{}
#	endif

	template<typename ComponentType, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<3, ComponentType, P> const& v)
		: x(v.x), y(v.y), z(v.z)
	{}

	// -- Explicit basic constructors --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(ComponentType scalar)
		: x(scalar), y(scalar), z(scalar)
	{}

	template <typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(ComponentType _x, ComponentType _y, ComponentType _z)
		: x(_x), y(_y), z(_z)
	{}

	// -- Conversion scalar constructors --

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<1, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
		, y(static_cast<ComponentType>(v.x))
		, z(static_cast<ComponentType>(v.x))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(X _x, Y _y, Z _z)
		: x(static_cast<ComponentType>(_x))
		, y(static_cast<ComponentType>(_y))
		, z(static_cast<ComponentType>(_z))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<1, X, Q> const& _x, Y _y, Z _z)
		: x(static_cast<ComponentType>(_x.x))
		, y(static_cast<ComponentType>(_y))
		, z(static_cast<ComponentType>(_z))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(X _x, vec<1, Y, Q> const& _y, Z _z)
		: x(static_cast<ComponentType>(_x))
		, y(static_cast<ComponentType>(_y.x))
		, z(static_cast<ComponentType>(_z))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, Z _z)
		: x(static_cast<ComponentType>(_x.x))
		, y(static_cast<ComponentType>(_y.x))
		, z(static_cast<ComponentType>(_z))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(X _x, Y _y, vec<1, Z, Q> const& _z)
		: x(static_cast<ComponentType>(_x))
		, y(static_cast<ComponentType>(_y))
		, z(static_cast<ComponentType>(_z.x))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<1, X, Q> const& _x, Y _y, vec<1, Z, Q> const& _z)
		: x(static_cast<ComponentType>(_x.x))
		, y(static_cast<ComponentType>(_y))
		, z(static_cast<ComponentType>(_z.x))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(X _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z)
		: x(static_cast<ComponentType>(_x))
		, y(static_cast<ComponentType>(_y.x))
		, z(static_cast<ComponentType>(_z.x))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename X, typename Y, typename Z>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<1, X, Q> const& _x, vec<1, Y, Q> const& _y, vec<1, Z, Q> const& _z)
		: x(static_cast<ComponentType>(_x.x))
		, y(static_cast<ComponentType>(_y.x))
		, z(static_cast<ComponentType>(_z.x))
	{}

	// -- Conversion vector constructors --

	template<typename ComponentType, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<2, A, P> const& _xy, B _z)
		: x(static_cast<ComponentType>(_xy.x))
		, y(static_cast<ComponentType>(_xy.y))
		, z(static_cast<ComponentType>(_z))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<2, A, P> const& _xy, vec<1, B, P> const& _z)
		: x(static_cast<ComponentType>(_xy.x))
		, y(static_cast<ComponentType>(_xy.y))
		, z(static_cast<ComponentType>(_z.x))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(A _x, vec<2, B, P> const& _yz)
		: x(static_cast<ComponentType>(_x))
		, y(static_cast<ComponentType>(_yz.x))
		, z(static_cast<ComponentType>(_yz.y))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename A, typename B, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<1, A, P> const& _x, vec<2, B, P> const& _yz)
		: x(static_cast<ComponentType>(_x.x))
		, y(static_cast<ComponentType>(_yz.x))
		, z(static_cast<ComponentType>(_yz.y))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<3, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
		, y(static_cast<ComponentType>(v.y))
		, z(static_cast<ComponentType>(v.z))
	{}

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>::vec(vec<4, U, P> const& v)
		: x(static_cast<ComponentType>(v.x))
		, y(static_cast<ComponentType>(v.y))
		, z(static_cast<ComponentType>(v.z))
	{}

	// -- ComponentIdentifier accesses --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR ComponentType & vec<3, ComponentType, Q>::operator[](typename vec<3, ComponentType, Q>::length_type i)
	{
		assert(i >= 0 && i < this->length());
		switch(i)
		{
		default:
			case 0:
		return x;
			case 1:
		return y;
			case 2:
		return z;
		}
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR ComponentType const& vec<3, ComponentType, Q>::operator[](typename vec<3, ComponentType, Q>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
		switch(i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}

	// -- Unary arithmetic operators --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, T, Q>& vec<3, T, Q>::operator=(vec<3, T, Q> const& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return *this;
		}
#	endif

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q>& vec<3, ComponentType, Q>::operator=(vec<3, U, Q> const& v)
	{
		this->x = static_cast<ComponentType>(v.x);
		this->y = static_cast<ComponentType>(v.y);
		this->z = static_cast<ComponentType>(v.z);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator+=(U scalar)
	{
		this->x += static_cast<ComponentType>(scalar);
		this->y += static_cast<ComponentType>(scalar);
		this->z += static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator+=(vec<1, U, Q> const& v)
	{
		this->x += static_cast<ComponentType>(v.x);
		this->y += static_cast<ComponentType>(v.x);
		this->z += static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator+=(vec<3, U, Q> const& v)
	{
		this->x += static_cast<ComponentType>(v.x);
		this->y += static_cast<ComponentType>(v.y);
		this->z += static_cast<ComponentType>(v.z);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator-=(U scalar)
	{
		this->x -= static_cast<ComponentType>(scalar);
		this->y -= static_cast<ComponentType>(scalar);
		this->z -= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator-=(vec<1, U, Q> const& v)
	{
		this->x -= static_cast<ComponentType>(v.x);
		this->y -= static_cast<ComponentType>(v.x);
		this->z -= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator-=(vec<3, U, Q> const& v)
	{
		this->x -= static_cast<ComponentType>(v.x);
		this->y -= static_cast<ComponentType>(v.y);
		this->z -= static_cast<ComponentType>(v.z);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator*=(U scalar)
	{
		this->x *= static_cast<ComponentType>(scalar);
		this->y *= static_cast<ComponentType>(scalar);
		this->z *= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator*=(vec<1, U, Q> const& v)
	{
		this->x *= static_cast<ComponentType>(v.x);
		this->y *= static_cast<ComponentType>(v.x);
		this->z *= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator*=(vec<3, U, Q> const& v)
	{
		this->x *= static_cast<ComponentType>(v.x);
		this->y *= static_cast<ComponentType>(v.y);
		this->z *= static_cast<ComponentType>(v.z);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator/=(U v)
	{
		this->x /= static_cast<ComponentType>(v);
		this->y /= static_cast<ComponentType>(v);
		this->z /= static_cast<ComponentType>(v);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator/=(vec<1, U, Q> const& v)
	{
		this->x /= static_cast<ComponentType>(v.x);
		this->y /= static_cast<ComponentType>(v.x);
		this->z /= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator/=(vec<3, U, Q> const& v)
	{
		this->x /= static_cast<ComponentType>(v.x);
		this->y /= static_cast<ComponentType>(v.y);
		this->z /= static_cast<ComponentType>(v.z);
		return *this;
	}

	// -- Increment and decrement operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator++()
	{
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator--()
	{
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> vec<3, ComponentType, Q>::operator++(int)
	{
		vec<3, ComponentType, Q> Result(*this);
		++*this;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> vec<3, ComponentType, Q>::operator--(int)
	{
		vec<3, ComponentType, Q> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator%=(U scalar)
	{
		this->x %= scalar;
		this->y %= scalar;
		this->z %= scalar;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator%=(vec<1, U, Q> const& v)
	{
		this->x %= v.x;
		this->y %= v.x;
		this->z %= v.x;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator%=(vec<3, U, Q> const& v)
	{
		this->x %= v.x;
		this->y %= v.y;
		this->z %= v.z;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator&=(U scalar)
	{
		this->x &= scalar;
		this->y &= scalar;
		this->z &= scalar;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator&=(vec<1, U, Q> const& v)
	{
		this->x &= v.x;
		this->y &= v.x;
		this->z &= v.x;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator&=(vec<3, U, Q> const& v)
	{
		this->x &= v.x;
		this->y &= v.y;
		this->z &= v.z;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator|=(U scalar)
	{
		this->x |= scalar;
		this->y |= scalar;
		this->z |= scalar;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator|=(vec<1, U, Q> const& v)
	{
		this->x |= v.x;
		this->y |= v.x;
		this->z |= v.x;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator|=(vec<3, U, Q> const& v)
	{
		this->x |= v.x;
		this->y |= v.y;
		this->z |= v.z;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator^=(U scalar)
	{
		this->x ^= scalar;
		this->y ^= scalar;
		this->z ^= scalar;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator^=(vec<1, U, Q> const& v)
	{
		this->x ^= v.x;
		this->y ^= v.x;
		this->z ^= v.x;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator^=(vec<3, U, Q> const& v)
	{
		this->x ^= v.x;
		this->y ^= v.y;
		this->z ^= v.z;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator<<=(U scalar)
	{
		this->x <<= scalar;
		this->y <<= scalar;
		this->z <<= scalar;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator<<=(vec<1, U, Q> const& v)
	{
		this->x <<= static_cast<ComponentType>(v.x);
		this->y <<= static_cast<ComponentType>(v.x);
		this->z <<= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator<<=(vec<3, U, Q> const& v)
	{
		this->x <<= static_cast<ComponentType>(v.x);
		this->y <<= static_cast<ComponentType>(v.y);
		this->z <<= static_cast<ComponentType>(v.z);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator>>=(U scalar)
	{
		this->x >>= static_cast<ComponentType>(scalar);
		this->y >>= static_cast<ComponentType>(scalar);
		this->z >>= static_cast<ComponentType>(scalar);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator>>=(vec<1, U, Q> const& v)
	{
		this->x >>= static_cast<ComponentType>(v.x);
		this->y >>= static_cast<ComponentType>(v.x);
		this->z >>= static_cast<ComponentType>(v.x);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> & vec<3, ComponentType, Q>::operator>>=(vec<3, U, Q> const& v)
	{
		this->x >>= static_cast<ComponentType>(v.x);
		this->y >>= static_cast<ComponentType>(v.y);
		this->z >>= static_cast<ComponentType>(v.z);
		return *this;
	}

	// -- Unary arithmetic operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator+(vec<3, ComponentType, Q> const& v)
	{
		return v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator-(vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			-v.x,
			-v.y,
			-v.z);
	}

	// -- Binary arithmetic operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator+(vec<3, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x + scalar,
			v.y + scalar,
			v.z + scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator+(vec<3, ComponentType, Q> const& v, vec<1, ComponentType, Q> const& scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x + scalar.x,
			v.y + scalar.x,
			v.z + scalar.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator+(ComponentType scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar + v.x,
			scalar + v.y,
			scalar + v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator+(vec<1, ComponentType, Q> const& scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar.x + v.x,
			scalar.x + v.y,
			scalar.x + v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator+(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return vec<3, ComponentType, Q>(
			v1.x + v2.x,
			v1.y + v2.y,
			v1.z + v2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator-(vec<3, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x - scalar,
			v.y - scalar,
			v.z - scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator-(vec<3, ComponentType, Q> const& v, vec<1, ComponentType, Q> const& scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x - scalar.x,
			v.y - scalar.x,
			v.z - scalar.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator-(ComponentType scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar - v.x,
			scalar - v.y,
			scalar - v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator-(vec<1, ComponentType, Q> const& scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar.x - v.x,
			scalar.x - v.y,
			scalar.x - v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator-(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return vec<3, ComponentType, Q>(
			v1.x - v2.x,
			v1.y - v2.y,
			v1.z - v2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator*(vec<3, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x * scalar,
			v.y * scalar,
			v.z * scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator*(vec<3, ComponentType, Q> const& v, vec<1, ComponentType, Q> const& scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x * scalar.x,
			v.y * scalar.x,
			v.z * scalar.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator*(ComponentType scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar * v.x,
			scalar * v.y,
			scalar * v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator*(vec<1, ComponentType, Q> const& scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar.x * v.x,
			scalar.x * v.y,
			scalar.x * v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator*(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return vec<3, ComponentType, Q>(
			v1.x * v2.x,
			v1.y * v2.y,
			v1.z * v2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator/(vec<3, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x / scalar,
			v.y / scalar,
			v.z / scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator/(vec<3, ComponentType, Q> const& v, vec<1, ComponentType, Q> const& scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x / scalar.x,
			v.y / scalar.x,
			v.z / scalar.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator/(ComponentType scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar / v.x,
			scalar / v.y,
			scalar / v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator/(vec<1, ComponentType, Q> const& scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar.x / v.x,
			scalar.x / v.y,
			scalar.x / v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator/(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return vec<3, ComponentType, Q>(
			v1.x / v2.x,
			v1.y / v2.y,
			v1.z / v2.z);
	}

	// -- Binary bit operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator%(vec<3, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x % scalar,
			v.y % scalar,
			v.z % scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator%(vec<3, ComponentType, Q> const& v, vec<1, ComponentType, Q> const& scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x % scalar.x,
			v.y % scalar.x,
			v.z % scalar.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator%(ComponentType scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar % v.x,
			scalar % v.y,
			scalar % v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator%(vec<1, ComponentType, Q> const& scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar.x % v.x,
			scalar.x % v.y,
			scalar.x % v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator%(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return vec<3, ComponentType, Q>(
			v1.x % v2.x,
			v1.y % v2.y,
			v1.z % v2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator&(vec<3, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x & scalar,
			v.y & scalar,
			v.z & scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator&(vec<3, ComponentType, Q> const& v, vec<1, ComponentType, Q> const& scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x & scalar.x,
			v.y & scalar.x,
			v.z & scalar.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator&(ComponentType scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar & v.x,
			scalar & v.y,
			scalar & v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator&(vec<1, ComponentType, Q> const& scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar.x & v.x,
			scalar.x & v.y,
			scalar.x & v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator&(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return vec<3, ComponentType, Q>(
			v1.x & v2.x,
			v1.y & v2.y,
			v1.z & v2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator|(vec<3, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x | scalar,
			v.y | scalar,
			v.z | scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator|(vec<3, ComponentType, Q> const& v, vec<1, ComponentType, Q> const& scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x | scalar.x,
			v.y | scalar.x,
			v.z | scalar.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator|(ComponentType scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar | v.x,
			scalar | v.y,
			scalar | v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator|(vec<1, ComponentType, Q> const& scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar.x | v.x,
			scalar.x | v.y,
			scalar.x | v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator|(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return vec<3, ComponentType, Q>(
			v1.x | v2.x,
			v1.y | v2.y,
			v1.z | v2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator^(vec<3, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x ^ scalar,
			v.y ^ scalar,
			v.z ^ scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator^(vec<3, ComponentType, Q> const& v, vec<1, ComponentType, Q> const& scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x ^ scalar.x,
			v.y ^ scalar.x,
			v.z ^ scalar.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator^(ComponentType scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar ^ v.x,
			scalar ^ v.y,
			scalar ^ v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator^(vec<1, ComponentType, Q> const& scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar.x ^ v.x,
			scalar.x ^ v.y,
			scalar.x ^ v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator^(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return vec<3, ComponentType, Q>(
			v1.x ^ v2.x,
			v1.y ^ v2.y,
			v1.z ^ v2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator<<(vec<3, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x << scalar,
			v.y << scalar,
			v.z << scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator<<(vec<3, ComponentType, Q> const& v, vec<1, ComponentType, Q> const& scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x << scalar.x,
			v.y << scalar.x,
			v.z << scalar.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator<<(ComponentType scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar << v.x,
			scalar << v.y,
			scalar << v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator<<(vec<1, ComponentType, Q> const& scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar.x << v.x,
			scalar.x << v.y,
			scalar.x << v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator<<(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return vec<3, ComponentType, Q>(
			v1.x << v2.x,
			v1.y << v2.y,
			v1.z << v2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator>>(vec<3, ComponentType, Q> const& v, ComponentType scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x >> scalar,
			v.y >> scalar,
			v.z >> scalar);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator>>(vec<3, ComponentType, Q> const& v, vec<1, ComponentType, Q> const& scalar)
	{
		return vec<3, ComponentType, Q>(
			v.x >> scalar.x,
			v.y >> scalar.x,
			v.z >> scalar.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator>>(ComponentType scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar >> v.x,
			scalar >> v.y,
			scalar >> v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator>>(vec<1, ComponentType, Q> const& scalar, vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			scalar.x >> v.x,
			scalar.x >> v.y,
			scalar.x >> v.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator>>(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return vec<3, ComponentType, Q>(
			v1.x >> v2.x,
			v1.y >> v2.y,
			v1.z >> v2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator~(vec<3, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(
			~v.x,
			~v.y,
			~v.z);
	}

	// -- Boolean operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return
			detail::compute_equal<ComponentType, std::numeric_limits<ComponentType>::is_iec559>::call(v1.x, v2.x) &&
			detail::compute_equal<ComponentType, std::numeric_limits<ComponentType>::is_iec559>::call(v1.y, v2.y) &&
			detail::compute_equal<ComponentType, std::numeric_limits<ComponentType>::is_iec559>::call(v1.z, v2.z);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(vec<3, ComponentType, Q> const& v1, vec<3, ComponentType, Q> const& v2)
	{
		return !(v1 == v2);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, bool, Q> operator&&(vec<3, bool, Q> const& v1, vec<3, bool, Q> const& v2)
	{
		return vec<3, bool, Q>(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z);
	}

	template<qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, bool, Q> operator||(vec<3, bool, Q> const& v1, vec<3, bool, Q> const& v2)
	{
		return vec<3, bool, Q>(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z);
	}
}//namespace glm
