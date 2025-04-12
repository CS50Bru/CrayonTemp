#include "scalar_integer.hpp"

namespace glm
{
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> isPowerOfTwo(vec<L, ComponentType, Q> const& Value)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_integer, "'isPowerOfTwo' only accept integer inputs");

		vec<L, ComponentType, Q> const Result(abs(Value));
		return equal(Result & (Result - vec<L, ComponentType, Q>(1)), vec<L, ComponentType, Q>(0));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> nextPowerOfTwo(vec<L, ComponentType, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_integer, "'nextPowerOfTwo' only accept integer inputs");

		return detail::compute_ceilPowerOfTwo<L, ComponentType, Q, std::numeric_limits<ComponentType>::is_signed>::call(v);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> prevPowerOfTwo(vec<L, ComponentType, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_integer, "'prevPowerOfTwo' only accept integer inputs");

		return detail::functor1<vec, L, ComponentType, ComponentType, Q>::call(prevPowerOfTwo, v);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> isMultiple(vec<L, ComponentType, Q> const& Value, ComponentType Multiple)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_integer, "'isMultiple' only accept integer inputs");

		return (Value % Multiple) == vec<L, ComponentType, Q>(0);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> isMultiple(vec<L, ComponentType, Q> const& Value, vec<L, ComponentType, Q> const& Multiple)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_integer, "'isMultiple' only accept integer inputs");

		return (Value % Multiple) == vec<L, ComponentType, Q>(0);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> nextMultiple(vec<L, ComponentType, Q> const& Source, ComponentType Multiple)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_integer, "'nextMultiple' only accept integer inputs");

		return detail::functor2<vec, L, ComponentType, Q>::call(nextMultiple, Source, vec<L, ComponentType, Q>(Multiple));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> nextMultiple(vec<L, ComponentType, Q> const& Source, vec<L, ComponentType, Q> const& Multiple)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_integer, "'nextMultiple' only accept integer inputs");

		return detail::functor2<vec, L, ComponentType, Q>::call(nextMultiple, Source, Multiple);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> prevMultiple(vec<L, ComponentType, Q> const& Source, ComponentType Multiple)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_integer, "'prevMultiple' only accept integer inputs");

		return detail::functor2<vec, L, ComponentType, Q>::call(prevMultiple, Source, vec<L, ComponentType, Q>(Multiple));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> prevMultiple(vec<L, ComponentType, Q> const& Source, vec<L, ComponentType, Q> const& Multiple)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_integer, "'prevMultiple' only accept integer inputs");

		return detail::functor2<vec, L, ComponentType, Q>::call(prevMultiple, Source, Multiple);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, int, Q> findNSB(vec<L, ComponentType, Q> const& Source, vec<L, int, Q> SignificantBitCount)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_integer, "'findNSB' only accept integer inputs");

		return detail::functor2_vec_int<L, ComponentType, Q>::call(findNSB, Source, SignificantBitCount);
	}
}//namespace glm
