/// @ref gtc_type_ptr

#include <cstring>

namespace glm
{
	/// @addtogroup gtc_type_ptr
	/// @{

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(vec<2, ComponentType, Q> const& v)
	{
		return &(v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(vec<2, ComponentType, Q>& v)
	{
		return &(v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const * value_ptr(vec<3, ComponentType, Q> const& v)
	{
		return &(v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(vec<3, ComponentType, Q>& v)
	{
		return &(v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(vec<4, ComponentType, Q> const& v)
	{
		return &(v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(vec<4, ComponentType, Q>& v)
	{
		return &(v.x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(mat<2, 2, ComponentType, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(mat<2, 2, ComponentType, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(mat<3, 3, ComponentType, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(mat<3, 3, ComponentType, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(mat<4, 4, ComponentType, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(mat<4, 4, ComponentType, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(mat<2, 3, ComponentType, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(mat<2, 3, ComponentType, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(mat<3, 2, ComponentType, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(mat<3, 2, ComponentType, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(mat<2, 4, ComponentType, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(mat<2, 4, ComponentType, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(mat<4, 2, ComponentType, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(mat<4, 2, ComponentType, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(mat<3, 4, ComponentType, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(mat<3, 4, ComponentType, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const* value_ptr(mat<4, 3, ComponentType, Q> const& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType * value_ptr(mat<4, 3, ComponentType, Q>& m)
	{
		return &(m[0].x);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType const * value_ptr(qua<ComponentType, Q> const& q)
	{
		return &(q[0]);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType* value_ptr(qua<ComponentType, Q>& q)
	{
		return &(q[0]);
	}

	template <typename ComponentType, qualifier Q>
	inline vec<1, ComponentType, Q> make_vec1(vec<1, ComponentType, Q> const& v)
	{
		return v;
	}

	template <typename ComponentType, qualifier Q>
	inline vec<1, ComponentType, Q> make_vec1(vec<2, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(v);
	}

	template <typename ComponentType, qualifier Q>
	inline vec<1, ComponentType, Q> make_vec1(vec<3, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(v);
	}

	template <typename ComponentType, qualifier Q>
	inline vec<1, ComponentType, Q> make_vec1(vec<4, ComponentType, Q> const& v)
	{
		return vec<1, ComponentType, Q>(v);
	}

	template <typename ComponentType, qualifier Q>
	inline vec<2, ComponentType, Q> make_vec2(vec<1, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(v.x, static_cast<ComponentType>(0));
	}

	template <typename ComponentType, qualifier Q>
	inline vec<2, ComponentType, Q> make_vec2(vec<2, ComponentType, Q> const& v)
	{
		return v;
	}

	template <typename ComponentType, qualifier Q>
	inline vec<2, ComponentType, Q> make_vec2(vec<3, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(v);
	}

	template <typename ComponentType, qualifier Q>
	inline vec<2, ComponentType, Q> make_vec2(vec<4, ComponentType, Q> const& v)
	{
		return vec<2, ComponentType, Q>(v);
	}

	template <typename ComponentType, qualifier Q>
	inline vec<3, ComponentType, Q> make_vec3(vec<1, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(v.x, static_cast<ComponentType>(0), static_cast<ComponentType>(0));
	}

	template <typename ComponentType, qualifier Q>
	inline vec<3, ComponentType, Q> make_vec3(vec<2, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(v.x, v.y, static_cast<ComponentType>(0));
	}

	template <typename ComponentType, qualifier Q>
	inline vec<3, ComponentType, Q> make_vec3(vec<3, ComponentType, Q> const& v)
	{
		return v;
	}

	template <typename ComponentType, qualifier Q>
	inline vec<3, ComponentType, Q> make_vec3(vec<4, ComponentType, Q> const& v)
	{
		return vec<3, ComponentType, Q>(v);
	}

	template <typename ComponentType, qualifier Q>
	inline vec<4, ComponentType, Q> make_vec4(vec<1, ComponentType, Q> const& v)
	{
		return vec<4, ComponentType, Q>(v.x, static_cast<ComponentType>(0), static_cast<ComponentType>(0), static_cast<ComponentType>(1));
	}

	template <typename ComponentType, qualifier Q>
	inline vec<4, ComponentType, Q> make_vec4(vec<2, ComponentType, Q> const& v)
	{
		return vec<4, ComponentType, Q>(v.x, v.y, static_cast<ComponentType>(0), static_cast<ComponentType>(1));
	}

	template <typename ComponentType, qualifier Q>
	inline vec<4, ComponentType, Q> make_vec4(vec<3, ComponentType, Q> const& v)
	{
		return vec<4, ComponentType, Q>(v.x, v.y, v.z, static_cast<ComponentType>(1));
	}

	template <typename ComponentType, qualifier Q>
	inline vec<4, ComponentType, Q> make_vec4(vec<4, ComponentType, Q> const& v)
	{
		return v;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER vec<2, ComponentType, defaultp> make_vec2(ComponentType const *const ptr)
	{
		vec<2, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(vec<2, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, defaultp> make_vec3(ComponentType const *const ptr)
	{
		vec<3, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(vec<3, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, defaultp> make_vec4(ComponentType const *const ptr)
	{
		vec<4, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(vec<4, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<2, 2, ComponentType, defaultp> make_mat2x2(ComponentType const *const ptr)
	{
		mat<2, 2, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<2, 2, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<2, 3, ComponentType, defaultp> make_mat2x3(ComponentType const *const ptr)
	{
		mat<2, 3, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<2, 3, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<2, 4, ComponentType, defaultp> make_mat2x4(ComponentType const *const ptr)
	{
		mat<2, 4, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<2, 4, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<3, 2, ComponentType, defaultp> make_mat3x2(ComponentType const *const ptr)
	{
		mat<3, 2, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<3, 2, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, defaultp> make_mat3x3(ComponentType const *const ptr)
	{
		mat<3, 3, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<3, 3, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<3, 4, ComponentType, defaultp> make_mat3x4(ComponentType const *const ptr)
	{
		mat<3, 4, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<3, 4, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 2, ComponentType, defaultp> make_mat4x2(ComponentType const *const ptr)
	{
		mat<4, 2, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<4, 2, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 3, ComponentType, defaultp> make_mat4x3(ComponentType const *const ptr)
	{
		mat<4, 3, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<4, 3, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> make_mat4x4(ComponentType const *const ptr)
	{
		mat<4, 4, ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(mat<4, 4, ComponentType, defaultp>));
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<2, 2, ComponentType, defaultp> make_mat2(ComponentType const *const ptr)
	{
		return make_mat2x2(ptr);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, defaultp> make_mat3(ComponentType const *const ptr)
	{
		return make_mat3x3(ptr);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> make_mat4(ComponentType const *const ptr)
	{
		return make_mat4x4(ptr);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER qua<ComponentType, defaultp> make_quat(ComponentType const *const ptr)
	{
		qua<ComponentType, defaultp> Result;
		memcpy(value_ptr(Result), ptr, sizeof(qua<ComponentType, defaultp>));
		return Result;
	}

	/// @}
}//namespace glm

