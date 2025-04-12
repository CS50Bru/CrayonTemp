/// @ref gtx_type_trait

namespace glm
{
	template<typename ComponentType>
	bool const type<ComponentType>::is_vec;
	template<typename ComponentType>
	bool const type<ComponentType>::is_mat;
	template<typename ComponentType>
	bool const type<ComponentType>::is_quat;
	template<typename ComponentType>
	length_t const type<ComponentType>::components;
	template<typename ComponentType>
	length_t const type<ComponentType>::cols;
	template<typename ComponentType>
	length_t const type<ComponentType>::rows;

	// vec
	template<length_t L, typename ComponentType, qualifier Q>
	bool const type<vec<L, ComponentType, Q> >::is_vec;
	template<length_t L, typename ComponentType, qualifier Q>
	bool const type<vec<L, ComponentType, Q> >::is_mat;
	template<length_t L, typename ComponentType, qualifier Q>
	bool const type<vec<L, ComponentType, Q> >::is_quat;
	template<length_t L, typename ComponentType, qualifier Q>
	length_t const type<vec<L, ComponentType, Q> >::components;

	// mat
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	bool const type<mat<C, R, ComponentType, Q> >::is_vec;
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	bool const type<mat<C, R, ComponentType, Q> >::is_mat;
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	bool const type<mat<C, R, ComponentType, Q> >::is_quat;
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	length_t const type<mat<C, R, ComponentType, Q> >::components;
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	length_t const type<mat<C, R, ComponentType, Q> >::cols;
	template<length_t C, length_t R, typename ComponentType, qualifier Q>
	length_t const type<mat<C, R, ComponentType, Q> >::rows;

	// tquat
	template<typename ComponentType, qualifier Q>
	bool const type<qua<ComponentType, Q> >::is_vec;
	template<typename ComponentType, qualifier Q>
	bool const type<qua<ComponentType, Q> >::is_mat;
	template<typename ComponentType, qualifier Q>
	bool const type<qua<ComponentType, Q> >::is_quat;
	template<typename ComponentType, qualifier Q>
	length_t const type<qua<ComponentType, Q> >::components;

	// tdualquat
	template<typename ComponentType, qualifier Q>
	bool const type<tdualquat<ComponentType, Q> >::is_vec;
	template<typename ComponentType, qualifier Q>
	bool const type<tdualquat<ComponentType, Q> >::is_mat;
	template<typename ComponentType, qualifier Q>
	bool const type<tdualquat<ComponentType, Q> >::is_quat;
	template<typename ComponentType, qualifier Q>
	length_t const type<tdualquat<ComponentType, Q> >::components;
}//namespace glm
