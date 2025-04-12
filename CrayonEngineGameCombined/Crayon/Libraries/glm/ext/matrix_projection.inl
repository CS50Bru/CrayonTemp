namespace glm
{
	template<typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> projectZO(vec<3, ComponentType, Q> const& obj, mat<4, 4, ComponentType, Q> const& model, mat<4, 4, ComponentType, Q> const& proj, vec<4, U, Q> const& viewport)
	{
		vec<4, ComponentType, Q> tmp = vec<4, ComponentType, Q>(obj, static_cast<ComponentType>(1));
		tmp = model * tmp;
		tmp = proj * tmp;

		tmp /= tmp.w;
		tmp.x = tmp.x * static_cast<ComponentType>(0.5) + static_cast<ComponentType>(0.5);
		tmp.y = tmp.y * static_cast<ComponentType>(0.5) + static_cast<ComponentType>(0.5);

		tmp[0] = tmp[0] * ComponentType(viewport[2]) + ComponentType(viewport[0]);
		tmp[1] = tmp[1] * ComponentType(viewport[3]) + ComponentType(viewport[1]);

		return vec<3, ComponentType, Q>(tmp);
	}

	template<typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> projectNO(vec<3, ComponentType, Q> const& obj, mat<4, 4, ComponentType, Q> const& model, mat<4, 4, ComponentType, Q> const& proj, vec<4, U, Q> const& viewport)
	{
		vec<4, ComponentType, Q> tmp = vec<4, ComponentType, Q>(obj, static_cast<ComponentType>(1));
		tmp = model * tmp;
		tmp = proj * tmp;

		tmp /= tmp.w;
		tmp = tmp * static_cast<ComponentType>(0.5) + static_cast<ComponentType>(0.5);
		tmp[0] = tmp[0] * ComponentType(viewport[2]) + ComponentType(viewport[0]);
		tmp[1] = tmp[1] * ComponentType(viewport[3]) + ComponentType(viewport[1]);

		return vec<3, ComponentType, Q>(tmp);
	}

	template<typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> project(vec<3, ComponentType, Q> const& obj, mat<4, 4, ComponentType, Q> const& model, mat<4, 4, ComponentType, Q> const& proj, vec<4, U, Q> const& viewport)
	{
		if(GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT)
			return projectZO(obj, model, proj, viewport);
		else
			return projectNO(obj, model, proj, viewport);
	}

	template<typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> unProjectZO(vec<3, ComponentType, Q> const& win, mat<4, 4, ComponentType, Q> const& model, mat<4, 4, ComponentType, Q> const& proj, vec<4, U, Q> const& viewport)
	{
		mat<4, 4, ComponentType, Q> Inverse = inverse(proj * model);

		vec<4, ComponentType, Q> tmp = vec<4, ComponentType, Q>(win, ComponentType(1));
		tmp.x = (tmp.x - ComponentType(viewport[0])) / ComponentType(viewport[2]);
		tmp.y = (tmp.y - ComponentType(viewport[1])) / ComponentType(viewport[3]);
		tmp.x = tmp.x * static_cast<ComponentType>(2) - static_cast<ComponentType>(1);
		tmp.y = tmp.y * static_cast<ComponentType>(2) - static_cast<ComponentType>(1);

		vec<4, ComponentType, Q> obj = Inverse * tmp;
		obj /= obj.w;

		return vec<3, ComponentType, Q>(obj);
	}

	template<typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> unProjectNO(vec<3, ComponentType, Q> const& win, mat<4, 4, ComponentType, Q> const& model, mat<4, 4, ComponentType, Q> const& proj, vec<4, U, Q> const& viewport)
	{
		mat<4, 4, ComponentType, Q> Inverse = inverse(proj * model);

		vec<4, ComponentType, Q> tmp = vec<4, ComponentType, Q>(win, ComponentType(1));
		tmp.x = (tmp.x - ComponentType(viewport[0])) / ComponentType(viewport[2]);
		tmp.y = (tmp.y - ComponentType(viewport[1])) / ComponentType(viewport[3]);
		tmp = tmp * static_cast<ComponentType>(2) - static_cast<ComponentType>(1);

		vec<4, ComponentType, Q> obj = Inverse * tmp;
		obj /= obj.w;

		return vec<3, ComponentType, Q>(obj);
	}

	template<typename ComponentType, typename U, qualifier Q>
	GLM_FUNC_QUALIFIER vec<3, ComponentType, Q> unProject(vec<3, ComponentType, Q> const& win, mat<4, 4, ComponentType, Q> const& model, mat<4, 4, ComponentType, Q> const& proj, vec<4, U, Q> const& viewport)
	{
		if(GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT)
			return unProjectZO(win, model, proj, viewport);
		else
			return unProjectNO(win, model, proj, viewport);
	}

	template<typename ComponentType, qualifier Q, typename U>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> pickMatrix(vec<2, ComponentType, Q> const& center, vec<2, ComponentType, Q> const& delta, vec<4, U, Q> const& viewport)
	{
		assert(delta.x > static_cast<ComponentType>(0) && delta.y > static_cast<ComponentType>(0));
		mat<4, 4, ComponentType, Q> Result(static_cast<ComponentType>(1));

		if(!(delta.x > static_cast<ComponentType>(0) && delta.y > static_cast<ComponentType>(0)))
			return Result; // Error

		vec<3, ComponentType, Q> Temp(
			(static_cast<ComponentType>(viewport[2]) - static_cast<ComponentType>(2) * (center.x - static_cast<ComponentType>(viewport[0]))) / delta.x,
			(static_cast<ComponentType>(viewport[3]) - static_cast<ComponentType>(2) * (center.y - static_cast<ComponentType>(viewport[1]))) / delta.y,
			static_cast<ComponentType>(0));

		// Translate and scale the picked region to the entire window
		Result = translate(Result, Temp);
		return scale(Result, vec<3, ComponentType, Q>(static_cast<ComponentType>(viewport[2]) / delta.x, static_cast<ComponentType>(viewport[3]) / delta.y, static_cast<ComponentType>(1)));
	}
}//namespace glm
