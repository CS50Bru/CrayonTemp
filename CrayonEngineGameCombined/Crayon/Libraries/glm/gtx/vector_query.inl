/// @ref gtx_vector_query

#include <cassert>

namespace glm{
namespace detail
{
	template<length_t L, typename ComponentType, qualifier Q>
	struct compute_areCollinear{};

	template<typename ComponentType, qualifier Q>
	struct compute_areCollinear<2, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static bool call(vec<2, ComponentType, Q> const& v0, vec<2, ComponentType, Q> const& v1, ComponentType const& epsilon)
		{
			return length(cross(vec<3, ComponentType, Q>(v0, static_cast<ComponentType>(0)), vec<3, ComponentType, Q>(v1, static_cast<ComponentType>(0)))) < epsilon;
		}
	};

	template<typename ComponentType, qualifier Q>
	struct compute_areCollinear<3, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static bool call(vec<3, ComponentType, Q> const& v0, vec<3, ComponentType, Q> const& v1, ComponentType const& epsilon)
		{
			return length(cross(v0, v1)) < epsilon;
		}
	};

	template<typename ComponentType, qualifier Q>
	struct compute_areCollinear<4, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static bool call(vec<4, ComponentType, Q> const& v0, vec<4, ComponentType, Q> const& v1, ComponentType const& epsilon)
		{
			return length(cross(vec<3, ComponentType, Q>(v0), vec<3, ComponentType, Q>(v1))) < epsilon;
		}
	};

	template<length_t L, typename ComponentType, qualifier Q>
	struct compute_isCompNull{};

	template<typename ComponentType, qualifier Q>
	struct compute_isCompNull<2, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<2, bool, Q> call(vec<2, ComponentType, Q> const& v, ComponentType const& epsilon)
		{
			return vec<2, bool, Q>(
				(abs(v.x) < epsilon),
				(abs(v.y) < epsilon));
		}
	};

	template<typename ComponentType, qualifier Q>
	struct compute_isCompNull<3, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<3, bool, Q> call(vec<3, ComponentType, Q> const& v, ComponentType const& epsilon)
		{
			return vec<3, bool, Q>(
				(abs(v.x) < epsilon),
				(abs(v.y) < epsilon),
				(abs(v.z) < epsilon));
		}
	};

	template<typename ComponentType, qualifier Q>
	struct compute_isCompNull<4, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, bool, Q> call(vec<4, ComponentType, Q> const& v, ComponentType const& epsilon)
		{
			return vec<4, bool, Q>(
				(abs(v.x) < epsilon),
				(abs(v.y) < epsilon),
				(abs(v.z) < epsilon),
				(abs(v.w) < epsilon));
		}
	};

}//namespace detail

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER bool areCollinear(vec<L, ComponentType, Q> const& v0, vec<L, ComponentType, Q> const& v1, ComponentType const& epsilon)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'areCollinear' only accept floating-point inputs");

		return detail::compute_areCollinear<L, ComponentType, Q>::call(v0, v1, epsilon);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER bool areOrthogonal(vec<L, ComponentType, Q> const& v0, vec<L, ComponentType, Q> const& v1, ComponentType const& epsilon)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'areOrthogonal' only accept floating-point inputs");

		return abs(dot(v0, v1)) <= max(
			static_cast<ComponentType>(1),
			length(v0)) * max(static_cast<ComponentType>(1), length(v1)) * epsilon;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER bool isNormalized(vec<L, ComponentType, Q> const& v, ComponentType const& epsilon)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'isNormalized' only accept floating-point inputs");

		return abs(length(v) - static_cast<ComponentType>(1)) <= static_cast<ComponentType>(2) * epsilon;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER bool isNull(vec<L, ComponentType, Q> const& v, ComponentType const& epsilon)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'isNull' only accept floating-point inputs");

		return length(v) <= epsilon;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> isCompNull(vec<L, ComponentType, Q> const& v, ComponentType const& epsilon)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'isCompNull' only accept floating-point inputs");

		return detail::compute_isCompNull<L, ComponentType, Q>::call(v, epsilon);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<2, bool, Q> isCompNull(vec<2, ComponentType, Q> const& v, ComponentType const& epsilon)
	{
		return vec<2, bool, Q>(
			abs(v.x) < epsilon,
			abs(v.y) < epsilon);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, bool, Q> isCompNull(vec<3, ComponentType, Q> const& v, ComponentType const& epsilon)
	{
		return vec<3, bool, Q>(
			abs(v.x) < epsilon,
			abs(v.y) < epsilon,
			abs(v.z) < epsilon);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> isCompNull(vec<4, ComponentType, Q> const& v, ComponentType const& epsilon)
	{
		return vec<4, bool, Q>(
			abs(v.x) < epsilon,
			abs(v.y) < epsilon,
			abs(v.z) < epsilon,
			abs(v.w) < epsilon);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER bool areOrthonormal(vec<L, ComponentType, Q> const& v0, vec<L, ComponentType, Q> const& v1, ComponentType const& epsilon)
	{
		return isNormalized(v0, epsilon) && isNormalized(v1, epsilon) && (abs(dot(v0, v1)) <= epsilon);
	}

}//namespace glm
