/// @ref gtx_color_space_YCoCg

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rgb2YCoCg
	(
		vec<3, ComponentType, Q> const& rgbColor
	)
	{
		vec<3, ComponentType, Q> result;
		result.x/*Y */ =   rgbColor.r / ComponentType(4) + rgbColor.g / ComponentType(2) + rgbColor.b / ComponentType(4);
		result.y/*Co*/ =   rgbColor.r / ComponentType(2) + rgbColor.g * ComponentType(0) - rgbColor.b / ComponentType(2);
		result.z/*Cg*/ = - rgbColor.r / ComponentType(4) + rgbColor.g / ComponentType(2) - rgbColor.b / ComponentType(4);
		return result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> YCoCg2rgb
	(
		vec<3, ComponentType, Q> const& YCoCgColor
	)
	{
		vec<3, ComponentType, Q> result;
		result.r = YCoCgColor.x + YCoCgColor.y - YCoCgColor.z;
		result.g = YCoCgColor.x				   + YCoCgColor.z;
		result.b = YCoCgColor.x - YCoCgColor.y - YCoCgColor.z;
		return result;
	}

	template<typename ComponentType, qualifier Q, bool isInteger>
	class compute_YCoCgR {
	public:
		static GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rgb2YCoCgR
		(
			vec<3, ComponentType, Q> const& rgbColor
		)
		{
			vec<3, ComponentType, Q> result;
			result.x/*Y */ = rgbColor.g * static_cast<ComponentType>(0.5) + (rgbColor.r + rgbColor.b) * static_cast<ComponentType>(0.25);
			result.y/*Co*/ = rgbColor.r - rgbColor.b;
			result.z/*Cg*/ = rgbColor.g - (rgbColor.r + rgbColor.b) * static_cast<ComponentType>(0.5);
			return result;
		}

		static GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> YCoCgR2rgb
		(
			vec<3, ComponentType, Q> const& YCoCgRColor
		)
		{
			vec<3, ComponentType, Q> result;
			ComponentType tmp = YCoCgRColor.x - (YCoCgRColor.z * static_cast<ComponentType>(0.5));
			result.g = YCoCgRColor.z + tmp;
			result.b = tmp - (YCoCgRColor.y * static_cast<ComponentType>(0.5));
			result.r = result.b + YCoCgRColor.y;
			return result;
		}
	};

	template<typename ComponentType, qualifier Q>
	class compute_YCoCgR<ComponentType, Q, true> {
	public:
		static GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rgb2YCoCgR
		(
			vec<3, ComponentType, Q> const& rgbColor
		)
		{
			vec<3, ComponentType, Q> result;
			result.y/*Co*/ = rgbColor.r - rgbColor.b;
			ComponentType tmp = rgbColor.b + (result.y >> 1);
			result.z/*Cg*/ = rgbColor.g - tmp;
			result.x/*Y */ = tmp + (result.z >> 1);
			return result;
		}

		static GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> YCoCgR2rgb
		(
			vec<3, ComponentType, Q> const& YCoCgRColor
		)
		{
			vec<3, ComponentType, Q> result;
			ComponentType tmp = YCoCgRColor.x - (YCoCgRColor.z >> 1);
			result.g = YCoCgRColor.z + tmp;
			result.b = tmp - (YCoCgRColor.y >> 1);
			result.r = result.b + YCoCgRColor.y;
			return result;
		}
	};

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rgb2YCoCgR
	(
		vec<3, ComponentType, Q> const& rgbColor
	)
	{
		return compute_YCoCgR<ComponentType, Q, std::numeric_limits<ComponentType>::is_integer>::rgb2YCoCgR(rgbColor);
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> YCoCgR2rgb
	(
		vec<3, ComponentType, Q> const& YCoCgRColor
	)
	{
		return compute_YCoCgR<ComponentType, Q, std::numeric_limits<ComponentType>::is_integer>::YCoCgR2rgb(YCoCgRColor);
	}
}//namespace glm
