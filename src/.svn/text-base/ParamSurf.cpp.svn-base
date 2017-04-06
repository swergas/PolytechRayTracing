/*
 * ParamSurf.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: Marion & Sandra
 */

#include "ParamSurf.h"

extern "C"{
	void dggev_(const char* JOBVL, const char* JOBVR, const int* N,
                       const double* A, const int* LDA, const double* B, const int* LDB,
                       double* ALPHAR, double* ALPHAI, double* BETA,
                       double* VL, const int* LDVL, double* VR, const int* LDVR,
                       double* WORK, const int* LWORK, int* INFO);
}

ParamSurf::ParamSurf(const Color &_color,mat M0, mat M1, mat M2, mat M3, string surface) : 
	 M0(M0), M1(M1), M2(M2), M3(M3) {
	this->color = _color;
	this->surface = surface;
	Material material(0.1, 0.4, 0.5, 20, 0.2); //FIXME Take into constructor
}

ParamSurf::~ParamSurf() {
}

/*
 *	Calculate the pencil of a parametric surface
 */
Set<mat> ParamSurf::make_pencil(const Ray& r) const {

	Set<mat> pencil = Set<mat> (2);

	Vector3 originRay = r[0];
	Vector3 directionRay = r[1];

	double x0 = originRay[0];
	double y0 = originRay[1];
	double z0 = originRay[2];

	double xd = directionRay[0];
	double yd = directionRay[1];
	double zd = directionRay[2];

	mat A = M0+x0*M1+y0*M2+z0*M3;
	mat B = (-xd)*M1+(-yd)*M2+(-zd)*M3;

	pencil.add(A);
	pencil.add(B);

	return pencil;
}

/*
 *	Calculate the reduction of a pencil (A,B)
 */
Set<mat> ParamSurf::make_reduction(mat A, mat B) const {

	Set<mat> reduction = Set<mat> (2);
	
	int r = rank(B);
	cout << "rB: " << r << endl;
	int m = B.rows();
	int n = B.cols();

	while (r < n) {
		//reduction on the colums of B
		mat BT = B.transpose();
		mat Q, R;
		//qr(BT, Q, R);

		bmat P;
		qr(BT, Q, R, P);
		cout << "Q: \n " << Q << endl;
		cout << "R: \n " << R << endl;
		cout << "P: \n " << P << endl;
		mat PT = to_mat(P.transpose());

/*
		mat U,V;
		vec s;
		svd(BT,U,s,V);

		cout << "U: \n " << U << endl;
		cout << "V: \n " << V << endl;
		mat UT = U.transpose();
		mat VT = V.transpose();

		cout << "s: \n " << s << endl;
		mat S = diag(s);
		vec v="0, 0, 0, 0, 0, 0";
		S.append_row(v);
		S.append_row(v);
		S.append_row(v);
		cout << " S: \n " <<  S << endl;
		cout << " SV: \n " <<  S*V << endl;
		cout << " S*UT: \n " <<  S*UT << endl;
		cout << " VT*S: \n " <<  VT*S << endl;
*/

		cout << "QR: \n " << Q*R << endl;
		cout << "BQ: \n " << B*Q << endl;
		mat A2 = PT*A*Q;
		cout << "PT*A*Q: \n " << PT*A*Q << endl;
		A2.del_cols(0,r-1);
		int rA2 = rank(A2,pow(10,-10));
		//cout << "A2: " << A2 << endl;
		//reduction on the rows of A2
		mat Q2, R2;
		qr(A2, Q2, R2);
		cout << "Q2: \n " << Q2 << endl;
		cout << "R2: \n " << R2 << endl;
		cout << "rR2: " << rank(R2,pow(10,-10)) << endl;
		cout << "rA2: " << rA2 << endl;
		cout << "A2: \n " << A2 << endl;

		mat E2 = Q2.transpose();
		cout << "E2*A2: \n " << E2*A2 << endl;
		mat EBQ = E2*PT*B*Q;
		mat EAQ = E2*PT*A*Q;
		cout << "EBQ:\n " << EBQ << endl;
		cout << "EAQ:\n  " << EAQ << endl;
		cout << "EBQ(m,n) " << EBQ.rows() <<","<<EBQ.cols() << endl;

		mat B5 = EBQ;
		B5.del_cols(r,n-1);
		if (rA2 > 0) 
		B5.del_rows(0,rA2-1);
		cout << "B5: \n " << B5 << endl;

		mat A5 = EAQ;
		A5.del_cols(r,n-1);
		if (rA2 > 0) 
		A5.del_rows(0,rA2-1);
		cout << "A5:\n  " << A5 << endl;
		cout << "rB5:\n  " << rank(B5) << endl;

		A = A5;
		B = B5;
		r = rank(B5);
		n = B5.cols();
		m = B5.rows();
	}

	if ( r == n ) {
		cout << "end" << endl;
		reduction.add(A);
		reduction.add(B);
		return reduction;
	}else{
		cout << "B.rows() != B.cols() " << endl;
		return make_reduction(A.transpose(), B.transpose());
	}
}

