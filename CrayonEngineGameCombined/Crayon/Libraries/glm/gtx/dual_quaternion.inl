/// @ref gtx_dual_quaternion

#include "../geometric.hpp"
#include <limits>

namespace glm
{
	// -- ComponentIdentifier accesses --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER typename tdualquat<ComponentType, Q>::part_type & tdualquat<ComponentType, Q>::operator[](typename tdualquat<ComponentType, Q>::length_type i)
	{
		assert(i >= 0 && i < this->length());
		return (&real)[i];
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER typename tdualquat<ComponentType, Q>::part_type const& tdualquat<ComponentType, Q>::operator[](typename tdualquat<ComponentType, Q>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
		return (&real)[i];
	}

	// -- Implicit basic constructors --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR tdualquat<T, Q>::tdualquat()
#			if GLM_CONFIG_DEFAULTED_FUNCTIONS != GLM_DISABLE
			: real(qua<T, Q>())
			, dual(qua<T, Q>(0, 0, 0, 0))
#			endif
		{}

		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR tdualquat<T, Q>::tdualquat(tdualquat<T, Q> const& d)
			: real(d.real)
			, dual(d.dual)
		{}
#	endif

	template<typename ComponentType, qualifier Q>
	template<qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR tdualquat<ComponentType, Q>::tdualquat(tdualquat<ComponentType, P> const& d)
		: real(d.real)
		, dual(d.dual)
	{}

	// -- Explicit basic constructors --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR tdualquat<ComponentType, Q>::tdualquat(qua<ComponentType, Q> const& r)
		: real(r), dual(qua<ComponentType, Q>(0, 0, 0, 0))
	{}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR tdualquat<ComponentType, Q>::tdualquat(qua<ComponentType, Q> const& q, vec<3, ComponentType, Q> const& p)
		: real(q), dual(
			ComponentType(-0.5) * ( p.x*q.x + p.y*q.y + p.z*q.z),
			ComponentType(+0.5) * ( p.x*q.w + p.y*q.z - p.z*q.y),
			ComponentType(+0.5) * (-p.x*q.z + p.y*q.w + p.z*q.x),
			ComponentType(+0.5) * ( p.x*q.y - p.y*q.x + p.z*q.w))
	{}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR tdualquat<ComponentType, Q>::tdualquat(qua<ComponentType, Q> const& r, qua<ComponentType, Q> const& d)
		: real(r), dual(d)
	{}

	// -- Conversion constructors --

	template<typename ComponentType, qualifier Q>
	template<typename U, qualifier P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR tdualquat<ComponentType, Q>::tdualquat(tdualquat<U, P> const& q)
		: real(q.real)
		, dual(q.dual)
	{}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR tdualquat<ComponentType, Q>::tdualquat(mat<2, 4, ComponentType, Q> const& m)
	{
		*this = dualquat_cast(m);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR tdualquat<ComponentType, Q>::tdualquat(mat<3, 4, ComponentType, Q> const& m)
	{
		*this = dualquat_cast(m);
	}

	// -- Unary arithmetic operators --

#	if GLM_CONFIG_DEFAULTED_FUNCTIONS == GLM_DISABLE
		template<typename T, qualifier Q>
		GLM_FUNC_QUALIFIER tdualquat<T, Q> & tdualquat<T, Q>::operator=(tdualquat<T, Q> const& q)
		{
			this->real = q.real;
			this->dual = q.dual;
			return *this;
		}
#	endif

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> & tdualquat<ComponentType, Q>::operator=(tdualquat<U, Q> const& q)
	{
		this->real = q.real;
		this->dual = q.dual;
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> & tdualquat<ComponentType, Q>::operator*=(U s)
	{
		this->real *= static_cast<ComponentType>(s);
		this->dual *= static_cast<ComponentType>(s);
		return *this;
	}

	template<typename ComponentType, qualifier Q>
	template<typename U>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> & tdualquat<ComponentType, Q>::operator/=(U s)
	{
		this->real /= static_cast<ComponentType>(s);
		this->dual /= static_cast<ComponentType>(s);
		return *this;
	}

	// -- Unary bit operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> operator+(tdualquat<ComponentType, Q> const& q)
	{
		return q;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> operator-(tdualquat<ComponentType, Q> const& q)
	{
		return tdualquat<ComponentType, Q>(-q.real, -q.dual);
	}

	// -- Binary operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> operator+(tdualquat<ComponentType, Q> const& q, tdualquat<ComponentType, Q> const& p)
	{
		return tdualquat<ComponentType, Q>(q.real + p.real,q.dual + p.dual);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> operator*(tdualquat<ComponentType, Q> const& p, tdualquat<ComponentType, Q> const& o)
	{
		return tdualquat<ComponentType, Q>(p.real * o.real,p.real * o.dual + p.dual * o.real);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> operator*(tdualquat<ComponentType, Q> const& q, vec<3, ComponentType, Q> const& v)
	{
		vec<3, ComponentType, Q> const real_v3(q.real.x,q.real.y,q.real.z);
		vec<3, ComponentType, Q> const dual_v3(q.dual.x,q.dual.y,q.dual.z);
		return (cross(real_v3, cross(real_v3,v) + v * q.real.w + dual_v3) + dual_v3 * q.real.w - real_v3 * q.dual.w) * ComponentType(2) + v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> operator*(vec<3, ComponentType, Q> const& v,	tdualquat<ComponentType, Q> const& q)
	{
		return glm::inverse(q) * v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> operator*(tdualquat<ComponentType, Q> const& q, vec<4, ComponentType, Q> const& v)
	{
		return vec<4, ComponentType, Q>(q * vec<3, ComponentType, Q>(v), v.w);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> operator*(vec<4, ComponentType, Q> const& v,	tdualquat<ComponentType, Q> const& q)
	{
		return glm::inverse(q) * v;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> operator*(tdualquat<ComponentType, Q> const& q, ComponentType const& s)
	{
		return tdualquat<ComponentType, Q>(q.real * s, q.dual * s);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> operator*(ComponentType const& s, tdualquat<ComponentType, Q> const& q)
	{
		return q * s;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> operator/(tdualquat<ComponentType, Q> const& q,	ComponentType const& s)
	{
		return tdualquat<ComponentType, Q>(q.real / s, q.dual / s);
	}

	// -- Boolean operators --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator==(tdualquat<ComponentType, Q> const& q1, tdualquat<ComponentType, Q> const& q2)
	{
		return (q1.real == q2.real) && (q1.dual == q2.dual);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER bool operator!=(tdualquat<ComponentType, Q> const& q1, tdualquat<ComponentType, Q> const& q2)
	{
		return (q1.real != q2.real) || (q1.dual != q2.dual);
	}

	// -- Operations --

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> dual_quat_identity()
	{
		return tdualquat<ComponentType, Q>(
			qua<ComponentType, Q>(static_cast<ComponentType>(1), static_cast<ComponentType>(0), static_cast<ComponentType>(0), static_cast<ComponentType>(0)),
			qua<ComponentType, Q>(static_cast<ComponentType>(0), static_cast<ComponentType>(0), static_cast<ComponentType>(0), static_cast<ComponentType>(0)));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> normalize(tdualquat<ComponentType, Q> const& q)
	{
		return q / length(q.real);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> lerp(tdualquat<ComponentType, Q> const& x, tdualquat<ComponentType, Q> const& y, ComponentType const& a)
	{
		// Dual Quaternion Linear blend aka DLB:
		// Lerp is only defined in [0, 1]
		assert(a >= static_cast<ComponentType>(0));
		assert(a <= static_cast<ComponentType>(1));
		ComponentType const k = dot(x.real,y.real) < static_cast<ComponentType>(0) ? -a : a;
		ComponentType const one(1);
		return tdualquat<ComponentType, Q>(x * (one - a) + y * k);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> inverse(tdualquat<ComponentType, Q> const& q)
	{
		const glm::qua<ComponentType, Q> real = conjugate(q.real);
		const glm::qua<ComponentType, Q> dual = conjugate(q.dual);
		return tdualquat<ComponentType, Q>(real, dual + (real * (-2.0f * dot(real,dual))));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<2, 4, ComponentType, Q> mat2x4_cast(tdualquat<ComponentType, Q> const& x)
	{
		return mat<2, 4, ComponentType, Q>( x[0].x, x[0].y, x[0].z, x[0].w, x[1].x, x[1].y, x[1].z, x[1].w );
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 4, ComponentType, Q> mat3x4_cast(tdualquat<ComponentType, Q> const& x)
	{
		qua<ComponentType, Q> r = x.real / length2(x.real);

		qua<ComponentType, Q> const rr(r.w * x.real.w, r.x * x.real.x, r.y * x.real.y, r.z * x.real.z);
		r *= static_cast<ComponentType>(2);

		ComponentType const xy = r.x * x.real.y;
		ComponentType const xz = r.x * x.real.z;
		ComponentType const yz = r.y * x.real.z;
		ComponentType const wx = r.w * x.real.x;
		ComponentType const wy = r.w * x.real.y;
		ComponentType const wz = r.w * x.real.z;

		vec<4, ComponentType, Q> const a(
			rr.w + rr.x - rr.y - rr.z,
			xy - wz,
			xz + wy,
			-(x.dual.w * r.x - x.dual.x * r.w + x.dual.y * r.z - x.dual.z * r.y));

		vec<4, ComponentType, Q> const b(
			xy + wz,
			rr.w + rr.y - rr.x - rr.z,
			yz - wx,
			-(x.dual.w * r.y - x.dual.x * r.z - x.dual.y * r.w + x.dual.z * r.x));

		vec<4, ComponentType, Q> const c(
			xz - wy,
			yz + wx,
			rr.w + rr.z - rr.x - rr.y,
			-(x.dual.w * r.z + x.dual.x * r.y - x.dual.y * r.x - x.dual.z * r.w));

		return mat<3, 4, ComponentType, Q>(a, b, c);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> dualquat_cast(mat<2, 4, ComponentType, Q> const& x)
	{
		return tdualquat<ComponentType, Q>(
			qua<ComponentType, Q>( x[0].w, x[0].x, x[0].y, x[0].z ),
			qua<ComponentType, Q>( x[1].w, x[1].x, x[1].y, x[1].z ));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER tdualquat<ComponentType, Q> dualquat_cast(mat<3, 4, ComponentType, Q> const& x)
	{
		qua<ComponentType, Q> real;

		ComponentType const trace = x[0].x + x[1].y + x[2].z;
		if(trace > static_cast<ComponentType>(0))
		{
			ComponentType const r = sqrt(ComponentType(1) + trace);
			ComponentType const invr = static_cast<ComponentType>(0.5) / r;
			real.w = static_cast<ComponentType>(0.5) * r;
			real.x = (x[2].y - x[1].z) * invr;
			real.y = (x[0].z - x[2].x) * invr;
			real.z = (x[1].x - x[0].y) * invr;
		}
		else if(x[0].x > x[1].y && x[0].x > x[2].z)
		{
			ComponentType const r = sqrt(ComponentType(1) + x[0].x - x[1].y - x[2].z);
			ComponentType const invr = static_cast<ComponentType>(0.5) / r;
			real.x = static_cast<ComponentType>(0.5)*r;
			real.y = (x[1].x + x[0].y) * invr;
			real.z = (x[0].z + x[2].x) * invr;
			real.w = (x[2].y - x[1].z) * invr;
		}
		else if(x[1].y > x[2].z)
		{
			ComponentType const r = sqrt(ComponentType(1) + x[1].y - x[0].x - x[2].z);
			ComponentType const invr = static_cast<ComponentType>(0.5) / r;
			real.x = (x[1].x + x[0].y) * invr;
			real.y = static_cast<ComponentType>(0.5) * r;
			real.z = (x[2].y + x[1].z) * invr;
			real.w = (x[0].z - x[2].x) * invr;
		}
		else
		{
			ComponentType const r = sqrt(ComponentType(1) + x[2].z - x[0].x - x[1].y);
			ComponentType const invr = static_cast<ComponentType>(0.5) / r;
			real.x = (x[0].z + x[2].x) * invr;
			real.y = (x[2].y + x[1].z) * invr;
			real.z = static_cast<ComponentType>(0.5) * r;
			real.w = (x[1].x - x[0].y) * invr;
		}

		qua<ComponentType, Q> dual;
		dual.x =  static_cast<ComponentType>(0.5) * ( x[0].w * real.w + x[1].w * real.z - x[2].w * real.y);
		dual.y =  static_cast<ComponentType>(0.5) * (-x[0].w * real.z + x[1].w * real.w + x[2].w * real.x);
		dual.z =  static_cast<ComponentType>(0.5) * ( x[0].w * real.y - x[1].w * real.x + x[2].w * real.w);
		dual.w = -static_cast<ComponentType>(0.5) * ( x[0].w * real.x + x[1].w * real.y + x[2].w * real.z);
		return tdualquat<ComponentType, Q>(real, dual);
	}
}//namespace glm
