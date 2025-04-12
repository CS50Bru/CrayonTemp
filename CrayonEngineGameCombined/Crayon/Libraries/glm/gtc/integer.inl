/// @ref gtc_integer

namespace glm{
namespace detail
{
	template<length_t L, typename ComponentType, qualifier Q, bool Aligned>
	struct compute_log2<L, ComponentType, Q, false, Aligned>
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, ComponentType, Q> const& v)
		{
			//Equivalent to return findMSB(vec); but save one function call in ASM with VC
			//return findMSB(vec);
			return vec<L, ComponentType, Q>(detail::compute_findMSB_vec<L, ComponentType, Q, sizeof(ComponentType) * 8>::call(v));
		}
	};

#	if GLM_HAS_BITSCAN_WINDOWS
		template<qualifier Q, bool Aligned>
		struct compute_log2<4, int, Q, false, Aligned>
		{
			GLM_FUNC_QUALIFIER static vec<4, int, Q> call(vec<4, int, Q> const& v)
			{
				vec<4, int, Q> Result;
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result.x), v.x);
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result.y), v.y);
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result.z), v.z);
				_BitScanReverse(reinterpret_cast<unsigned long*>(&Result.w), v.w);
				return Result;
			}
		};
#	endif//GLM_HAS_BITSCAN_WINDOWS
}//namespace detail
	template<typename genType>
	GLM_FUNC_QUALIFIER int iround(genType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'iround' only accept floating-point inputs");
		assert(static_cast<genType>(0.0) <= x);

		return static_cast<int>(x + static_cast<genType>(0.5));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, int, Q> iround(vec<L, ComponentType, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'iround' only accept floating-point inputs");
		assert(all(lessThanEqual(vec<L, ComponentType, Q>(0), x)));

		return vec<L, int, Q>(x + static_cast<ComponentType>(0.5));
	}

	template<typename genType>
	GLM_FUNC_QUALIFIER uint uround(genType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'uround' only accept floating-point inputs");
		assert(static_cast<genType>(0.0) <= x);

		return static_cast<uint>(x + static_cast<genType>(0.5));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, uint, Q> uround(vec<L, ComponentType, Q> const& x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<ComponentType>::is_iec559, "'uround' only accept floating-point inputs");
		assert(all(lessThanEqual(vec<L, ComponentType, Q>(0), x)));

		return vec<L, uint, Q>(x + static_cast<ComponentType>(0.5));
	}
}//namespace glm
