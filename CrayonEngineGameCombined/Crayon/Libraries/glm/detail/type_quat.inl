#include "../trigonometric.hpp"
#include "../exponential.hpp"
#include "../ext/quaternion_geometric.hpp"
#include <limits>

namespace glm{
namespace detail
{
	template <typename ComponentType>
	struct genTypeTrait<qua<ComponentType> >
	{
		static const genTypeEnum GENTYPE = GENTYPE_QUAT;
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_dot<qua<ComponentType, Q>, ComponentType, Aligned>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static ComponentType call(qua<ComponentType, Q> const& a, qua<ComponentType, Q> const& b)
		{
			vec<4, ComponentType, Q> tmp(a.w * b.w, a.x * b.x, a.y * b.y, a.z * b.z);
			return (tmp.x + tmp.y) + (tmp.z + tmp.w);
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_quat_add
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static qua<ComponentType, Q> call(qua<ComponentType, Q> const& q, qua<ComponentType, Q> const& p)
		{
			return qua<ComponentType, Q>(q.w + p.w, q.x + p.x, q.y + p.y, q.z + p.z);
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_quat_sub
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static qua<ComponentType, Q> call(qua<ComponentType, Q> const& q, qua<ComponentType, Q> const& p)
		{
			return qua<ComponentType, Q>(q.w - p.w, q.x - p.x, q.y - p.y, q.z - p.z);
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_quat_mul_scalar
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static qua<ComponentType, Q> call(qua<ComponentType, Q> const& q, ComponentType s)
		{
			return qua<ComponentType, Q>(q.w * s, q.x * s, q.y * s, q.z * s);
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_quat_div_scalar
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static qua<ComponentType, Q> call(qua<ComponentType, Q> const& q, ComponentType s)
		{
			return qua<ComponentType, Q>(q.w / s, q.x / s, q.y / s, q.z / s);
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_quat_mul_vec4
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static vec<4, ComponentType, Q> call(qua<ComponentType, Q> const& q, vec<4, ComponentType, Q> const& v)
		{
			return vec<4, ComponentType, Q>(q * vec<3, ComponentType, Q>(v), v.w);
		}
	};
}//namespace detail

	// -- ComponentIdentifier accesses --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR ComponentType & qua<ComponentType, Q>::operator[](typename qua<ComponentType, Q>::length_type i)
	{
		assert(i >= 0 && i < this->length());
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			return (&w)[i];
#		else
			return (&x)[i];
#		endif
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR ComponentType const& qua<ComponentType, Q>::operator[](typename qua<ComponentType, Q>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			return (&w)[i];
#		else
			return (&x)[i];
#		endif
	}

	// -- Implicit basic constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q>::qua()
#			if GLM_CONFIG_CTOR_INIT != GLM_CTOR_INIT_DISABLE
#				ifdef GLM_FORCE_QUAT_DATA_WXYZ
					: w(1), x(0), y(0), z(0)
#				else
					: x(0), y(0), z(0), w(1)
#				endif
#			endif
		{}

		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q>::qua(qua<T, Q> const& q)
#			ifdef GLM_FORCE_QUAT_DATA_WXYZ
				: w(q.w), x(q.x), y(q.y), z(q.z)
#			else
				: x(q.x), y(q.y), z(q.z), w(q.w)
#			endif
		{}
#	endif

	template<typename ComponentType, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q>::qua(qua<ComponentType, P> const& q)
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			: w(q.w), x(q.x), y(q.y), z(q.z)
#		else
			: x(q.x), y(q.y), z(q.z), w(q.w)
#		endif
	{}

	// -- Explicit basic constructors --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q>::qua(ComponentType s, vec<3, ComponentType, Q> const& v)
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			: w(s), x(v.x), y(v.y), z(v.z)
#		else
			: x(v.x), y(v.y), z(v.z), w(s)
#		endif
	{}

	template <typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q>::qua(ComponentType _w, ComponentType _x, ComponentType _y, ComponentType _z)
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			: w(_w), x(_x), y(_y), z(_z)
#		else
			: x(_x), y(_y), z(_z), w(_w)
#		endif
	{}

	// -- Conversion constructors --

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q>::qua(qua<U, P> const& q)
#		ifdef GLM_FORCE_QUAT_DATA_WXYZ
			: w(static_cast<T>(q.w)), x(static_cast<T>(q.x)), y(static_cast<T>(q.y)), z(static_cast<T>(q.z))
#		else
			: x(static_cast<ComponentType>(q.x)), y(static_cast<ComponentType>(q.y)), z(static_cast<ComponentType>(q.z)), w(static_cast<ComponentType>(q.w))
#		endif
	{}

	//template<typename valType>
	//GLM_FUNC_QUALIFIER qua<valType>::qua
	//(
	//	valType const& pitch,
	//	valType const& yaw,
	//	valType const& roll
	//)
	//{
	//	vec<3, valType> eulerAngle(pitch * valType(0.5), yaw * valType(0.5), roll * valType(0.5));
	//	vec<3, valType> c = glm::cos(eulerAngle * valType(0.5));
	//	vec<3, valType> s = glm::sin(eulerAngle * valType(0.5));
	//
	//	this->w = c.x * c.y * c.z + s.x * s.y * s.z;
	//	this->x = s.x * c.y * c.z - c.x * s.y * s.z;
	//	this->y = c.x * s.y * c.z + s.x * c.y * s.z;
	//	this->z = c.x * c.y * s.z - s.x * s.y * c.z;
	//}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q>::qua(vec<3, ComponentType, Q> const& u, vec<3, ComponentType, Q> const& v)
	{
		ComponentType norm_u_norm_v = sqrt(dot(u, u) * dot(v, v));
		ComponentType real_part = norm_u_norm_v + dot(u, v);
		vec<3, ComponentType, Q> t;

		if(real_part < static_cast<ComponentType>(1.e-6f) * norm_u_norm_v)
		{
			// If u and v are exactly opposite, rotate 180 degrees
			// around an arbitrary orthogonal axis. Axis normalisation
			// can happen later, when we normalise the quaternion.
			real_part = static_cast<ComponentType>(0);
			t = abs(u.x) > abs(u.z) ? vec<3, ComponentType, Q>(-u.y, u.x, static_cast<ComponentType>(0)) : vec<3, ComponentType, Q>(static_cast<ComponentType>(0), -u.z, u.y);
		}
		else
		{
			// Otherwise, build quaternion the standard way.
			t = cross(u, v);
		}

		*this = normalize(qua<ComponentType, Q>(real_part, t.x, t.y, t.z));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q>::qua(vec<3, ComponentType, Q> const& eulerAngle)
	{
		vec<3, ComponentType, Q> c = glm::cos(eulerAngle * ComponentType(0.5));
		vec<3, ComponentType, Q> s = glm::sin(eulerAngle * ComponentType(0.5));

		this->w = c.x * c.y * c.z + s.x * s.y * s.z;
		this->x = s.x * c.y * c.z - c.x * s.y * s.z;
		this->y = c.x * s.y * c.z + s.x * c.y * s.z;
		this->z = c.x * c.y * s.z - s.x * s.y * c.z;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q>::qua(mat<3, 3, ComponentType, Q> const& m)
	{
		*this = quat_cast(m);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q>::qua(mat<4, 4, ComponentType, Q> const& m)
	{
		*this = quat_cast(m);
	}

#	if GLM_HAS_EXPLICIT_CONVERSION_OPERATORS
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q>::operator mat<3, 3, ComponentType, Q>() const
	{
		return mat3_cast(*this);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER qua<ComponentType, Q>::operator mat<4, 4, ComponentType, Q>() const
	{
		return mat4_cast(*this);
	}
#	endif//GLM_HAS_EXPLICIT_CONVERSION_OPERATORS

	// -- Unary arithmetic operators --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<T, Q> & qua<T, Q>::operator=(qua<T, Q> const& q)
		{
			this->w = q.w;
			this->x = q.x;
			this->y = q.y;
			this->z = q.z;
			return *this;
		}
#	endif

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> & qua<ComponentType, Q>::operator=(qua<U, Q> const& q)
	{
		this->w = static_cast<ComponentType>(q.w);
		this->x = static_cast<ComponentType>(q.x);
		this->y = static_cast<ComponentType>(q.y);
		this->z = static_cast<ComponentType>(q.z);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> & qua<ComponentType, Q>::operator+=(qua<U, Q> const& q)
	{
		return (*this = detail::compute_quat_add<ComponentType, Q, detail::is_aligned<Q>::value>::call(*this, qua<ComponentType, Q>(q)));
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> & qua<ComponentType, Q>::operator-=(qua<U, Q> const& q)
	{
		return (*this = detail::compute_quat_sub<ComponentType, Q, detail::is_aligned<Q>::value>::call(*this, qua<ComponentType, Q>(q)));
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> & qua<ComponentType, Q>::operator*=(qua<U, Q> const& r)
	{
		qua<ComponentType, Q> const p(*this);
		qua<ComponentType, Q> const q(r);

		this->w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
		this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
		this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
		this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> & qua<ComponentType, Q>::operator*=(U s)
	{
		return (*this = detail::compute_quat_mul_scalar<ComponentType, Q, detail::is_aligned<Q>::value>::call(*this, static_cast<U>(s)));
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> & qua<ComponentType, Q>::operator/=(U s)
	{
		return (*this = detail::compute_quat_div_scalar<ComponentType, Q, detail::is_aligned<Q>::value>::call(*this, static_cast<U>(s)));
	}

	// -- Unary bit operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> operator+(qua<ComponentType, Q> const& q)
	{
		return q;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> operator-(qua<ComponentType, Q> const& q)
	{
		return qua<ComponentType, Q>(-q.w, -q.x, -q.y, -q.z);
	}

	// -- Binary operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> operator+(qua<ComponentType, Q> const& q, qua<ComponentType, Q> const& p)
	{
		return qua<ComponentType, Q>(q) += p;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> operator-(qua<ComponentType, Q> const& q, qua<ComponentType, Q> const& p)
	{
		return qua<ComponentType, Q>(q) -= p;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> operator*(qua<ComponentType, Q> const& q, qua<ComponentType, Q> const& p)
	{
		return qua<ComponentType, Q>(q) *= p;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator*(qua<ComponentType, Q> const& q, vec<3, ComponentType, Q> const& v)
	{
		vec<3, ComponentType, Q> const QuatVector(q.x, q.y, q.z);
		vec<3, ComponentType, Q> const uv(glm::cross(QuatVector, v));
		vec<3, ComponentType, Q> const uuv(glm::cross(QuatVector, uv));

		return v + ((uv * q.w) + uuv) * static_cast<ComponentType>(2);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<3, ComponentType, Q> operator*(vec<3, ComponentType, Q> const& v, qua<ComponentType, Q> const& q)
	{
		return glm::inverse(q) * v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, ComponentType, Q> operator*(qua<ComponentType, Q> const& q, vec<4, ComponentType, Q> const& v)
	{
		return detail::compute_quat_mul_vec4<ComponentType, Q, detail::is_aligned<Q>::value>::call(q, v);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR vec<4, ComponentType, Q> operator*(vec<4, ComponentType, Q> const& v, qua<ComponentType, Q> const& q)
	{
		return glm::inverse(q) * v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> operator*(qua<ComponentType, Q> const& q, ComponentType const& s)
	{
		return qua<ComponentType, Q>(
			q.w * s, q.x * s, q.y * s, q.z * s);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> operator*(ComponentType const& s, qua<ComponentType, Q> const& q)
	{
		return q * s;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR qua<ComponentType, Q> operator/(qua<ComponentType, Q> const& q, ComponentType const& s)
	{
		return qua<ComponentType, Q>(
			q.w / s, q.x / s, q.y / s, q.z / s);
	}

	// -- Boolean operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator==(qua<ComponentType, Q> const& q1, qua<ComponentType, Q> const& q2)
	{
		return q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR bool operator!=(qua<ComponentType, Q> const& q1, qua<ComponentType, Q> const& q2)
	{
		return q1.x != q2.x || q1.y != q2.y || q1.z != q2.z || q1.w != q2.w;
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "type_quat_simd.inl"
#endif

