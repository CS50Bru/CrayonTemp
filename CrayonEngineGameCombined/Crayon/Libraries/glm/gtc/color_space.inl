/// @ref gtc_color_space

namespace glm{
namespace detail
{
	template<length_t L, typename ComponentType, qualifier Q>
	struct compute_rgbToSrgb
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, ComponentType, Q> const& ColorRGB, ComponentType GammaCorrection)
		{
			vec<L, ComponentType, Q> const ClampedColor(clamp(ColorRGB, static_cast<ComponentType>(0), static_cast<ComponentType>(1)));

			return mix(
				pow(ClampedColor, vec<L, ComponentType, Q>(GammaCorrection)) * static_cast<ComponentType>(1.055) - static_cast<ComponentType>(0.055),
				ClampedColor * static_cast<ComponentType>(12.92),
				lessThan(ClampedColor, vec<L, ComponentType, Q>(static_cast<ComponentType>(0.0031308))));
		}
	};

	template<typename ComponentType, qualifier Q>
	struct compute_rgbToSrgb<4, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, ComponentType, Q> call(vec<4, ComponentType, Q> const& ColorRGB, ComponentType GammaCorrection)
		{
			return vec<4, ComponentType, Q>(compute_rgbToSrgb<3, ComponentType, Q>::call(vec<3, ComponentType, Q>(ColorRGB), GammaCorrection), ColorRGB.w);
		}
	};

	template<length_t L, typename ComponentType, qualifier Q>
	struct compute_srgbToRgb
	{
		GLM_FUNC_QUALIFIER static vec<L, ComponentType, Q> call(vec<L, ComponentType, Q> const& ColorSRGB, ComponentType Gamma)
		{
			return mix(
				pow((ColorSRGB + static_cast<ComponentType>(0.055)) * static_cast<ComponentType>(0.94786729857819905213270142180095), vec<L, ComponentType, Q>(Gamma)),
				ColorSRGB * static_cast<ComponentType>(0.07739938080495356037151702786378),
				lessThanEqual(ColorSRGB, vec<L, ComponentType, Q>(static_cast<ComponentType>(0.04045))));
		}
	};

	template<typename ComponentType, qualifier Q>
	struct compute_srgbToRgb<4, ComponentType, Q>
	{
		GLM_FUNC_QUALIFIER static vec<4, ComponentType, Q> call(vec<4, ComponentType, Q> const& ColorSRGB, ComponentType Gamma)
		{
			return vec<4, ComponentType, Q>(compute_srgbToRgb<3, ComponentType, Q>::call(vec<3, ComponentType, Q>(ColorSRGB), Gamma), ColorSRGB.w);
		}
	};
}//namespace detail

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> convertLinearToSRGB(vec<L, ComponentType, Q> const& ColorLinear)
	{
		return detail::compute_rgbToSrgb<L, ComponentType, Q>::call(ColorLinear, static_cast<ComponentType>(0.41666));
	}

	// Based on Ian Taylor http://chilliant.blogspot.fr/2012/08/srgb-approximations-for-hlsl.html
	template<>
	GLM_FUNC_QUALIFIER vec<3, float, lowp> convertLinearToSRGB(vec<3, float, lowp> const& ColorLinear)
	{
		vec<3, float, lowp> S1 = sqrt(ColorLinear);
		vec<3, float, lowp> S2 = sqrt(S1);
		vec<3, float, lowp> S3 = sqrt(S2);
		return 0.662002687f * S1 + 0.684122060f * S2 - 0.323583601f * S3 - 0.0225411470f * ColorLinear;
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> convertLinearToSRGB(vec<L, ComponentType, Q> const& ColorLinear, ComponentType Gamma)
	{
		return detail::compute_rgbToSrgb<L, ComponentType, Q>::call(ColorLinear, static_cast<ComponentType>(1) / Gamma);
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> convertSRGBToLinear(vec<L, ComponentType, Q> const& ColorSRGB)
	{
		return detail::compute_srgbToRgb<L, ComponentType, Q>::call(ColorSRGB, static_cast<ComponentType>(2.4));
	}

	template<length_t L, typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, ComponentType, Q> convertSRGBToLinear(vec<L, ComponentType, Q> const& ColorSRGB, ComponentType Gamma)
	{
		return detail::compute_srgbToRgb<L, ComponentType, Q>::call(ColorSRGB, Gamma);
	}
}//namespace glm
