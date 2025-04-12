#include "../exponential.hpp"
#include "../common.hpp"

namespace glm{
namespace detail
{
	template<length_t L, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_length
	{
		GLM_FUNC_QUALIFIER static ComponentType call(vec<L, ComponentType, Q> const& v)
		{
			return sqrt(dot(v, v));
		}
	};

	template<length_t L, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_distance
	{
		GLM_FUNC_QUALIFIER static ComponentType call(vec<L, ComponentType, Q> const& p0, vec<L, ComponentType, Q> const& p1)
		{
			return length(p1 - p0);
		}
	};

	template<typename V, typename ComponentType, bool Aligned>
	struct compute_dot{};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_dot<vec<1, ComponentType, Q>, ComponentType, Aligned>
	{
		GLM_FUNC_QUALIFIER static ComponentType call(vec<1, ComponentType, Q> const& a, vec<1, ComponentType, Q> const& b)
		{
			return a.x * b.x;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_dot<vec<2, ComponentType, Q>, ComponentType, Aligned>
	{
		GLM_FUNC_QUALIFIER static ComponentType call(vec<2, ComponentType, Q> const& a, vec<2, ComponentType, Q> const& b)
		{
			vec<2, ComponentType, Q> tmp(a * b);
			return tmp.x + tmp.y;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_dot<vec<3, ComponentType, Q>, ComponentType, Aligned>
	{
		GLM_FUNC_QUALIFIER static ComponentType call(vec<3, ComponentType, Q> const& a, vec<3, ComponentType, Q> const& b)
		{
			vec<3, ComponentType, Q> tmp(a * b);
			return tmp.x + tmp.y + tmp.z;
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_dot<vec<4, ComponentType, Q>, ComponentType, Aligned>
	{
		GLM_FUNC_QUALIFIER static ComponentType call(vec<4, ComponentType, Q> const& a, vec<4, ComponentType, Q> const& b)
		{
			vec<4, ComponentType, Q> tmp(a * b);
			return (tmp.x + tmp.y) + (tmp.z + tmp.w);
		}
	};

	template<typename ComponentType, qualifier Q, bool Aligned>
	struct compute_cross
	{
		GLM_FUNC_QUALIFIER static vec<3, ComponentType, Q> call(vec<3, ComponentType, Q> const& x, vec<3, ComponentType, Q> const& y)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'cross' accepts only floating-point inputs");

			return vec<3, ComponentType, Q>(
				x.y * y.z - y.y * x.z,
				x.z * y.x - y.z * x.x,
				x.x * y.y - y.x * x.y);
		}
	};

	template<length_t L, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_normalize
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, ComponentType, Q> const& v)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'normalize' accepts only floating-point inputs");

			return v * inversesqrt(dot(v, v));
		}
	};

	template<length_t L, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_faceforward
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, ComponentType, Q> const& N, vec<L, ComponentType, Q> const& I, vec<L, ComponentType, Q> const& Nref)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'normalize' accepts only floating-point inputs");

			return dot(Nref, I) < static_cast<ComponentType>(0) ? N : -N;
		}
	};

	template<length_t L, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_reflect
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, ComponentType, Q> const& I, vec<L, ComponentType, Q> const& N)
		{
			return I - N * dot(N, I) * static_cast<ComponentType>(2);
		}
	};

	template<length_t L, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_refract
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, ComponentType, Q> const& I, vec<L, ComponentType, Q> const& N, ComponentType eta)
		{
			ComponentType const dotValue(dot(N, I));
			ComponentType const k(static_cast<ComponentType>(1) - eta * eta * (static_cast<ComponentType>(1) - dotValue * dotValue));
			vec<L, ComponentType, Q> const Result =
                (k >= static_cast<ComponentType>(0)) ? (eta * I - (eta * dotValue + std::sqrt(k)) * N) : vec<L, ComponentType, Q>(0);
			return Result;
		}
	};
}//namespace detail

	// length
	template<typename genType>
	GLM_FUNC_QUALIFIER genType length(genType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'length' accepts only floating-point inputs");

		return abs(x);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType length(vec<L, ComponentType, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'length' accepts only floating-point inputs");

		return detail::compute_length<L, ComponentType, Q, detail::is_aligned<Q>::value>::call(v);
	}

	// distance
	template<typename genType>
	GLM_FUNC_QUALIFIER genType distance(genType const& p0, genType const& p1)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'distance' accepts only floating-point inputs");

		return length(p1 - p0);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType distance(vec<L, ComponentType, Q> const& p0, vec<L, ComponentType, Q> const& p1)
	{
		return detail::compute_distance<L, ComponentType, Q, detail::is_aligned<Q>::value>::call(p0, p1);
	}

	// dot
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER ComponentType dot(ComponentType x, ComponentType y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'dot' accepts only floating-point inputs");
		return x * y;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType dot(vec<L, ComponentType, Q> const& x, vec<L, ComponentType, Q> const& y)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'dot' accepts only floating-point inputs");
		return detail::compute_dot<vec<L, ComponentType, Q>, ComponentType, detail::is_aligned<Q>::value>::call(x, y);
	}

	// cross
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> cross(vec<3, ComponentType, Q> const& x, vec<3, ComponentType, Q> const& y)
	{
		return detail::compute_cross<ComponentType, Q, detail::is_aligned<Q>::value>::call(x, y);
	}
/*
	// normalize
	template<typename genType>
	GLM_FUNC_QUALIFIER genType normalize(genType const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'normalize' accepts only floating-point inputs");

		return x < genType(0) ? genType(-1) : genType(1);
	}
*/
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> normalize(vec<L, ComponentType, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'normalize' accepts only floating-point inputs");

		return detail::compute_normalize<L, ComponentType, Q, detail::is_aligned<Q>::value>::call(x);
	}

	// faceforward
	template<typename genType>
	GLM_FUNC_QUALIFIER genType faceforward(genType const& N, genType const& I, genType const& Nref)
	{
		return dot(Nref, I) < static_cast<genType>(0) ? N : -N;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> faceforward(vec<L, ComponentType, Q> const& N, vec<L, ComponentType, Q> const& I, vec<L, ComponentType, Q> const& Nref)
	{
		return detail::compute_faceforward<L, ComponentType, Q, detail::is_aligned<Q>::value>::call(N, I, Nref);
	}

	// reflect
	template<typename genType>
	GLM_FUNC_QUALIFIER genType reflect(genType const& I, genType const& N)
	{
		return I - N * dot(N, I) * genType(2);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> reflect(vec<L, ComponentType, Q> const& I, vec<L, ComponentType, Q> const& N)
	{
		return detail::compute_reflect<L, ComponentType, Q, detail::is_aligned<Q>::value>::call(I, N);
	}

	// refract
	template<typename genType>
	GLM_FUNC_QUALIFIER genType refract(genType const& I, genType const& N, genType eta)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'refract' accepts only floating-point inputs");
		genType const dotValue(dot(N, I));
		genType const k(static_cast<genType>(1) - eta * eta * (static_cast<genType>(1) - dotValue * dotValue));
		return (eta * I - (eta * dotValue + sqrt(k)) * N) * static_cast<genType>(k >= static_cast<genType>(0));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> refract(vec<L, ComponentType, Q> const& I, vec<L, ComponentType, Q> const& N, ComponentType eta)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'refract' accepts only floating-point inputs");
		return detail::compute_refract<L, ComponentType, Q, detail::is_aligned<Q>::value>::call(I, N, eta);
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "func_geometric_simd.inl"
#endif
