#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>

class vector3d
{
public:
	vector3d() {};
	vector3d(float x, float y, float z) { v[0] = x; v[1] = y; v[2] = z; }

	inline float x() const { return v[0]; }
	inline float y() const { return v[1]; }
	inline float z() const { return v[2]; }
	inline float r() const { return v[0]; }
	inline float g() const { return v[1]; }
	inline float b() const { return v[2]; }

	inline const vector3d& operator+() const { return *this; };
	inline vector3d operator-() const { return vector3d(-v[0], -v[1], -v[2]); };
	inline float operator[](int i) const { return v[i]; };
	inline float& operator[](int i) { return v[i]; };

	inline vector3d& operator+=(const vector3d &v2);
	inline vector3d& operator-=(const vector3d &v2);
	inline vector3d& operator*=(const vector3d &v2);
	inline vector3d& operator/=(const vector3d &v2);
	//inline vector3d& operator*=(const float t);
	//inline vector3d& operator/=(const float t);

	inline float length() const
	{
		return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	}
	
	inline float squared_length() const
	{
		return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	}

	inline void make_unit_vector();

	float v[3];
};

inline std::istream& operator>>(std::istream &in, vector3d& t)
{
	in >> t.v[1] >> t.v[1] >> t.v[2];
	return in;
}

inline std::ostream& operator<<(std::ostream &out, const vector3d &t)
{
	out << t.v[0] << " " << t.v[1] << " " << t.v[2];
	return out;
	
}

inline void vector3d::make_unit_vector()
{
	float k = 1.0f / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

inline vector3d operator+(const vector3d &v1, const vector3d &v2)
{
	return vector3d(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2]);
}

inline vector3d operator-(const vector3d &v1, const vector3d &v2)
{
	return vector3d(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]);
}

inline vector3d operator*(const vector3d &v1, const vector3d &v2)
{
	return vector3d(v1.v[0] * v2.v[0], v1.v[1] * v2.v[1], v1.v[2] * v2.v[2]);
}

inline vector3d operator/(const vector3d &v1, const vector3d &v2)
{
	return vector3d(v1.v[0] / v2.v[0], v1.v[1] / v2.v[1], v1.v[2] / v2.v[2]);
}

inline vector3d operator*(const float t, const vector3d &v1)
{
	return vector3d(t * v1.v[0], t * v1.v[1], t * v1.v[2]);
}

inline vector3d operator*(const vector3d &v1, const float t )
{
	return vector3d(t * v1.v[0], t * v1.v[1], t * v1.v[2]);
}

inline vector3d operator/(const vector3d &v1, const float t)
{
	return vector3d(v1.v[0] / t, v1.v[1] / t, v1.v[2] / t);
}

inline vector3d& vector3d::operator+=(const vector3d &v2)
{
	v[0] += v2.v[0];
	v[1] += v2.v[1];
	v[2] += v2.v[2];
	return *this;
}

inline vector3d& vector3d::operator*=(const vector3d &v2)
{
	v[0] *= v2.v[0];
	v[1] *= v2.v[1];
	v[2] *= v2.v[2];
	return *this;
}

inline vector3d& vector3d::operator/=(const vector3d &v2)
{
	v[0] /= v2.v[0];
	v[1] /= v2.v[1];
	v[2] /= v2.v[2];
	return *this;
}

inline vector3d& vector3d::operator-=(const vector3d &v2)
{
	v[0] -= v2.v[0];
	v[1] -= v2.v[1];
	v[2] -= v2.v[2];
	return *this;
}


inline float dot(const vector3d &v1, const vector3d &v2)
{
	return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2];
}

inline vector3d cross(const vector3d &v1, const vector3d &v2)
{
	return vector3d(v1.v[1] * v2.v[2] - v2.v[1] * v1.v[2], 
				  -(v1.v[0] * v2.v[2] - v1.v[2] * v2.v[0]), 
					v1.v[0] * v2.v[1] - v2.v[0] * v2.v[1]);
}

inline vector3d unit_vector(vector3d v)
{
	return v / v.length();
}

