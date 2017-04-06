
#include <stdio.h>
#include <atlas_enum.h>
//These lines are needed for use of cout and endl

using namespace std;

//extern "C" void zggev_(char *jobvl, char *jobvr, int *n, complex *a,int *lda, complex *b, int *ldb, complex *alpha, complex *beta, complex *vl,int *ldvl, complex *vr, int *ldvr,complex *work, int *lwork, double *rwork, int *info);


extern "C"
{
#include <clapack.h>
	//#include "/home/user/Bureau/lancer_rayons/CLAPACK-3.2.1/INCLUDE/clapack.h"
//#include"/home/user/Bureau/lancer_rayons/CLAPACK-3.2.1/INCLUDE/f2c.h"
//#include"/home/user/Bureau/lancer_rayons/CLAPACK-3.2.1/INCLUDE/cblas.h" 
}

int main()
{

 doublecomplex cA[4];
 doublecomplex cB[4];
cA={3, 3 ,4 ,7};
cB={1 ,2 ,8 ,9};

  //cA="-21.10-22.50 53.50-50.50 -34.50+127.50i 7.50+0.50i;-0.46-7.78i -3.50-37.50i -15.50+58.50i -10.50-1.50i;4.30-5.50i 39.70-17.10i -68.50+12.50i -7.50-3.50i;5.50+4.40i 14.40+43.30i -32.50-46.00i -19.00-32.50i";

 //cB="1.00-5.00i 1.60+1.20i -3.00+0.00i 0.00-1.00i;0.80-0.60i 3.00-5.00i -4.00+3.00i -2.40-3.20i;1.00+0.00i  2.40+1.80i -4.00-5.00i 0.00-3.00i;0.00+1.00i -1.80+2.40i  0.00-4.00i  4.00-5.00i";

  cout<< "cA = " << cA<<endl;
  cout<< "cB = " << cB<<endl;

  double lambda[2];
 // double evecs[];
//  eig(cA,lambda,evecs);
  char jobvl = 'N', jobvr = 'V';
  int n, lda, ldb, ldvl, ldvr, lwork, info;
  n=lda=2;
  double evecs[n];
  ldb = 2;
  ldvl = 1;
  ldvr = n;
  lwork = std::max(1,  n*n+64); // This may be choosen better!

  int work=lwork;
  int rwork=8*n; // This may be choosen better
  int alpha=n;
  int beta=n;
  double  vl[1];
  double vr[n*n];
  clapack_zggev(&jobvl, &jobvr, &n, cA, &lda,cB, &ldb, alpha,  beta, vl,&ldvl, vr, &ldvr, work, &lwork,rwork, &info);
  lambda=elem_div(alpha,beta);
  evecs=vr;
  cout<<endl;
  cout<< "eig(cA,cB)= \n";
  cout << "lambda = "<<lambda<<endl;
  cout << "evecs = "<<evecs<<endl;

  //Exit program:
  return 0;

}

