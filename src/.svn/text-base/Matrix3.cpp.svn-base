#include "Matrix3.h"
#include <iostream>

using namespace std;

Matrix3::Matrix3(double value) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			_elements[i][j] = value;
		}
	}
}

Matrix3::Matrix3(const Vector3& column1, const Vector3& column2, const Vector3& column3) {
	for (int i = 0; i < 3; i++) {
		_elements[i][0] = column1[i];
		_elements[i][1] = column2[i];
		_elements[i][2] = column3[i];
	}
}

Matrix3::Matrix3(const Matrix3& matrix) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			_elements[i][j] = matrix[i][j];
		}
	}
}

Vector3 Matrix3::operator[](unsigned index) {
	if (index < 3) {
		return Vector3(_elements[index][0], _elements[index][1], _elements[index][2]);
	}
	throw Out_Of_Bounds();
}

Vector3 Matrix3::operator[](unsigned index) const {
	if (index < 3) {
		return Vector3(_elements[index][0], _elements[index][1], _elements[index][2]);
	}
	throw Out_Of_Bounds();
}

Vector3 Matrix3::line(unsigned indexLigne) const {
	if (indexLigne < 3) {
		return Vector3(_elements[indexLigne][0], _elements[indexLigne][1], _elements[indexLigne][2]);
	}
	throw Out_Of_Bounds();
}

Vector3 Matrix3::column(unsigned indexColumn) const {
	if (indexColumn < 3) {
		Vector3 vcolumn;
		for (unsigned k = 0; k < 3; k++) {
			vcolumn[k] = line(k)[indexColumn];
		}
		return vcolumn;
	}
	throw Out_Of_Bounds();
}

double& Matrix3::operator()(unsigned line, unsigned column) {
	return _elements[line][column];
}

double Matrix3::operator()(unsigned line, unsigned column) const {
	return _elements[line][column];
}

ostream& operator<<(ostream &os, const Matrix3 matrix) {
	os << "[" << endl;
	for (int k = 0; k < 3; k++) {
		os << "  " << matrix[k] << endl;
	}
	return os << "]";
}

Matrix3 operator+(const Matrix3 &matrix1, const Matrix3 &matrix2) {
	Matrix3 matrix_somme;
	for (int k = 0; k < 3; k++) {
		matrix_somme[k] = matrix1[k] + matrix2[k];
	}
	return matrix_somme;
}

Matrix3 operator-(const Matrix3 &matrix1, const Matrix3 &matrix2) {
	Matrix3 matrix_somme;
	for (int k = 0; k < 3; k++) {
		matrix_somme[k] = matrix1[k] - matrix2[k];
	}
	return matrix_somme;
}

Matrix3 operator*(const Matrix3 &matrix1, const Matrix3 &matrix2) {
	Matrix3 matrix_produit;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_produit(i, j) = (dot_product(matrix1.line(i),  matrix2.column(j)));
		}
	}
	return matrix_produit;
}

Vector3 operator*(const Matrix3& matrix, const Vector3& vector) {
	Vector3 vector_produit;
	for (int i = 0; i < 3; i++) {
		vector_produit[i] = dot_product(matrix.line(i), vector);
	}
	return vector_produit;
}

Matrix3 transpose(const Matrix3& matrix) {
	Matrix3 res;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			res(i, j) = matrix(j, i);
		}
	}
	return res;
}

bool operator==(const Matrix3 &matrix1, const Matrix3 &matrix2) {
	return matrix1._elements == matrix2._elements;
}

bool operator!=(const Matrix3 &matrix1, const Matrix3 &matrix2) {
	return !(matrix1 == matrix2);
}

Matrix3 Matrix3::operator=(Matrix3 matrix) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			_elements[i][j] = matrix(i, j);
		}
	}
	return *this;
}

Matrix3 Matrix3::operator+=(const Matrix3 &matrix) {
	return *this = (*this + matrix);
}

Matrix3 Matrix3::operator-=(const Matrix3 &matrix) {
	return *this = (*this - matrix);
}

Matrix3 Matrix3::operator*=(const Matrix3 &matrix) {
	return *this = (*this * matrix);
}