/*
 *	Calculate the intersections of a ray with a parametric surface
 */
Set<double> ParamSurf::intersect(const Ray& r) const {
	
	Set<mat> pencil = make_pencil(r);

	mat A = pencil.get(0);
	mat B = pencil.get(1);

	if ( A.cols() != A.rows() ) {
		Set<mat> reduc = make_reduction(A,B);
		A = reduc.get(0);
		B = reduc.get(1);
		if(A.size() == 0) {
			return Set<double>(0);
		}
	}
	//cout << "A = " << A << endl;
	//cout << "B = " << B << endl;

	char jobvl = 'N', jobvr = 'V';
	int n, lda, ldb, ldvl, ldvr, lwork, info;
	n=lda=A.rows();
	ldb = B.rows();
	ldvl = 1;
	ldvr = n;
	lwork = std::max(1,  n*n+64); // This may be choosen better! ???

	vec work(lwork);
	vec alphar(n), alphai(n), beta(n);
	mat vl(1,n), vr(n, n);
	dggev_(&jobvl, &jobvr, &n, A._data(), &lda,
        B._data(), &ldb, alphar._data(), alphai._data(), beta._data(), vl._data(),
        &ldvl, vr._data(), &ldvr, work._data(), &lwork, &info);

	//cout << "alphar = " << alphar << endl;
	//cout << "alphai = " << alphai << endl;
	//cout << "beta = " << beta << endl;

	double vp;
	Set<double> gev = Set<double>(n);
	for(int i=0; i < n; i++){
		if (beta(i)!=0 && beta(i) > abs(0.0001)) {
			vp = alphar(i)/beta(i);
			if (vp > 0) {
				gev.add(vp);
			}
		}
	}

	//The generalized eigenvalues ​​are sorted in ascending order
	double temp;
	for (int j=gev.size(); j>0; j--) {
		for (int i=0; i < j-1; i++) {
			if (gev[i] > gev[i+1]) {
				temp=gev[i];
				gev[i]=gev[i+1];
				gev[i+1]=temp;
			}
	  	}
 	}

	return gev;
}

Vector3 ParamSurf::normalButterfly(double s, double t) const {

	double s2 = pow(s,2);
	double t2 = pow(t,2);

	double x = (-(2/s)-((1-t2)/(s*t2)))/s2;
	double y = (-(2/s)-((s2-t2+1)/(s*t2)))/s2;
	double z = ((2/t)-((s2-t2+1)/(s2*t)))*(-(2/s)-((1-t2)/(s*t2)))+(((1-t2)*(-(2/s)-(s2-t2+1)/(s*t2)))/s2*t);

	Vector3 normal(x, y, z);
	
	return normal;
}

Vector3 ParamSurf::normalSteiner(double s, double t) const {

	double s2 = pow(s,2);
	double t2 = pow(t,2);

	double x = 1/(s2*t2);
	double y = ((2/t)-((s2+t2+1)/(s2*t)))/t2;
	double z = ((2/s)-((s2+t2+1)/(s*t2)))/s2;

	Vector3 normal(x, y, z);
	
	return normal;

}

Vector3 ParamSurf::normal(const Vector3& pt_intersection) const {

	double x = pt_intersection[0];
	double y = pt_intersection[1];
	double z = pt_intersection[2];

	//kernel
	mat M = M0+x*M1+y*M2+z*M3;
	mat Q, R;
	qr(M, Q, R);
	cout << "Q " << Q <<endl;
	cout << "R " << R <<endl;
	mat QT = Q.transpose();
	cout << "QT " << QT <<endl;
	QT.del_rows(0,rank(M)-1);
	cout <<"rgM " <<rank(M) <<endl;
	cout << "QTbis " << QT <<endl;
	cout << "u2 "<< QT(0,0) <<endl;
	double s = QT(0,1)/QT(0,0);
	double t = QT(0,2)/QT(0,0);
	cout << "s" << s <<endl;
	cout << "t" << t <<endl;

	if(surface.compare("butterfly")==0) {
		Vector3 n = normalButterfly(s, t);
	}else if(surface.compare("steiner")==0) {
		Vector3 n = normalSteiner(s, t);
	}

	return Vector3(1, 0, 0);
}

