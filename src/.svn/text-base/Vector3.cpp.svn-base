#include "Vector3.h"
#include <cmath> // sqrt ()

Vector3::Vector3(double x, double y, double z) {
	_coords[0] = x;
	_coords[1] = y;
	_coords[2] = z;
}

Vector3::Vector3(const Vector3 &v1) {
	*this = v1;
}

Vector3::~Vector3() {
}

double Vector3::getX() const {
	return _coords[0];
}

double Vector3::getY() const {
	return _coords[1];
}

double Vector3::getZ() const {
	return _coords[2];
}

void Vector3::setX(double x) {
	_coords[0] = x;
}

void Vector3::setY(double y) {
	_coords[1] = y;
}

void Vector3::setZ(double z) {
	_coords[2] = z;
}

double Vector3::operator[](int i) const {
	return _coords[i];
}

double& Vector3::operator[](const int &i) {
	return _coords[i];
}

bool operator==(const Vector3 &v1, const Vector3 &v2) {
	return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2];
}

bool operator!=(const Vector3 &v1, const Vector3 &v2) {
	return !(v1 == v2);
}

const Vector3& Vector3::operator+() const {
	return *this;
}

Vector3 Vector3::operator-() const {
	return Vector3(-_coords[0], -_coords[1], -_coords[2]);
}

Vector3& Vector3::operator=(const Vector3 &v) {
	_coords[0] = v[0];
	_coords[1] = v[1];
	_coords[2] = v[2];
	return *this;
}

Vector3 operator*(const Vector3& v, const double k) {
	return Vector3(v[0] * k, v[1] * k, v[2] * k);
}

Vector3 operator*(const double k, const Vector3& v) {
	return Vector3(v[0] * k, v[1] * k, v[2] * k);
}

Vector3 operator/(const Vector3& v, const double k) {
	return Vector3(v[0] / k, v[1] / k, v[2] / k);
}

Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

Vector3& Vector3::operator*=(const double k) {
	return *this = (*this * k);
}

Vector3& Vector3::operator/=(const double k) {
	return *this = (*this / k);
}

Vector3& Vector3::operator+=(const Vector3& v) {
	return *this = (*this + v);
}

Vector3& Vector3::operator-=(const Vector3& v) {
	return *this = (*this - v);
}

double dot_product(const Vector3& v1, const Vector3& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

Vector3 cross_product(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1[1] * v2[2] - v1[2] * v2[1],
			v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0]);
}

double triple_product(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
	return dot_product(cross_product(v1, v2), v3);
}

double Vector3::norm() const {
	return sqrt(
			_coords[0] * _coords[0] + _coords[1] * _coords[1] + _coords[2]
					* _coords[2]);
}

double Vector3::squared_norm() const {
	return (_coords[0] * _coords[0] + _coords[1] * _coords[1] + _coords[2]
			* _coords[2]);
}

Vector3 &Vector3::normalize() {
	return (*this = *this / (*this).norm());
}

Vector3 Vector3::normalized() const {
	return *this / (*this).norm();
}

double Vector3::min_coord() const {
	double tmp = _coords[0];
	if (tmp > _coords[1])
		tmp = _coords[1];
	if (tmp > _coords[2])
		tmp = _coords[2];
	return tmp;
}

double Vector3::max_coord() const {
	double tmp = _coords[0];
	if (tmp < _coords[1])
		tmp = _coords[1];
	if (tmp < _coords[2])
		tmp = _coords[2];
	return tmp;
}

double Vector3::min_abs_coord() const {
	double tmp = fabs(_coords[0]);
	if (tmp > fabs(_coords[1]))
		tmp = fabs(_coords[1]);
	if (tmp > fabs(_coords[2]))
		tmp = fabs(_coords[2]);
	return tmp;
}

double Vector3::max_abs_coord() const {
	double tmp = fabs(_coords[0]);
	if (tmp < fabs(_coords[1]))
		tmp = fabs(_coords[1]);
	if (tmp < fabs(_coords[2]))
		tmp = fabs(_coords[2]);
	return tmp;
}

int Vector3::index_min_coord() const {
	int index = 0;
	double tmp = _coords[0];
	if (tmp > _coords[1]) {
		tmp = _coords[1];
		index = 1;
	}
	if (tmp > _coords[2])
		index = 2;
	return index;
}

int Vector3::index_max_coord() const {
	int index = 0;
	double tmp = _coords[0];
	if (tmp < _coords[1]) {
		tmp = _coords[1];
		index = 1;
	}
	if (tmp < _coords[2])
		index = 2;
	return index;
}

int Vector3::index_min_abs_coord() const {
	int index = 0;
	double tmp = fabs(_coords[0]);
	if (tmp > fabs(_coords[1])) {
		tmp = fabs(_coords[1]);
		index = 1;
	}
	if (tmp > fabs(_coords[2]))
		index = 2;
	return index;
}

int Vector3::index_max_abs_coord() const {
	int index = 0;
	double tmp = fabs(_coords[0]);
	if (tmp < fabs(_coords[1])) {
		tmp = fabs(_coords[1]);
		index = 1;
	}
	if (tmp < fabs(_coords[2]))
		index = 2;
	return index;
}

Vector3 minVect(const Vector3& v1, const Vector3& v2) {
	Vector3 v(v1);
	if (v2[0] < v1[0])
		v.setX(v2[0]);
	if (v2[1] < v1[1])
		v.setY(v2[1]);
	if (v2[2] < v1[2])
		v.setZ(v2[2]);
	return v;
}

Vector3 maxVect(const Vector3& v1, const Vector3& v2) {
	Vector3 v(v1);
	if (v2[0] > v1[0])
		v.setX(v2[0]);
	if (v2[1] > v1[1])
		v.setY(v2[1]);
	if (v2[2] > v1[2])
		v.setZ(v2[2]);
	return v;
}

std::ostream& operator<<(std::ostream &os, const Vector3 &v) {
	return os << "(" << v[0] << "; " << v[1] << "; " << v[2] << ")";
}

std::istream& operator>>(std::istream &is, Vector3 &v) {
	return is >> v._coords[0] >> v._coords[1] >> v._coords[2];
}
