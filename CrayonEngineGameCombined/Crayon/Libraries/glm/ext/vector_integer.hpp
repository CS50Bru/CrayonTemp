/// @ref ext_vector_integer
/// @file glm/ext/vector_integer.hpp
///
/// @see core (dependence)
/// @see ext_vector_integer (dependence)
///
/// @defgroup ext_vector_integer GLM_EXT_vector_integer
/// @ingroup ext
///
/// Include <glm/ext/vector_integer.hpp> to use the features of this extension.

#pragma once

// Dependencies
#include "../detail/setup.hpp"
#include "../detail/qualifier.hpp"
#include "../detail/_vectorize.hpp"
#include "../vector_relational.hpp"
#include "../common.hpp"
#include <limits>

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_integer extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_integer
	/// @{

	/// Return true if the value is a power of two number.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Signed or unsigned integer scalar types.
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_vector_integer
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, bool, Q> isPowerOfTwo(vec<L, ComponentType, Q> const& v);

	/// Return the power of two number which value is just higher the input value,
	/// round up to a power of two.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Signed or unsigned integer scalar types.
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_vector_integer
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> nextPowerOfTwo(vec<L, ComponentType, Q> const& v);

	/// Return the power of two number which value is just lower the input value,
	/// round down to a power of two.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Signed or unsigned integer scalar types.
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_vector_integer
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> prevPowerOfTwo(vec<L, ComponentType, Q> const& v);

	/// Return true if the 'Value' is a multiple of 'Multiple'.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Signed or unsigned integer scalar types.
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_vector_integer
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, bool, Q> isMultiple(vec<L, ComponentType, Q> const& v, ComponentType Multiple);

	/// Return true if the 'Value' is a multiple of 'Multiple'.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Signed or unsigned integer scalar types.
	/// @tparam Q Value from qualifier enum
	///
	/// @see ext_vector_integer
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, bool, Q> isMultiple(vec<L, ComponentType, Q> const& v, vec<L, ComponentType, Q> const& Multiple);

	/// Higher multiple number of Source.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Signed or unsigned integer scalar types.
	/// @tparam Q Value from qualifier enum
	///
	/// @param v Source values to which is applied the function
	/// @param Multiple Must be a null or positive value
	///
	/// @see ext_vector_integer
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> nextMultiple(vec<L, ComponentType, Q> const& v, ComponentType Multiple);

	/// Higher multiple number of Source.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Signed or unsigned integer scalar types.
	/// @tparam Q Value from qualifier enum
	///
	/// @param v Source values to which is applied the function
	/// @param Multiple Must be a null or positive value
	///
	/// @see ext_vector_integer
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> nextMultiple(vec<L, ComponentType, Q> const& v, vec<L, ComponentType, Q> const& Multiple);

	/// Lower multiple number of Source.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Signed or unsigned integer scalar types.
	/// @tparam Q Value from qualifier enum
	///
	/// @param v Source values to which is applied the function
	/// @param Multiple Must be a null or positive value
	///
	/// @see ext_vector_integer
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> prevMultiple(vec<L, ComponentType, Q> const& v, ComponentType Multiple);

	/// Lower multiple number of Source.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam ComponentType Signed or unsigned integer scalar types.
	/// @tparam Q Value from qualifier enum
	///
	/// @param v Source values to which is applied the function
	/// @param Multiple Must be a null or positive value
	///
	/// @see ext_vector_integer
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, ComponentType, Q> prevMultiple(vec<L, ComponentType, Q> const& v, vec<L, ComponentType, Q> const& Multiple);

	/// Returns the bit number of the Nth significant bit set to
	/// 1 in the binary representation of value.
	/// If value bitcount is less than the Nth significant bit, -1 will be returned.
	///
	/// @tparam L An integer between 1 and 4 included that qualify the dimension of the vector.
	/// @tparam ComponentType Signed or unsigned integer scalar types.
	///
	/// @see ext_vector_integer
	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_DECL vec<L, int, Q> findNSB(vec<L, ComponentType, Q> const& Source, vec<L, int, Q> SignificantBitCount);

	/// @}
} //namespace glm

#include "vector_integer.inl"
