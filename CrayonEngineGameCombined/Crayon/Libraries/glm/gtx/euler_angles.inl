/// @ref gtx_euler_angles

#include "compatibility.hpp" // glm::atan2

namespace glm
{
	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleX
	(
		ComponentType const& angleX
	)
	{
		ComponentType cosX = glm::cos(angleX);
		ComponentType sinX = glm::sin(angleX);

		return mat<4, 4, ComponentType, defaultp>(
			ComponentType(1), ComponentType(0), ComponentType(0), ComponentType(0),
			ComponentType(0), cosX, sinX, ComponentType(0),
			ComponentType(0),-sinX, cosX, ComponentType(0),
			ComponentType(0), ComponentType(0), ComponentType(0), ComponentType(1));
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleY
	(
		ComponentType const& angleY
	)
	{
		ComponentType cosY = glm::cos(angleY);
		ComponentType sinY = glm::sin(angleY);

		return mat<4, 4, ComponentType, defaultp>(
			cosY,	ComponentType(0),	-sinY,	ComponentType(0),
			ComponentType(0),	ComponentType(1),	ComponentType(0),	ComponentType(0),
			sinY,	ComponentType(0),	cosY,	ComponentType(0),
			ComponentType(0),	ComponentType(0),	ComponentType(0),	ComponentType(1));
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleZ
	(
		ComponentType const& angleZ
	)
	{
		ComponentType cosZ = glm::cos(angleZ);
		ComponentType sinZ = glm::sin(angleZ);

		return mat<4, 4, ComponentType, defaultp>(
			cosZ,	sinZ,	ComponentType(0), ComponentType(0),
			-sinZ,	cosZ,	ComponentType(0), ComponentType(0),
			ComponentType(0),	ComponentType(0),	ComponentType(1), ComponentType(0),
			ComponentType(0),	ComponentType(0),	ComponentType(0), ComponentType(1));
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> derivedEulerAngleX
	(
		ComponentType const & angleX,
		ComponentType const & angularVelocityX
	)
	{
		ComponentType cosX = glm::cos(angleX) * angularVelocityX;
		ComponentType sinX = glm::sin(angleX) * angularVelocityX;

		return mat<4, 4, ComponentType, defaultp>(
			ComponentType(0), ComponentType(0), ComponentType(0), ComponentType(0),
			ComponentType(0),-sinX, cosX, ComponentType(0),
			ComponentType(0),-cosX,-sinX, ComponentType(0),
			ComponentType(0), ComponentType(0), ComponentType(0), ComponentType(0));
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> derivedEulerAngleY
	(
		ComponentType const & angleY,
		ComponentType const & angularVelocityY
	)
	{
		ComponentType cosY = glm::cos(angleY) * angularVelocityY;
		ComponentType sinY = glm::sin(angleY) * angularVelocityY;

		return mat<4, 4, ComponentType, defaultp>(
			-sinY, ComponentType(0), -cosY, ComponentType(0),
			 ComponentType(0), ComponentType(0),  ComponentType(0), ComponentType(0),
			 cosY, ComponentType(0), -sinY, ComponentType(0),
			 ComponentType(0), ComponentType(0),  ComponentType(0), ComponentType(0));
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> derivedEulerAngleZ
	(
		ComponentType const & angleZ,
		ComponentType const & angularVelocityZ
	)
	{
		ComponentType cosZ = glm::cos(angleZ) * angularVelocityZ;
		ComponentType sinZ = glm::sin(angleZ) * angularVelocityZ;

		return mat<4, 4, ComponentType, defaultp>(
			-sinZ,  cosZ, ComponentType(0), ComponentType(0),
			-cosZ, -sinZ, ComponentType(0), ComponentType(0),
			 ComponentType(0),  ComponentType(0), ComponentType(0), ComponentType(0),
			 ComponentType(0),  ComponentType(0), ComponentType(0), ComponentType(0));
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleXY
	(
		ComponentType const& angleX,
		ComponentType const& angleY
	)
	{
		ComponentType cosX = glm::cos(angleX);
		ComponentType sinX = glm::sin(angleX);
		ComponentType cosY = glm::cos(angleY);
		ComponentType sinY = glm::sin(angleY);

		return mat<4, 4, ComponentType, defaultp>(
			cosY,   -sinX * -sinY,  cosX * -sinY,   ComponentType(0),
			ComponentType(0),   cosX,           sinX,           ComponentType(0),
			sinY,   -sinX * cosY,   cosX * cosY,    ComponentType(0),
			ComponentType(0),   ComponentType(0),           ComponentType(0),           ComponentType(1));
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleYX
	(
		ComponentType const& angleY,
		ComponentType const& angleX
	)
	{
		ComponentType cosX = glm::cos(angleX);
		ComponentType sinX = glm::sin(angleX);
		ComponentType cosY = glm::cos(angleY);
		ComponentType sinY = glm::sin(angleY);

		return mat<4, 4, ComponentType, defaultp>(
			cosY,          0,      -sinY,    ComponentType(0),
			sinY * sinX,  cosX, cosY * sinX, ComponentType(0),
			sinY * cosX, -sinX, cosY * cosX, ComponentType(0),
			ComponentType(0),         ComponentType(0),     ComponentType(0),    ComponentType(1));
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleXZ
	(
		ComponentType const& angleX,
		ComponentType const& angleZ
	)
	{
		return eulerAngleX(angleX) * eulerAngleZ(angleZ);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleZX
	(
		ComponentType const& angleZ,
		ComponentType const& angleX
	)
	{
		return eulerAngleZ(angleZ) * eulerAngleX(angleX);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleYZ
	(
		ComponentType const& angleY,
		ComponentType const& angleZ
	)
	{
		return eulerAngleY(angleY) * eulerAngleZ(angleZ);
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleZY
	(
		ComponentType const& angleZ,
		ComponentType const& angleY
	)
	{
		return eulerAngleZ(angleZ) * eulerAngleY(angleY);
	}

    template<typename ComponentType>
    GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleXYZ
    (
     ComponentType const& t1,
     ComponentType const& t2,
     ComponentType const& t3
     )
    {
        ComponentType c1 = glm::cos(-t1);
        ComponentType c2 = glm::cos(-t2);
        ComponentType c3 = glm::cos(-t3);
        ComponentType s1 = glm::sin(-t1);
        ComponentType s2 = glm::sin(-t2);
        ComponentType s3 = glm::sin(-t3);

        mat<4, 4, ComponentType, defaultp> Result;
        Result[0][0] = c2 * c3;
        Result[0][1] =-c1 * s3 + s1 * s2 * c3;
        Result[0][2] = s1 * s3 + c1 * s2 * c3;
        Result[0][3] = static_cast<ComponentType>(0);
        Result[1][0] = c2 * s3;
        Result[1][1] = c1 * c3 + s1 * s2 * s3;
        Result[1][2] =-s1 * c3 + c1 * s2 * s3;
        Result[1][3] = static_cast<ComponentType>(0);
        Result[2][0] =-s2;
        Result[2][1] = s1 * c2;
        Result[2][2] = c1 * c2;
        Result[2][3] = static_cast<ComponentType>(0);
        Result[3][0] = static_cast<ComponentType>(0);
        Result[3][1] = static_cast<ComponentType>(0);
        Result[3][2] = static_cast<ComponentType>(0);
        Result[3][3] = static_cast<ComponentType>(1);
        return Result;
    }

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleYXZ
	(
		ComponentType const& yaw,
		ComponentType const& pitch,
		ComponentType const& roll
	)
	{
		ComponentType tmp_ch = glm::cos(yaw);
		ComponentType tmp_sh = glm::sin(yaw);
		ComponentType tmp_cp = glm::cos(pitch);
		ComponentType tmp_sp = glm::sin(pitch);
		ComponentType tmp_cb = glm::cos(roll);
		ComponentType tmp_sb = glm::sin(roll);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
		Result[0][1] = tmp_sb * tmp_cp;
		Result[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
		Result[1][1] = tmp_cb * tmp_cp;
		Result[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = tmp_sh * tmp_cp;
		Result[2][1] = -tmp_sp;
		Result[2][2] = tmp_ch * tmp_cp;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleXZX
	(
		ComponentType const & t1,
		ComponentType const & t2,
		ComponentType const & t3
	)
	{
		ComponentType c1 = glm::cos(t1);
		ComponentType s1 = glm::sin(t1);
		ComponentType c2 = glm::cos(t2);
		ComponentType s2 = glm::sin(t2);
		ComponentType c3 = glm::cos(t3);
		ComponentType s3 = glm::sin(t3);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = c2;
		Result[0][1] = c1 * s2;
		Result[0][2] = s1 * s2;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] =-c3 * s2;
		Result[1][1] = c1 * c2 * c3 - s1 * s3;
		Result[1][2] = c1 * s3 + c2 * c3 * s1;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = s2 * s3;
		Result[2][1] =-c3 * s1 - c1 * c2 * s3;
		Result[2][2] = c1 * c3 - c2 * s1 * s3;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleXYX
	(
		ComponentType const & t1,
		ComponentType const & t2,
		ComponentType const & t3
	)
	{
		ComponentType c1 = glm::cos(t1);
		ComponentType s1 = glm::sin(t1);
		ComponentType c2 = glm::cos(t2);
		ComponentType s2 = glm::sin(t2);
		ComponentType c3 = glm::cos(t3);
		ComponentType s3 = glm::sin(t3);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = c2;
		Result[0][1] = s1 * s2;
		Result[0][2] =-c1 * s2;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] = s2 * s3;
		Result[1][1] = c1 * c3 - c2 * s1 * s3;
		Result[1][2] = c3 * s1 + c1 * c2 * s3;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = c3 * s2;
		Result[2][1] =-c1 * s3 - c2 * c3 * s1;
		Result[2][2] = c1 * c2 * c3 - s1 * s3;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleYXY
	(
		ComponentType const & t1,
		ComponentType const & t2,
		ComponentType const & t3
	)
	{
		ComponentType c1 = glm::cos(t1);
		ComponentType s1 = glm::sin(t1);
		ComponentType c2 = glm::cos(t2);
		ComponentType s2 = glm::sin(t2);
		ComponentType c3 = glm::cos(t3);
		ComponentType s3 = glm::sin(t3);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = c1 * c3 - c2 * s1 * s3;
		Result[0][1] = s2* s3;
		Result[0][2] =-c3 * s1 - c1 * c2 * s3;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] = s1 * s2;
		Result[1][1] = c2;
		Result[1][2] = c1 * s2;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = c1 * s3 + c2 * c3 * s1;
		Result[2][1] =-c3 * s2;
		Result[2][2] = c1 * c2 * c3 - s1 * s3;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleYZY
	(
		ComponentType const & t1,
		ComponentType const & t2,
		ComponentType const & t3
	)
	{
		ComponentType c1 = glm::cos(t1);
		ComponentType s1 = glm::sin(t1);
		ComponentType c2 = glm::cos(t2);
		ComponentType s2 = glm::sin(t2);
		ComponentType c3 = glm::cos(t3);
		ComponentType s3 = glm::sin(t3);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = c1 * c2 * c3 - s1 * s3;
		Result[0][1] = c3 * s2;
		Result[0][2] =-c1 * s3 - c2 * c3 * s1;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] =-c1 * s2;
		Result[1][1] = c2;
		Result[1][2] = s1 * s2;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = c3 * s1 + c1 * c2 * s3;
		Result[2][1] = s2 * s3;
		Result[2][2] = c1 * c3 - c2 * s1 * s3;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleZYZ
	(
		ComponentType const & t1,
		ComponentType const & t2,
		ComponentType const & t3
	)
	{
		ComponentType c1 = glm::cos(t1);
		ComponentType s1 = glm::sin(t1);
		ComponentType c2 = glm::cos(t2);
		ComponentType s2 = glm::sin(t2);
		ComponentType c3 = glm::cos(t3);
		ComponentType s3 = glm::sin(t3);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = c1 * c2 * c3 - s1 * s3;
		Result[0][1] = c1 * s3 + c2 * c3 * s1;
		Result[0][2] =-c3 * s2;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] =-c3 * s1 - c1 * c2 * s3;
		Result[1][1] = c1 * c3 - c2 * s1 * s3;
		Result[1][2] = s2 * s3;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = c1 * s2;
		Result[2][1] = s1 * s2;
		Result[2][2] = c2;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleZXZ
	(
		ComponentType const & t1,
		ComponentType const & t2,
		ComponentType const & t3
	)
	{
		ComponentType c1 = glm::cos(t1);
		ComponentType s1 = glm::sin(t1);
		ComponentType c2 = glm::cos(t2);
		ComponentType s2 = glm::sin(t2);
		ComponentType c3 = glm::cos(t3);
		ComponentType s3 = glm::sin(t3);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = c1 * c3 - c2 * s1 * s3;
		Result[0][1] = c3 * s1 + c1 * c2 * s3;
		Result[0][2] = s2 *s3;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] =-c1 * s3 - c2 * c3 * s1;
		Result[1][1] = c1 * c2 * c3 - s1 * s3;
		Result[1][2] = c3 * s2;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = s1 * s2;
		Result[2][1] =-c1 * s2;
		Result[2][2] = c2;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleXZY
	(
		ComponentType const & t1,
		ComponentType const & t2,
		ComponentType const & t3
	)
	{
		ComponentType c1 = glm::cos(t1);
		ComponentType s1 = glm::sin(t1);
		ComponentType c2 = glm::cos(t2);
		ComponentType s2 = glm::sin(t2);
		ComponentType c3 = glm::cos(t3);
		ComponentType s3 = glm::sin(t3);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = c2 * c3;
		Result[0][1] = s1 * s3 + c1 * c3 * s2;
		Result[0][2] = c3 * s1 * s2 - c1 * s3;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] =-s2;
		Result[1][1] = c1 * c2;
		Result[1][2] = c2 * s1;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = c2 * s3;
		Result[2][1] = c1 * s2 * s3 - c3 * s1;
		Result[2][2] = c1 * c3 + s1 * s2 *s3;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleYZX
	(
		ComponentType const & t1,
		ComponentType const & t2,
		ComponentType const & t3
	)
	{
		ComponentType c1 = glm::cos(t1);
		ComponentType s1 = glm::sin(t1);
		ComponentType c2 = glm::cos(t2);
		ComponentType s2 = glm::sin(t2);
		ComponentType c3 = glm::cos(t3);
		ComponentType s3 = glm::sin(t3);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = c1 * c2;
		Result[0][1] = s2;
		Result[0][2] =-c2 * s1;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] = s1 * s3 - c1 * c3 * s2;
		Result[1][1] = c2 * c3;
		Result[1][2] = c1 * s3 + c3 * s1 * s2;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = c3 * s1 + c1 * s2 * s3;
		Result[2][1] =-c2 * s3;
		Result[2][2] = c1 * c3 - s1 * s2 * s3;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleZYX
	(
		ComponentType const & t1,
		ComponentType const & t2,
		ComponentType const & t3
	)
	{
		ComponentType c1 = glm::cos(t1);
		ComponentType s1 = glm::sin(t1);
		ComponentType c2 = glm::cos(t2);
		ComponentType s2 = glm::sin(t2);
		ComponentType c3 = glm::cos(t3);
		ComponentType s3 = glm::sin(t3);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = c1 * c2;
		Result[0][1] = c2 * s1;
		Result[0][2] =-s2;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] = c1 * s2 * s3 - c3 * s1;
		Result[1][1] = c1 * c3 + s1 * s2 * s3;
		Result[1][2] = c2 * s3;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = s1 * s3 + c1 * c3 * s2;
		Result[2][1] = c3 * s1 * s2 - c1 * s3;
		Result[2][2] = c2 * c3;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> eulerAngleZXY
	(
		ComponentType const & t1,
		ComponentType const & t2,
		ComponentType const & t3
	)
	{
		ComponentType c1 = glm::cos(t1);
		ComponentType s1 = glm::sin(t1);
		ComponentType c2 = glm::cos(t2);
		ComponentType s2 = glm::sin(t2);
		ComponentType c3 = glm::cos(t3);
		ComponentType s3 = glm::sin(t3);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = c1 * c3 - s1 * s2 * s3;
		Result[0][1] = c3 * s1 + c1 * s2 * s3;
		Result[0][2] =-c2 * s3;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] =-c2 * s1;
		Result[1][1] = c1 * c2;
		Result[1][2] = s2;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = c1 * s3 + c3 * s1 * s2;
		Result[2][1] = s1 * s3 - c1 * c3 * s2;
		Result[2][2] = c2 * c3;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, defaultp> yawPitchRoll
	(
		ComponentType const& yaw,
		ComponentType const& pitch,
		ComponentType const& roll
	)
	{
		ComponentType tmp_ch = glm::cos(yaw);
		ComponentType tmp_sh = glm::sin(yaw);
		ComponentType tmp_cp = glm::cos(pitch);
		ComponentType tmp_sp = glm::sin(pitch);
		ComponentType tmp_cb = glm::cos(roll);
		ComponentType tmp_sb = glm::sin(roll);

		mat<4, 4, ComponentType, defaultp> Result;
		Result[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
		Result[0][1] = tmp_sb * tmp_cp;
		Result[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
		Result[0][3] = static_cast<ComponentType>(0);
		Result[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
		Result[1][1] = tmp_cb * tmp_cp;
		Result[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
		Result[1][3] = static_cast<ComponentType>(0);
		Result[2][0] = tmp_sh * tmp_cp;
		Result[2][1] = -tmp_sp;
		Result[2][2] = tmp_ch * tmp_cp;
		Result[2][3] = static_cast<ComponentType>(0);
		Result[3][0] = static_cast<ComponentType>(0);
		Result[3][1] = static_cast<ComponentType>(0);
		Result[3][2] = static_cast<ComponentType>(0);
		Result[3][3] = static_cast<ComponentType>(1);
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<2, 2, ComponentType, defaultp> orientate2
	(
		ComponentType const& angle
	)
	{
		ComponentType c = glm::cos(angle);
		ComponentType s = glm::sin(angle);

		mat<2, 2, ComponentType, defaultp> Result;
		Result[0][0] = c;
		Result[0][1] = s;
		Result[1][0] = -s;
		Result[1][1] = c;
		return Result;
	}

	template<typename ComponentType>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, defaultp> orientate3
	(
		ComponentType const& angle
	)
	{
		ComponentType c = glm::cos(angle);
		ComponentType s = glm::sin(angle);

		mat<3, 3, ComponentType, defaultp> Result;
		Result[0][0] = c;
		Result[0][1] = s;
		Result[0][2] = 0.0f;
		Result[1][0] = -s;
		Result[1][1] = c;
		Result[1][2] = 0.0f;
		Result[2][0] = 0.0f;
		Result[2][1] = 0.0f;
		Result[2][2] = 1.0f;
		return Result;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, ComponentType, Q> orientate3
	(
		vec<3, ComponentType, Q> const& angles
	)
	{
		return mat<3, 3, ComponentType, Q>(yawPitchRoll(angles.z, angles.x, angles.y));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> orientate4
	(
		vec<3, ComponentType, Q> const& angles
	)
	{
		return yawPitchRoll(angles.z, angles.x, angles.y);
	}

    template<typename ComponentType>
    GLM_FUNC_DECL void extractEulerAngleXYZ(mat<4, 4, ComponentType, defaultp> const& M,
                                            ComponentType & t1,
                                            ComponentType & t2,
                                            ComponentType & t3)
    {
        ComponentType T1 = glm::atan2<ComponentType, defaultp>(M[2][1], M[2][2]);
        ComponentType C2 = glm::sqrt(M[0][0]*M[0][0] + M[1][0]*M[1][0]);
        ComponentType T2 = glm::atan2<ComponentType, defaultp>(-M[2][0], C2);
        ComponentType S1 = glm::sin(T1);
        ComponentType C1 = glm::cos(T1);
        ComponentType T3 = glm::atan2<ComponentType, defaultp>(S1*M[0][2] - C1*M[0][1], C1*M[1][1] - S1*M[1][2  ]);
        t1 = -T1;
        t2 = -T2;
        t3 = -T3;
    }

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleYXZ(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(M[2][0], M[2][2]);
		ComponentType C2 = glm::sqrt(M[0][1]*M[0][1] + M[1][1]*M[1][1]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(-M[2][1], C2);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(S1*M[1][2] - C1*M[1][0], C1*M[0][0] - S1*M[0][2]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleXZX(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(M[0][2], M[0][1]);
		ComponentType S2 = glm::sqrt(M[1][0]*M[1][0] + M[2][0]*M[2][0]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(S2, M[0][0]);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(C1*M[1][2] - S1*M[1][1], C1*M[2][2] - S1*M[2][1]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleXYX(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(M[0][1], -M[0][2]);
		ComponentType S2 = glm::sqrt(M[1][0]*M[1][0] + M[2][0]*M[2][0]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(S2, M[0][0]);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(-C1*M[2][1] - S1*M[2][2], C1*M[1][1] + S1*M[1][2]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleYXY(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(M[1][0], M[1][2]);
		ComponentType S2 = glm::sqrt(M[0][1]*M[0][1] + M[2][1]*M[2][1]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(S2, M[1][1]);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(C1*M[2][0] - S1*M[2][2], C1*M[0][0] - S1*M[0][2]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleYZY(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(M[1][2], -M[1][0]);
		ComponentType S2 = glm::sqrt(M[0][1]*M[0][1] + M[2][1]*M[2][1]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(S2, M[1][1]);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(-S1*M[0][0] - C1*M[0][2], S1*M[2][0] + C1*M[2][2]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleZYZ(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(M[2][1], M[2][0]);
		ComponentType S2 = glm::sqrt(M[0][2]*M[0][2] + M[1][2]*M[1][2]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(S2, M[2][2]);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(C1*M[0][1] - S1*M[0][0], C1*M[1][1] - S1*M[1][0]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleZXZ(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(M[2][0], -M[2][1]);
		ComponentType S2 = glm::sqrt(M[0][2]*M[0][2] + M[1][2]*M[1][2]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(S2, M[2][2]);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(-C1*M[1][0] - S1*M[1][1], C1*M[0][0] + S1*M[0][1]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleXZY(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(M[1][2], M[1][1]);
		ComponentType C2 = glm::sqrt(M[0][0]*M[0][0] + M[2][0]*M[2][0]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(-M[1][0], C2);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(S1*M[0][1] - C1*M[0][2], C1*M[2][2] - S1*M[2][1]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleYZX(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(-M[0][2], M[0][0]);
		ComponentType C2 = glm::sqrt(M[1][1]*M[1][1] + M[2][1]*M[2][1]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(M[0][1], C2);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(S1*M[1][0] + C1*M[1][2], S1*M[2][0] + C1*M[2][2]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleZYX(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(M[0][1], M[0][0]);
		ComponentType C2 = glm::sqrt(M[1][2]*M[1][2] + M[2][2]*M[2][2]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(-M[0][2], C2);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(S1*M[2][0] - C1*M[2][1], C1*M[1][1] - S1*M[1][0]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}

	template <typename ComponentType>
	GLM_FUNC_QUALIFIER void extractEulerAngleZXY(mat<4, 4, ComponentType, defaultp> const & M,
												 ComponentType & t1,
												 ComponentType & t2,
												 ComponentType & t3)
	{
		ComponentType T1 = glm::atan2<ComponentType, defaultp>(-M[1][0], M[1][1]);
		ComponentType C2 = glm::sqrt(M[0][2]*M[0][2] + M[2][2]*M[2][2]);
		ComponentType T2 = glm::atan2<ComponentType, defaultp>(M[1][2], C2);
		ComponentType S1 = glm::sin(T1);
		ComponentType C1 = glm::cos(T1);
		ComponentType T3 = glm::atan2<ComponentType, defaultp>(C1*M[2][0] + S1*M[2][1], C1*M[0][0] + S1*M[0][1]);
		t1 = T1;
		t2 = T2;
		t3 = T3;
	}
}//namespace glm
