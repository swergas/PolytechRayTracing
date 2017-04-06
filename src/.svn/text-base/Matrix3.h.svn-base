#ifndef MATRIX_H
#define MATRIX_H

/**
 * \file Matrix3.h
 * \brief Matrix 3x3 creator
 * \author Quentin Grimaud, Michael Gygli, Valentin Michelet
 * \version 0.7
 * \date October 2011
 *
 * Program to generate and manipulate matrix 3x3 from Vector3 class.
 *
 */
#include "Vector3.h"

using namespace std;

class Matrix3 {
public:
	double _elements[3][3];

	class Out_Of_Bounds {};

	Matrix3(double value = 0.0);
	Matrix3(const Vector3& colomn1, const Vector3& column2, const Vector3& column3);
	Matrix3(const Matrix3& matrix);

	Vector3 operator[](unsigned index);
	Vector3 operator[](unsigned index) const;

	Vector3 line(unsigned indexLine) const;
	Vector3 column(unsigned indexColumn) const;

	double& operator()(unsigned line, unsigned column);
	double operator()(unsigned line, unsigned column) const;

	friend ostream& operator<<(ostream& os, const Matrix3 matrix);
	friend Matrix3 operator+(const Matrix3& matrix1, const Matrix3& matrix2);
	friend Matrix3 operator-(const Matrix3& matrix1, const Matrix3& matrix2);
	friend Matrix3 operator*(const Matrix3& matrix1, const Matrix3& matrix2);
	friend Vector3 operator*(const Matrix3& matrix, const Vector3& vector);

	friend Matrix3 transpose(const Matrix3& matrix);

	friend bool operator==(const Matrix3& matrix1, const Matrix3& matrix2);
	friend bool operator!=(const Matrix3& matrix1, const Matrix3& matrix2);

	Matrix3 operator=(Matrix3 matrix);
	Matrix3 operator+=(const Matrix3& matrix);
	Matrix3 operator-=(const Matrix3& matrix);
	Matrix3 operator*=(const Matrix3& matrix);

};

#endif
