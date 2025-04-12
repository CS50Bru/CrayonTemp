/// @ref ext_scalar_common
/// @file glm/ext/scalar_common.hpp
///
/// @defgroup ext_scalar_common GLM_EXT_scalar_common
/// @ingroup ext
///
/// Exposes min and max functions for 3 to 4 scalar parameters.
///
/// Include <glm/ext/scalar_common.hpp> to use the features of this extension.
///
/// @see core_func_common
/// @see ext_vector_common

#pragma once

// Dependency:
#include "../common.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_scalar_common extension included")
#endif

namespace glm
{
	/// @addtogroup ext_scalar_common
	/// @{

	/// Returns the minimum component-wise values of 3 inputs
	///
	/// @tparam ComponentType A floating-point scalar type.
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType min(ComponentType a, ComponentType b, ComponentType c);

	/// Returns the minimum component-wise values of 4 inputs
	///
	/// @tparam ComponentType A floating-point scalar type.
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType min(ComponentType a, ComponentType b, ComponentType c, ComponentType d);

	/// Returns the maximum component-wise values of 3 inputs
	///
	/// @tparam ComponentType A floating-point scalar type.
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType max(ComponentType a, ComponentType b, ComponentType c);

	/// Returns the maximum component-wise values of 4 inputs
	///
	/// @tparam ComponentType A floating-point scalar type.
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType max(ComponentType a, ComponentType b, ComponentType c, ComponentType d);

	/// Returns the minimum component-wise values of 2 inputs. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam ComponentType A floating-point scalar type.
	///
	/// @see <a href="http://en.cppreference.com/w/cpp/numeric/math/fmin">std::fmin documentation</a>
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType fmin(ComponentType a, ComponentType b);

	/// Returns the minimum component-wise values of 3 inputs. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam ComponentType A floating-point scalar type.
	///
	/// @see <a href="http://en.cppreference.com/w/cpp/numeric/math/fmin">std::fmin documentation</a>
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType fmin(ComponentType a, ComponentType b, ComponentType c);

	/// Returns the minimum component-wise values of 4 inputs. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam ComponentType A floating-point scalar type.
	///
	/// @see <a href="http://en.cppreference.com/w/cpp/numeric/math/fmin">std::fmin documentation</a>
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType fmin(ComponentType a, ComponentType b, ComponentType c, ComponentType d);

	/// Returns the maximum component-wise values of 2 inputs. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam ComponentType A floating-point scalar type.
	///
	/// @see <a href="http://en.cppreference.com/w/cpp/numeric/math/fmax">std::fmax documentation</a>
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType fmax(ComponentType a, ComponentType b);

	/// Returns the maximum component-wise values of 3 inputs. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam ComponentType A floating-point scalar type.
	///
	/// @see <a href="http://en.cppreference.com/w/cpp/numeric/math/fmax">std::fmax documentation</a>
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType fmax(ComponentType a, ComponentType b, ComponentType C);

	/// Returns the maximum component-wise values of 4 inputs. If one of the two arguments is NaN, the value of the other argument is returned.
	///
	/// @tparam ComponentType A floating-point scalar type.
	///
	/// @see <a href="http://en.cppreference.com/w/cpp/numeric/math/fmax">std::fmax documentation</a>
	template<typename ComponentType>
	GLM_FUNC_DECL ComponentType fmax(ComponentType a, ComponentType b, ComponentType C, ComponentType D);

	/// @}
}//namespace glm

#include "scalar_common.inl"