int main() {

	/*	
	//surface avec M carrée
	mat M0 = "-1,0,0,0,0,-2; 0,-2,0,0,0,0; 0,0,0,0,-2,0; 0,0,0,0,0,0; 0,0,0,0,0,0; -4,0,0,0,-8,-8";
	mat M1 = "-1,0,1,0,0,-1; 0,0,0,0,0,0; 0,0,0,0,0,0; 0,0,0,0,0,0; 0,0,0,0,0,0; -4,0,0,0,0,-4";
	mat M2 = "0,0,0,0,0,0; -1,0,1,0,0,-1; 0,0,0,0,0,0; 0,0,0,0,0,-2; 0,0,0,-2,0,0; 0,4,0,0,0,0";
	mat M3 = "0,0,0,0,0,0; 0,0,0,0,0,0; -1,0,1,0,0,-1; 0,0,0,2,0,0; 2,0,0,0,0,0; 0,0,0,0,6,0";
	ParamSurf paramSurf1 = ParamSurf(Color(0,1,0),M0,M1,M2,M3);
	Vector3 origin= Vector3(0,0,0);
	Vector3 direction= Vector3(2,1,2);
	Set<double> gev =paramSurf1.intersect(Ray(origin,direction));
	*/

/*	//Sphère
	mat M0 = "0,0,1,0; 0,1,0,0; 1,0,0,0";
	mat M1 = "0,0,-1,0; 0,1,0,0; 1,0,0,0";
	mat M2 = "-1,0,0,0; 0,0,0,-1; 0,0,-1,0";
	mat M3 = "0,-1,0,0; 0,0,-1,0; 0,0,0,1";
*/
/*
	//Butterfly surface
	mat M0 = "0,0,0,1,0,0,0,0,0; 1,0,0,0,0,0,0,0,0; 0,0,1,0,0,0,0,0,0; 0,0,0,0,0,1,0,0,0; 0,0,0,0,1,0,0,0,0; 0,1,0,0,0,0,0,0,0";
	mat M1 = "0,0,0,0,-1,0,0,0,1; 0,0,0,0,0,0,0,0,0; -1,0,0,0,0,0,0,-1,0; 0,0,0,0,0,0,0,0,0; 0,0,0,0,0,-1,0,0,0; 0,0,0,0,0,0,0,0,-1";
	mat M2 = "0,0,0,0,1,0,0,0,-1; 0,0,0,0,0,0,0,0,0; 1,0,0,0,0,0,1,1,0; 0,0,0,0,1,0,0,0,-1; 0,1,0,0,0,1,0,0,0; 0,0,0,0,0,0,0,0,1";
	mat M3 = "0,0,0,0,0,0,-1,0,0; 0,-1,0,-1,0,0,0,0,0; 0,0,0,0,0,0,0,0,0; 0,0,0,0,0,0,0,0,0; 0,0,-1,0,0,0,0,0,0; 0,0,0,0,0,0,1,0,0";
*/


	//Steiner surface
	mat M0 = "1,0,0,0,0,0,0,0,0; 0,0,1,0,0,0,0,0,0; 0,0,0,1,0,0,0,0,0; 0,0,0,0,0,0,0,0,0; 0,1,0,0,0,0,0,0,0; 0,1,0,0,0,0,0,0,0";
	mat M1 = "0,0,0,0,0,0,0,0,0; 0,0,0,0,-1,0,0,0,0; 0,0,0,0,0,0,0,0,-1; 0,-1,0,0,0,0,0,0,0; 0,0,0,0,0,0,0,0,0; 0,0,0,0,0,0,0,0,0";
	mat M2 = "0,0,0,0,0,0,0,0,1; -1,1,0,0,0,0,0,-1,0; 0,0,0,0,0,0,0,0,0; 0,0,0,-1,1,-1,0,0,0; 0,0,-1,0,0,0,-1,0,1; 0,0,0,0,0,0,0,0,1";
	mat M3 = "0,0,0,0,1,0,0,0,0; 0,0,0,0,0,0,0,0,0; 0,0,0,0,0,0,0,1,0; 0,0,0,0,0,0,1,0,0; 0,0,0,0,1,0,0,0,0; 0,0,0,0,0,1,0,0,0";



	ParamSurf paramSurf2 = ParamSurf(Color(0,1,0),M0,M1,M2,M3,"steiner");
	Vector3 origin= Vector3(0,0.5,0.5);
	Vector3 direction= Vector3(1,1,1);
/*	Set<mat> pencil = paramSurf2.make_pencil(Ray(origin,direction));
	cout << "pencil[0]\n" << pencil[0] <<endl;
	cout << "pencil[1]\n" << pencil[1] <<endl;
	Set<mat> reduction = paramSurf2.make_reduction(pencil[0],pencil[1]);
	cout << "reduction[0]\n" << reduction[0] <<endl;
	cout << "reduction[1]\n" << reduction[1] <<endl;
*/
	Set<double> gev = paramSurf2.intersect(Ray(origin,direction));


	cout << "gen vp " << endl;
	for(int i=0;i<gev.size();i++){
		cout << gev.get(i) << endl;
	}

	return 0;
}
