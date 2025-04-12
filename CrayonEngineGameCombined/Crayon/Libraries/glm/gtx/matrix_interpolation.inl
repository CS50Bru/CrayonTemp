/// @ref gtx_matrix_interpolation

#include "../gtc/constants.hpp"

namespace glm
{
	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER void axisAngle(mat<4, 4, ComponentType, Q> const& m, vec<3, ComponentType, Q> & axis, ComponentType& angle)
	{
		ComponentType epsilon = static_cast<ComponentType>(0.01);
		ComponentType epsilon2 = static_cast<ComponentType>(0.1);

		if((abs(m[1][0] - m[0][1]) < epsilon) && (abs(m[2][0] - m[0][2]) < epsilon) && (abs(m[2][1] - m[1][2]) < epsilon))
		{
			if ((abs(m[1][0] + m[0][1]) < epsilon2) && (abs(m[2][0] + m[0][2]) < epsilon2) && (abs(m[2][1] + m[1][2]) < epsilon2) && (abs(m[0][0] + m[1][1] + m[2][2] - static_cast<ComponentType>(3.0)) < epsilon2))
			{
				angle = static_cast<ComponentType>(0.0);
				axis.x = static_cast<ComponentType>(1.0);
				axis.y = static_cast<ComponentType>(0.0);
				axis.z = static_cast<ComponentType>(0.0);
				return;
			}
			angle = static_cast<ComponentType>(3.1415926535897932384626433832795);
			ComponentType xx = (m[0][0] + static_cast<ComponentType>(1.0)) * static_cast<ComponentType>(0.5);
			ComponentType yy = (m[1][1] + static_cast<ComponentType>(1.0)) * static_cast<ComponentType>(0.5);
			ComponentType zz = (m[2][2] + static_cast<ComponentType>(1.0)) * static_cast<ComponentType>(0.5);
			ComponentType xy = (m[1][0] + m[0][1]) * static_cast<ComponentType>(0.25);
			ComponentType xz = (m[2][0] + m[0][2]) * static_cast<ComponentType>(0.25);
			ComponentType yz = (m[2][1] + m[1][2]) * static_cast<ComponentType>(0.25);
			if((xx > yy) && (xx > zz))
			{
				if(xx < epsilon)
				{
					axis.x = static_cast<ComponentType>(0.0);
					axis.y = static_cast<ComponentType>(0.7071);
					axis.z = static_cast<ComponentType>(0.7071);
				}
				else
				{
					axis.x = sqrt(xx);
					axis.y = xy / axis.x;
					axis.z = xz / axis.x;
				}
			}
			else if (yy > zz)
			{
				if(yy < epsilon)
				{
					axis.x = static_cast<ComponentType>(0.7071);
					axis.y = static_cast<ComponentType>(0.0);
					axis.z = static_cast<ComponentType>(0.7071);
				}
				else
				{
					axis.y = sqrt(yy);
					axis.x = xy / axis.y;
					axis.z = yz / axis.y;
				}
			}
			else
			{
				if (zz < epsilon)
				{
					axis.x = static_cast<ComponentType>(0.7071);
					axis.y = static_cast<ComponentType>(0.7071);
					axis.z = static_cast<ComponentType>(0.0);
				}
				else
				{
					axis.z = sqrt(zz);
					axis.x = xz / axis.z;
					axis.y = yz / axis.z;
				}
			}
			return;
		}
		ComponentType s = sqrt((m[2][1] - m[1][2]) * (m[2][1] - m[1][2]) + (m[2][0] - m[0][2]) * (m[2][0] - m[0][2]) + (m[1][0] - m[0][1]) * (m[1][0] - m[0][1]));
		if (glm::abs(s) < ComponentType(0.001))
			s = static_cast<ComponentType>(1);
		ComponentType const angleCos = (m[0][0] + m[1][1] + m[2][2] - static_cast<ComponentType>(1)) * static_cast<ComponentType>(0.5);
		if(angleCos - static_cast<ComponentType>(1) < epsilon)
			angle = pi<ComponentType>() * static_cast<ComponentType>(0.25);
		else
			angle = acos(angleCos);
		axis.x = (m[1][2] - m[2][1]) / s;
		axis.y = (m[2][0] - m[0][2]) / s;
		axis.z = (m[0][1] - m[1][0]) / s;
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> axisAngleMatrix(vec<3, ComponentType, Q> const& axis, ComponentType const angle)
	{
		ComponentType c = cos(angle);
		ComponentType s = sin(angle);
		ComponentType t = static_cast<ComponentType>(1) - c;
		vec<3, ComponentType, Q> n = normalize(axis);

		return mat<4, 4, ComponentType, Q>(
			t * n.x * n.x + c,          t * n.x * n.y + n.z * s,    t * n.x * n.z - n.y * s,    static_cast<ComponentType>(0.0),
			t * n.x * n.y - n.z * s,    t * n.y * n.y + c,          t * n.y * n.z + n.x * s,    static_cast<ComponentType>(0.0),
			t * n.x * n.z + n.y * s,    t * n.y * n.z - n.x * s,    t * n.z * n.z + c,          static_cast<ComponentType>(0.0),
			static_cast<ComponentType>(0.0),        static_cast<ComponentType>(0.0),        static_cast<ComponentType>(0.0),        static_cast<ComponentType>(1.0));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> extractMatrixRotation(mat<4, 4, ComponentType, Q> const& m)
	{
		return mat<4, 4, ComponentType, Q>(
			m[0][0], m[0][1], m[0][2], static_cast<ComponentType>(0.0),
			m[1][0], m[1][1], m[1][2], static_cast<ComponentType>(0.0),
			m[2][0], m[2][1], m[2][2], static_cast<ComponentType>(0.0),
			static_cast<ComponentType>(0.0), static_cast<ComponentType>(0.0), static_cast<ComponentType>(0.0), static_cast<ComponentType>(1.0));
	}

	template<typename ComponentType, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, ComponentType, Q> interpolate(mat<4, 4, ComponentType, Q> const& m1, mat<4, 4, ComponentType, Q> const& m2, ComponentType const delta)
	{
		mat<4, 4, ComponentType, Q> m1rot = extractMatrixRotation(m1);
		mat<4, 4, ComponentType, Q> dltRotation = m2 * transpose(m1rot);
		vec<3, ComponentType, Q> dltAxis;
		ComponentType dltAngle;
		axisAngle(dltRotation, dltAxis, dltAngle);
		mat<4, 4, ComponentType, Q> out = axisAngleMatrix(dltAxis, dltAngle * delta) * m1rot;
		out[3][0] = m1[3][0] + delta * (m2[3][0] - m1[3][0]);
		out[3][1] = m1[3][1] + delta * (m2[3][1] - m1[3][1]);
		out[3][2] = m1[3][2] + delta * (m2[3][2] - m1[3][2]);
		return out;
	}
}//namespace glm
