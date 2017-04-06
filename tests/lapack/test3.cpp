#include<iostream>
#include<math.h>

#include<complex>
#include <stdlib.h>

using namespace std;

extern "C" void zgetrf_( int*, int* , complex<double>* , int*, int* , int* );

extern "C" void zgetri_( int*, complex<double>* , int*, int* , complex<double>*, int* , int* );

//........................................................................................
void zgeTranspose( complex<double> *Transposed, complex<double> *M ,int n)
{

int i,j;
for(i=0;i<n;i++)

 for(j=0;j<n;j++) Transposed[i+n*j] = M[i*n+j];
}

//.........................................................................................
void MatrixComplexInverse(complex<double> *invA, complex<double> *A, int n)
{

 int LWORK=10*n;

 int *permutations;

 complex<double> *WORK, *tempA;

 tempA = new complex<double>[n*n];

 permutations =  new int[2*n];
 WORK = new complex<double>[n*n];


 int INFO;

 zgeTranspose(tempA,A,n);


 zgetrf_( &n, &n, tempA , &n, permutations , &INFO );

 if (INFO != 0) {
   cout<<"ComplexMatrixInverse: Error at zgetrf  \n"; exit(0);
   }



 zgetri_( &n, tempA , &n, permutations , WORK, &LWORK, &INFO );

 if (INFO != 0) {
   cout<<"ComplexMatrixInverse: Error at zgetri  \n"; exit(0);
   }

 zgeTranspose(invA,tempA,n);

 delete [] WORK;

 delete [] tempA;
 delete [] permutations;

}

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
 int i,j;
 const int N = 3;

 complex<double> I(0.,1.);

 complex<double> A[] = { 1. + I , 2. ,  3 , 4. , 5.+I , 6. , 7., 8., 9. + I};

 complex<double> invA[N*N];

 MatrixComplexInverse(invA,A,N);


 for(i=0;i<N;i++){
   for(j=0;j<N;j++) cout << invA[i*N + j]<<"\t";

   cout<<"\n";
 }

cout<<"---------------------------\n";

return 0;

}
