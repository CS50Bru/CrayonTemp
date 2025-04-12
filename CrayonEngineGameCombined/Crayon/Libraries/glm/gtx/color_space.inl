/// @ref gtx_color_space

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> rgbColor(const vec<3, ComponentType, Q>& hsvColor)
	{
		vec<3, ComponentType, Q> hsv = hsvColor;
		vec<3, ComponentType, Q> rgbColor;

		if(hsv.y == static_cast<ComponentType>(0))
			// achromatic (grey)
			rgbColor = vec<3, ComponentType, Q>(hsv.z);
		else
		{
			ComponentType sector = floor(hsv.x * (ComponentType(1) / ComponentType(60)));
			ComponentType frac = (hsv.x * (ComponentType(1) / ComponentType(60))) - sector;
			// factorial part of h
			ComponentType o = hsv.z * (ComponentType(1) - hsv.y);
			ComponentType p = hsv.z * (ComponentType(1) - hsv.y * frac);
			ComponentType q = hsv.z * (ComponentType(1) - hsv.y * (ComponentType(1) - frac));

			switch(int(sector))
			{
			default:
			case 0:
				rgbColor.r = hsv.z;
				rgbColor.g = q;
				rgbColor.b = o;
				break;
			case 1:
				rgbColor.r = p;
				rgbColor.g = hsv.z;
				rgbColor.b = o;
				break;
			case 2:
				rgbColor.r = o;
				rgbColor.g = hsv.z;
				rgbColor.b = q;
				break;
			case 3:
				rgbColor.r = o;
				rgbColor.g = p;
				rgbColor.b = hsv.z;
				break;
			case 4:
				rgbColor.r = q;
				rgbColor.g = o;
				rgbColor.b = hsv.z;
				break;
			case 5:
				rgbColor.r = hsv.z;
				rgbColor.g = o;
				rgbColor.b = p;
				break;
			}
		}

		return rgbColor;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> hsvColor(const vec<3, ComponentType, Q>& rgbColor)
	{
		vec<3, ComponentType, Q> hsv = rgbColor;
		float Min   = min(min(rgbColor.r, rgbColor.g), rgbColor.b);
		float Max   = max(max(rgbColor.r, rgbColor.g), rgbColor.b);
		float Delta = Max - Min;

		hsv.z = Max;

		if(Max != static_cast<ComponentType>(0))
		{
			hsv.y = Delta / hsv.z;
			ComponentType h = static_cast<ComponentType>(0);

			if(rgbColor.r == Max)
				// between yellow & magenta
				h = static_cast<ComponentType>(0) + ComponentType(60) * (rgbColor.g - rgbColor.b) / Delta;
			else if(rgbColor.g == Max)
				// between cyan & yellow
				h = static_cast<ComponentType>(120) + ComponentType(60) * (rgbColor.b - rgbColor.r) / Delta;
			else
				// between magenta & cyan
				h = static_cast<ComponentType>(240) + ComponentType(60) * (rgbColor.r - rgbColor.g) / Delta;

			if(h < ComponentType(0))
				hsv.x = h + ComponentType(360);
			else
				hsv.x = h;
		}
		else
		{
			// If r = g = b = 0 then s = 0, h is undefined
			hsv.y = static_cast<ComponentType>(0);
			hsv.x = static_cast<ComponentType>(0);
		}

		return hsv;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> saturation(ComponentType const s)
	{
		vec<3, ComponentType, defaultp> rgbw = vec<3, ComponentType, defaultp>(ComponentType(0.2126), ComponentType(0.7152), ComponentType(0.0722));

		vec<3, ComponentType, defaultp> const col((ComponentType(1) - s) * rgbw);

		mat<4, 4, ComponentType, defaultp> result(ComponentType(1));
		result[0][0] = col.x + s;
		result[0][1] = col.x;
		result[0][2] = col.x;
		result[1][0] = col.y;
		result[1][1] = col.y + s;
		result[1][2] = col.y;
		result[2][0] = col.z;
		result[2][1] = col.z;
		result[2][2] = col.z + s;

		return result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> saturation(const ComponentType s, const vec<3, ComponentType, Q>& color)
	{
		return vec<3, ComponentType, Q>(saturation(s) * vec<4, ComponentType, Q>(color, ComponentType(0)));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, ComponentType, Q> saturation(const ComponentType s, const vec<4, ComponentType, Q>& color)
	{
		return saturation(s) * color;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER ComponentType luminosity(const vec<3, ComponentType, Q>& color)
	{
		const vec<3, ComponentType, Q> tmp = vec<3, ComponentType, Q>(0.33, 0.59, 0.11);
		return dot(color, tmp);
	}
}//namespace glm
