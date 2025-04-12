/// @ref gtx_hash
///
/// @see core (dependence)
///
/// @defgroup gtx_hash GLM_GTX_hash
/// @ingroup gtx
///
/// @brief Add std::hash support for glm types
///
/// <glm/gtx/hash.inl> need to be included to use the features of this extension.

namespace glm {
namespace detail
{
	GLM_INLINE void hash_combine(size_t &seed, size_t hash)
	{
		hash += 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= hash;
	}
}}

namespace std
{
	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::vec<1, ComponentType, Q>>::operator()(glm::vec<1, ComponentType, Q> const& v) const
	{
		hash<ComponentType> hasher;
		return hasher(v.x);
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::vec<2, ComponentType, Q>>::operator()(glm::vec<2, ComponentType, Q> const& v) const
	{
		size_t seed = 0;
		hash<ComponentType> hasher;
		glm::detail::hash_combine(seed, hasher(v.x));
		glm::detail::hash_combine(seed, hasher(v.y));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::vec<3, ComponentType, Q>>::operator()(glm::vec<3, ComponentType, Q> const& v) const
	{
		size_t seed = 0;
		hash<ComponentType> hasher;
		glm::detail::hash_combine(seed, hasher(v.x));
		glm::detail::hash_combine(seed, hasher(v.y));
		glm::detail::hash_combine(seed, hasher(v.z));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::vec<4, ComponentType, Q>>::operator()(glm::vec<4, ComponentType, Q> const& v) const
	{
		size_t seed = 0;
		hash<ComponentType> hasher;
		glm::detail::hash_combine(seed, hasher(v.x));
		glm::detail::hash_combine(seed, hasher(v.y));
		glm::detail::hash_combine(seed, hasher(v.z));
		glm::detail::hash_combine(seed, hasher(v.w));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::qua<ComponentType, Q>>::operator()(glm::qua<ComponentType,Q> const& q) const
	{
		size_t seed = 0;
		hash<ComponentType> hasher;
		glm::detail::hash_combine(seed, hasher(q.x));
		glm::detail::hash_combine(seed, hasher(q.y));
		glm::detail::hash_combine(seed, hasher(q.z));
		glm::detail::hash_combine(seed, hasher(q.w));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::tdualquat<ComponentType, Q>>::operator()(glm::tdualquat<ComponentType, Q> const& q) const
	{
		size_t seed = 0;
		hash<glm::qua<ComponentType, Q>> hasher;
		glm::detail::hash_combine(seed, hasher(q.real));
		glm::detail::hash_combine(seed, hasher(q.dual));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::mat<2, 2, ComponentType, Q>>::operator()(glm::mat<2, 2, ComponentType, Q> const& m) const
	{
		size_t seed = 0;
		hash<glm::vec<2, ComponentType, Q>> hasher;
		glm::detail::hash_combine(seed, hasher(m[0]));
		glm::detail::hash_combine(seed, hasher(m[1]));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::mat<2, 3, ComponentType, Q>>::operator()(glm::mat<2, 3, ComponentType, Q> const& m) const
	{
		size_t seed = 0;
		hash<glm::vec<3, ComponentType, Q>> hasher;
		glm::detail::hash_combine(seed, hasher(m[0]));
		glm::detail::hash_combine(seed, hasher(m[1]));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::mat<2, 4, ComponentType, Q>>::operator()(glm::mat<2, 4, ComponentType, Q> const& m) const
	{
		size_t seed = 0;
		hash<glm::vec<4, ComponentType, Q>> hasher;
		glm::detail::hash_combine(seed, hasher(m[0]));
		glm::detail::hash_combine(seed, hasher(m[1]));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::mat<3, 2, ComponentType, Q>>::operator()(glm::mat<3, 2, ComponentType, Q> const& m) const
	{
		size_t seed = 0;
		hash<glm::vec<2, ComponentType, Q>> hasher;
		glm::detail::hash_combine(seed, hasher(m[0]));
		glm::detail::hash_combine(seed, hasher(m[1]));
		glm::detail::hash_combine(seed, hasher(m[2]));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::mat<3, 3, ComponentType, Q>>::operator()(glm::mat<3, 3, ComponentType, Q> const& m) const
	{
		size_t seed = 0;
		hash<glm::vec<3, ComponentType, Q>> hasher;
		glm::detail::hash_combine(seed, hasher(m[0]));
		glm::detail::hash_combine(seed, hasher(m[1]));
		glm::detail::hash_combine(seed, hasher(m[2]));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::mat<3, 4, ComponentType, Q>>::operator()(glm::mat<3, 4, ComponentType, Q> const& m) const
	{
		size_t seed = 0;
		hash<glm::vec<4, ComponentType, Q>> hasher;
		glm::detail::hash_combine(seed, hasher(m[0]));
		glm::detail::hash_combine(seed, hasher(m[1]));
		glm::detail::hash_combine(seed, hasher(m[2]));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::mat<4, 2, ComponentType,Q>>::operator()(glm::mat<4, 2, ComponentType,Q> const& m) const
	{
		size_t seed = 0;
		hash<glm::vec<2, ComponentType, Q>> hasher;
		glm::detail::hash_combine(seed, hasher(m[0]));
		glm::detail::hash_combine(seed, hasher(m[1]));
		glm::detail::hash_combine(seed, hasher(m[2]));
		glm::detail::hash_combine(seed, hasher(m[3]));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::mat<4, 3, ComponentType,Q>>::operator()(glm::mat<4, 3, ComponentType,Q> const& m) const
	{
		size_t seed = 0;
		hash<glm::vec<3, ComponentType, Q>> hasher;
		glm::detail::hash_combine(seed, hasher(m[0]));
		glm::detail::hash_combine(seed, hasher(m[1]));
		glm::detail::hash_combine(seed, hasher(m[2]));
		glm::detail::hash_combine(seed, hasher(m[3]));
		return seed;
	}

	template<typename ComponentType, glm::qualifier Q>
	GLM_FUNC_QUALIFIER size_t hash<glm::mat<4, 4, ComponentType,Q>>::operator()(glm::mat<4, 4, ComponentType, Q> const& m) const
	{
		size_t seed = 0;
		hash<glm::vec<4, ComponentType, Q>> hasher;
		glm::detail::hash_combine(seed, hasher(m[0]));
		glm::detail::hash_combine(seed, hasher(m[1]));
		glm::detail::hash_combine(seed, hasher(m[2]));
		glm::detail::hash_combine(seed, hasher(m[3]));
		return seed;
	}
}
