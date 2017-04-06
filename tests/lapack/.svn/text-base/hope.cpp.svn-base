#include <cstdio>
#include <iostream>
#include <cmath>
#include <complex>
#include <cstdlib>

#include <itpp/itbase.h>

using namespace itpp;
using namespace std;

extern "C"{
void zggev_(char *jobvl, char *jobvr, int *n, complex<double> *a, int *lda, complex<double> *b, int *ldb, complex<double> *alpha,complex<double> *beta, complex<double> *vl, int *ldvl, complex<double> *vr, int *ldvr,complex<double> *work, int *lwork, double *rwork, int *info);
}

int main()
{
  cmat cA,cB;
  cA="-21.10-22.50i 53.50-50.50i -34.50+127.50i 7.50+0.50i;-0.46-7.78i -3.50-37.50i -15.50+58.50i -10.50-1.50i;4.30-5.50i 39.70-17.10i -68.50+12.50i -7.50-3.50i;5.50+4.40i 14.40+43.30i -32.50-46.00i -19.00-32.50i";

 cB="1.00-5.00i 1.60+1.20i -3.00+0.00i 0.00-1.00i;0.80-0.60i 3.00-5.00i -4.00+3.00i -2.40-3.20i; 1.00+0.00i  2.40+1.80i -4.00-5.00i 0.00-3.00i;0.00+1.00i -1.80+2.40i  0.00-4.00i  4.00-5.00i";

  cout<< "cA = " << cA<<endl;
  cout<< "cB = " << cB<<endl;

  cvec lambda;
  cmat evecs;
//  eig(cA,lambda,evecs);
  char jobvl = 'N', jobvr = 'V';
  int n, lda, ldb, ldvl, ldvr, lwork, info;
  n=lda=cA.rows();
  ldb = cB.rows();
  ldvl = 1;
  ldvr = n;
  lwork = std::max(1,  n*n+64); // This may be choosen better!

  cvec work(lwork);
  vec rwork(8*n); // This may be choosen better
  cvec alpha(n), beta(n);
  cmat vl(1,1), vr(n, n);
  zggev_(&jobvl, &jobvr, &n, cA._data(), &lda,
       cB._data(), &ldb, alpha._data(),  beta._data(), vl._data(),
       &ldvl, vr._data(), &ldvr, work._data(), &lwork,
       rwork._data(), &info);
  lambda=elem_div(alpha,beta);
  evecs=vr;
  cout<<endl;
  cout<< "eig(cA,cB)= \n";
  cout << "lambda = "<<lambda<<endl;
  cout << "evecs = "<<evecs<<endl;
/*


#include <itpp/base/mat.h>

using namespace std;
using namespace itpp;

typedef complex<double> CPX;

extern "C" void zggev_(char *jobvl, char *jobvr, int *n, CPX *a,
            int *lda, CPX *b, int *ldb, CPX *alpha,
            CPX *beta, CPX *vl,
            int *ldvl, CPX *vr, int *ldvr,
            CPX *work, int *lwork, double *rwork, int *info);

int main()
{

 CPX I(0.,1.);

 CPX a[] = {-21.10-22.50*I, 53.50-50.50*I, -34.50+127.50*I, 7.50+0.50*I, -0.46-7.78*I, -3.50-37.50*I, -15.50+58.50*I, -10.50-1.50*I, 4.30-5.50*I, 39.70-17.10*I, -68.50+12.50*I, -7.50-3.50*I, 5.50+4.40*I, 14.40+43.30*I, -32.50-46.00*I, -19.00-32.50*I};
 CPX b[] = {1.00-5.00*I, 1.60+1.20*I, -3.00+0.00*I, 0.00-1.00*I,0.80-0.60*I, 3.00-5.00*I, -4.00+3.00*I, -2.40-3.20*I,1.00+0.00*I,  2.40+1.80*I, -4.00-5.00*I, 0.00-3.00*I, 0.00+1.00*I, -1.80+2.40*I,  0.00-4.00*I,  4.00-5.00*I};
    
  double lambda[2];
 // double evecs[];
//  eig(cA,lambda,evecs);
  char jobvl = 'N', jobvr = 'V';
  int n, lda, ldb, ldvl, ldvr, info;
  n=lda=4;
  double evecs[n];
  ldb = 4;
  ldvl = 1;
  ldvr = n;
  int lwork = max(1, n*n+64); // This may be choosen better!

  CPX work=lwork;
  double rwork=8*n; // This may be choosen better
  CPX alpha=4.;
  CPX beta=4.;
  CPX  vl[1];
  CPX vr[n*n];

zggev_(&jobvl, &jobvr, &n, a, &lda, b, &ldb, &alpha, &beta, vl, &ldvl, vr, &ldvr, &work, &lwork, &rwork, &info);

 // lambda=elem_div(alpha,beta);
  cout<<alpha<<endl;
  cout<< "eig(A,B) = \n";
//cout << "alpha, beta = "<<alpha<< ", " << beta <<endl;
  //cout << "lambda = "<<lambda<<endl;
  //cout << "evecs = "<<evecs<<endl;

*/

  return 0;

}

