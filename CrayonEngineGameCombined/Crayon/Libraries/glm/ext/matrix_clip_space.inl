namespace glm
{
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> ortho(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top)
	{
		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(1));
		Result[0][0] = static_cast<ComponentType>(2) / (right - left);
		Result[1][1] = static_cast<ComponentType>(2) / (top - bottom);
		Result[2][2] = - static_cast<ComponentType>(1);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> orthoLH_ZO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType zNear, ComponentType zFar)
	{
		mat<4, 4, ComponentType, defaultp> Result(1);
		Result[0][0] = static_cast<ComponentType>(2) / (right - left);
		Result[1][1] = static_cast<ComponentType>(2) / (top - bottom);
		Result[2][2] = static_cast<ComponentType>(1) / (zFar - zNear);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		Result[3][2] = - zNear / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> orthoLH_NO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType zNear, ComponentType zFar)
	{
		mat<4, 4, ComponentType, defaultp> Result(1);
		Result[0][0] = static_cast<ComponentType>(2) / (right - left);
		Result[1][1] = static_cast<ComponentType>(2) / (top - bottom);
		Result[2][2] = static_cast<ComponentType>(2) / (zFar - zNear);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		Result[3][2] = - (zFar + zNear) / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> orthoRH_ZO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType zNear, ComponentType zFar)
	{
		mat<4, 4, ComponentType, defaultp> Result(1);
		Result[0][0] = static_cast<ComponentType>(2) / (right - left);
		Result[1][1] = static_cast<ComponentType>(2) / (top - bottom);
		Result[2][2] = - static_cast<ComponentType>(1) / (zFar - zNear);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		Result[3][2] = - zNear / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> orthoRH_NO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType zNear, ComponentType zFar)
	{
		mat<4, 4, ComponentType, defaultp> Result(1);
		Result[0][0] = static_cast<ComponentType>(2) / (right - left);
		Result[1][1] = static_cast<ComponentType>(2) / (top - bottom);
		Result[2][2] = - static_cast<ComponentType>(2) / (zFar - zNear);
		Result[3][0] = - (right + left) / (right - left);
		Result[3][1] = - (top + bottom) / (top - bottom);
		Result[3][2] = - (zFar + zNear) / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> orthoZO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return orthoLH_ZO(left, right, bottom, top, zNear, zFar);
#		else
			return orthoRH_ZO(left, right, bottom, top, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> orthoNO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return orthoLH_NO(left, right, bottom, top, zNear, zFar);
#		else
			return orthoRH_NO(left, right, bottom, top, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> orthoLH(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return orthoLH_ZO(left, right, bottom, top, zNear, zFar);
#		else
			return orthoLH_NO(left, right, bottom, top, zNear, zFar);
#		endif

	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> orthoRH(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return orthoRH_ZO(left, right, bottom, top, zNear, zFar);
#		else
			return orthoRH_NO(left, right, bottom, top, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> ortho(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_ZO
			return orthoLH_ZO(left, right, bottom, top, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_NO
			return orthoLH_NO(left, right, bottom, top, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
			return orthoRH_ZO(left, right, bottom, top, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_NO
			return orthoRH_NO(left, right, bottom, top, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> frustumLH_ZO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType nearVal, ComponentType farVal)
	{
		mat<4, 4, ComponentType, defaultp> Result(0);
		Result[0][0] = (static_cast<ComponentType>(2) * nearVal) / (right - left);
		Result[1][1] = (static_cast<ComponentType>(2) * nearVal) / (top - bottom);
		Result[2][0] = (right + left) / (right - left);
		Result[2][1] = (top + bottom) / (top - bottom);
		Result[2][2] = farVal / (farVal - nearVal);
		Result[2][3] = static_cast<ComponentType>(1);
		Result[3][2] = -(farVal * nearVal) / (farVal - nearVal);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> frustumLH_NO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType nearVal, ComponentType farVal)
	{
		mat<4, 4, ComponentType, defaultp> Result(0);
		Result[0][0] = (static_cast<ComponentType>(2) * nearVal) / (right - left);
		Result[1][1] = (static_cast<ComponentType>(2) * nearVal) / (top - bottom);
		Result[2][0] = (right + left) / (right - left);
		Result[2][1] = (top + bottom) / (top - bottom);
		Result[2][2] = (farVal + nearVal) / (farVal - nearVal);
		Result[2][3] = static_cast<ComponentType>(1);
		Result[3][2] = - (static_cast<ComponentType>(2) * farVal * nearVal) / (farVal - nearVal);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> frustumRH_ZO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType nearVal, ComponentType farVal)
	{
		mat<4, 4, ComponentType, defaultp> Result(0);
		Result[0][0] = (static_cast<ComponentType>(2) * nearVal) / (right - left);
		Result[1][1] = (static_cast<ComponentType>(2) * nearVal) / (top - bottom);
		Result[2][0] = (right + left) / (right - left);
		Result[2][1] = (top + bottom) / (top - bottom);
		Result[2][2] = farVal / (nearVal - farVal);
		Result[2][3] = static_cast<ComponentType>(-1);
		Result[3][2] = -(farVal * nearVal) / (farVal - nearVal);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> frustumRH_NO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType nearVal, ComponentType farVal)
	{
		mat<4, 4, ComponentType, defaultp> Result(0);
		Result[0][0] = (static_cast<ComponentType>(2) * nearVal) / (right - left);
		Result[1][1] = (static_cast<ComponentType>(2) * nearVal) / (top - bottom);
		Result[2][0] = (right + left) / (right - left);
		Result[2][1] = (top + bottom) / (top - bottom);
		Result[2][2] = - (farVal + nearVal) / (farVal - nearVal);
		Result[2][3] = static_cast<ComponentType>(-1);
		Result[3][2] = - (static_cast<ComponentType>(2) * farVal * nearVal) / (farVal - nearVal);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> frustumZO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType nearVal, ComponentType farVal)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return frustumLH_ZO(left, right, bottom, top, nearVal, farVal);
#		else
			return frustumRH_ZO(left, right, bottom, top, nearVal, farVal);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> frustumNO(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType nearVal, ComponentType farVal)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return frustumLH_NO(left, right, bottom, top, nearVal, farVal);
#		else
			return frustumRH_NO(left, right, bottom, top, nearVal, farVal);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> frustumLH(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType nearVal, ComponentType farVal)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return frustumLH_ZO(left, right, bottom, top, nearVal, farVal);
#		else
			return frustumLH_NO(left, right, bottom, top, nearVal, farVal);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> frustumRH(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType nearVal, ComponentType farVal)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return frustumRH_ZO(left, right, bottom, top, nearVal, farVal);
#		else
			return frustumRH_NO(left, right, bottom, top, nearVal, farVal);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> frustum(ComponentType left, ComponentType right, ComponentType bottom, ComponentType top, ComponentType nearVal, ComponentType farVal)
	{
#		if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_ZO
			return frustumLH_ZO(left, right, bottom, top, nearVal, farVal);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_NO
			return frustumLH_NO(left, right, bottom, top, nearVal, farVal);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
			return frustumRH_ZO(left, right, bottom, top, nearVal, farVal);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_NO
			return frustumRH_NO(left, right, bottom, top, nearVal, farVal);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveRH_ZO(ComponentType fovy, ComponentType aspect, ComponentType zNear, ComponentType zFar)
	{
		assert(abs(aspect - std::numeric_limits<ComponentType>::epsilon()) > static_cast<ComponentType>(0));

		ComponentType const tanHalfFovy = tan(fovy / static_cast<ComponentType>(2));

		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(0));
		Result[0][0] = static_cast<ComponentType>(1) / (aspect * tanHalfFovy);
		Result[1][1] = static_cast<ComponentType>(1) / (tanHalfFovy);
		Result[2][2] = zFar / (zNear - zFar);
		Result[2][3] = - static_cast<ComponentType>(1);
		Result[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveRH_NO(ComponentType fovy, ComponentType aspect, ComponentType zNear, ComponentType zFar)
	{
		assert(abs(aspect - std::numeric_limits<ComponentType>::epsilon()) > static_cast<ComponentType>(0));

		ComponentType const tanHalfFovy = tan(fovy / static_cast<ComponentType>(2));

		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(0));
		Result[0][0] = static_cast<ComponentType>(1) / (aspect * tanHalfFovy);
		Result[1][1] = static_cast<ComponentType>(1) / (tanHalfFovy);
		Result[2][2] = - (zFar + zNear) / (zFar - zNear);
		Result[2][3] = - static_cast<ComponentType>(1);
		Result[3][2] = - (static_cast<ComponentType>(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveLH_ZO(ComponentType fovy, ComponentType aspect, ComponentType zNear, ComponentType zFar)
	{
		assert(abs(aspect - std::numeric_limits<ComponentType>::epsilon()) > static_cast<ComponentType>(0));

		ComponentType const tanHalfFovy = tan(fovy / static_cast<ComponentType>(2));

		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(0));
		Result[0][0] = static_cast<ComponentType>(1) / (aspect * tanHalfFovy);
		Result[1][1] = static_cast<ComponentType>(1) / (tanHalfFovy);
		Result[2][2] = zFar / (zFar - zNear);
		Result[2][3] = static_cast<ComponentType>(1);
		Result[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveLH_NO(ComponentType fovy, ComponentType aspect, ComponentType zNear, ComponentType zFar)
	{
		assert(abs(aspect - std::numeric_limits<ComponentType>::epsilon()) > static_cast<ComponentType>(0));

		ComponentType const tanHalfFovy = tan(fovy / static_cast<ComponentType>(2));

		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(0));
		Result[0][0] = static_cast<ComponentType>(1) / (aspect * tanHalfFovy);
		Result[1][1] = static_cast<ComponentType>(1) / (tanHalfFovy);
		Result[2][2] = (zFar + zNear) / (zFar - zNear);
		Result[2][3] = static_cast<ComponentType>(1);
		Result[3][2] = - (static_cast<ComponentType>(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveZO(ComponentType fovy, ComponentType aspect, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return perspectiveLH_ZO(fovy, aspect, zNear, zFar);
#		else
			return perspectiveRH_ZO(fovy, aspect, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveNO(ComponentType fovy, ComponentType aspect, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return perspectiveLH_NO(fovy, aspect, zNear, zFar);
#		else
			return perspectiveRH_NO(fovy, aspect, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveLH(ComponentType fovy, ComponentType aspect, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return perspectiveLH_ZO(fovy, aspect, zNear, zFar);
#		else
			return perspectiveLH_NO(fovy, aspect, zNear, zFar);
#		endif

	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveRH(ComponentType fovy, ComponentType aspect, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return perspectiveRH_ZO(fovy, aspect, zNear, zFar);
#		else
			return perspectiveRH_NO(fovy, aspect, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspective(ComponentType fovy, ComponentType aspect, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_ZO
			return perspectiveLH_ZO(fovy, aspect, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_NO
			return perspectiveLH_NO(fovy, aspect, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
			return perspectiveRH_ZO(fovy, aspect, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_NO
			return perspectiveRH_NO(fovy, aspect, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveFovRH_ZO(ComponentType fov, ComponentType width, ComponentType height, ComponentType zNear, ComponentType zFar)
	{
		assert(width > static_cast<ComponentType>(0));
		assert(height > static_cast<ComponentType>(0));
		assert(fov > static_cast<ComponentType>(0));

		ComponentType const rad = fov;
		ComponentType const h = glm::cos(static_cast<ComponentType>(0.5) * rad) / glm::sin(static_cast<ComponentType>(0.5) * rad);
		ComponentType const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(0));
		Result[0][0] = w;
		Result[1][1] = h;
		Result[2][2] = zFar / (zNear - zFar);
		Result[2][3] = - static_cast<ComponentType>(1);
		Result[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveFovRH_NO(ComponentType fov, ComponentType width, ComponentType height, ComponentType zNear, ComponentType zFar)
	{
		assert(width > static_cast<ComponentType>(0));
		assert(height > static_cast<ComponentType>(0));
		assert(fov > static_cast<ComponentType>(0));

		ComponentType const rad = fov;
		ComponentType const h = glm::cos(static_cast<ComponentType>(0.5) * rad) / glm::sin(static_cast<ComponentType>(0.5) * rad);
		ComponentType const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(0));
		Result[0][0] = w;
		Result[1][1] = h;
		Result[2][2] = - (zFar + zNear) / (zFar - zNear);
		Result[2][3] = - static_cast<ComponentType>(1);
		Result[3][2] = - (static_cast<ComponentType>(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveFovLH_ZO(ComponentType fov, ComponentType width, ComponentType height, ComponentType zNear, ComponentType zFar)
	{
		assert(width > static_cast<ComponentType>(0));
		assert(height > static_cast<ComponentType>(0));
		assert(fov > static_cast<ComponentType>(0));

		ComponentType const rad = fov;
		ComponentType const h = glm::cos(static_cast<ComponentType>(0.5) * rad) / glm::sin(static_cast<ComponentType>(0.5) * rad);
		ComponentType const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(0));
		Result[0][0] = w;
		Result[1][1] = h;
		Result[2][2] = zFar / (zFar - zNear);
		Result[2][3] = static_cast<ComponentType>(1);
		Result[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveFovLH_NO(ComponentType fov, ComponentType width, ComponentType height, ComponentType zNear, ComponentType zFar)
	{
		assert(width > static_cast<ComponentType>(0));
		assert(height > static_cast<ComponentType>(0));
		assert(fov > static_cast<ComponentType>(0));

		ComponentType const rad = fov;
		ComponentType const h = glm::cos(static_cast<ComponentType>(0.5) * rad) / glm::sin(static_cast<ComponentType>(0.5) * rad);
		ComponentType const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(0));
		Result[0][0] = w;
		Result[1][1] = h;
		Result[2][2] = (zFar + zNear) / (zFar - zNear);
		Result[2][3] = static_cast<ComponentType>(1);
		Result[3][2] = - (static_cast<ComponentType>(2) * zFar * zNear) / (zFar - zNear);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveFovZO(ComponentType fov, ComponentType width, ComponentType height, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return perspectiveFovLH_ZO(fov, width, height, zNear, zFar);
#		else
			return perspectiveFovRH_ZO(fov, width, height, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveFovNO(ComponentType fov, ComponentType width, ComponentType height, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return perspectiveFovLH_NO(fov, width, height, zNear, zFar);
#		else
			return perspectiveFovRH_NO(fov, width, height, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveFovLH(ComponentType fov, ComponentType width, ComponentType height, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return perspectiveFovLH_ZO(fov, width, height, zNear, zFar);
#		else
			return perspectiveFovLH_NO(fov, width, height, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveFovRH(ComponentType fov, ComponentType width, ComponentType height, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT
			return perspectiveFovRH_ZO(fov, width, height, zNear, zFar);
#		else
			return perspectiveFovRH_NO(fov, width, height, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> perspectiveFov(ComponentType fov, ComponentType width, ComponentType height, ComponentType zNear, ComponentType zFar)
	{
#		if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_ZO
			return perspectiveFovLH_ZO(fov, width, height, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_LH_NO
			return perspectiveFovLH_NO(fov, width, height, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
			return perspectiveFovRH_ZO(fov, width, height, zNear, zFar);
#		elif GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_NO
			return perspectiveFovRH_NO(fov, width, height, zNear, zFar);
#		endif
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> infinitePerspectiveRH(ComponentType fovy, ComponentType aspect, ComponentType zNear)
	{
		ComponentType const range = tan(fovy / static_cast<ComponentType>(2)) * zNear;
		ComponentType const left = -range * aspect;
		ComponentType const right = range * aspect;
		ComponentType const bottom = -range;
		ComponentType const top = range;

		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(0));
		Result[0][0] = (static_cast<ComponentType>(2) * zNear) / (right - left);
		Result[1][1] = (static_cast<ComponentType>(2) * zNear) / (top - bottom);
		Result[2][2] = - static_cast<ComponentType>(1);
		Result[2][3] = - static_cast<ComponentType>(1);
		Result[3][2] = - static_cast<ComponentType>(2) * zNear;
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> infinitePerspectiveLH(ComponentType fovy, ComponentType aspect, ComponentType zNear)
	{
		ComponentType const range = tan(fovy / static_cast<ComponentType>(2)) * zNear;
		ComponentType const left = -range * aspect;
		ComponentType const right = range * aspect;
		ComponentType const bottom = -range;
		ComponentType const top = range;

		mat<4, 4, ComponentType, defaultp> Result(ComponentType(0));
		Result[0][0] = (static_cast<ComponentType>(2) * zNear) / (right - left);
		Result[1][1] = (static_cast<ComponentType>(2) * zNear) / (top - bottom);
		Result[2][2] = static_cast<ComponentType>(1);
		Result[2][3] = static_cast<ComponentType>(1);
		Result[3][2] = - static_cast<ComponentType>(2) * zNear;
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> infinitePerspective(ComponentType fovy, ComponentType aspect, ComponentType zNear)
	{
#		if GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT
			return infinitePerspectiveLH(fovy, aspect, zNear);
#		else
			return infinitePerspectiveRH(fovy, aspect, zNear);
#		endif
	}

	// Infinite projection matrix: http://www.terathon.com/gdc07_lengyel.pdf
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> tweakedInfinitePerspective(ComponentType fovy, ComponentType aspect, ComponentType zNear, ComponentType ep)
	{
		ComponentType const range = tan(fovy / static_cast<ComponentType>(2)) * zNear;
		ComponentType const left = -range * aspect;
		ComponentType const right = range * aspect;
		ComponentType const bottom = -range;
		ComponentType const top = range;

		mat<4, 4, ComponentType, defaultp> Result(static_cast<ComponentType>(0));
		Result[0][0] = (static_cast<ComponentType>(2) * zNear) / (right - left);
		Result[1][1] = (static_cast<ComponentType>(2) * zNear) / (top - bottom);
		Result[2][2] = ep - static_cast<ComponentType>(1);
		Result[2][3] = static_cast<ComponentType>(-1);
		Result[3][2] = (ep - static_cast<ComponentType>(2)) * zNear;
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> tweakedInfinitePerspective(ComponentType fovy, ComponentType aspect, ComponentType zNear)
	{
		return tweakedInfinitePerspective(fovy, aspect, zNear, epsilon<ComponentType>());
	}
}//namespace glm
