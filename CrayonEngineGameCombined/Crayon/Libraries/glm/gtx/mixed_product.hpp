/// @ref gtx_mixed_product
/// @file glm/gtx/mixed_product.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_mixed_product GLM_GTX_mixed_producte
/// @ingroup gtx
///
/// Include <glm/gtx/mixed_product.hpp> to use the features of this extension.
///
/// Mixed product of 3 vectors.

#pragma once

// Dependency:
#include "../glm.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	ifndef GLM_ENABLE_EXPERIMENTAL
#		pragma message("GLM: GLM_GTX_mixed_product is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it.")
#	else
#		pragma message("GLM: GLM_GTX_mixed_product extension included")
#	endif
#endif

namespace glm
{
	/// @addtogroup gtx_mixed_product
	/// @{

	/// @brief Mixed product of 3 vectors (from GLM_GTX_mixed_product extension)
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_DECL ComponentType mixedProduct(
		vec<3, ComponentType, Q> const& v1,
		vec<3, ComponentType, Q> const& v2,
		vec<3, ComponentType, Q> const& v3);

	/// @}
}// namespace glm

#include "mixed_product.inl"
