// #include <iostream>
// using namespace std;

// __global__ void multi(int *A, int *B, int *C, int n){
//     int row = blockIdx.y * blockDim.y + threadIdx.y;
//     int col = blockIdx.x * blockDim.x + threadIdx.x;

//     if(row<n && col<n){
//         int sum = 0;
//         for(int k=0; k<n; k++){
//             sum += A[row*n + k] * B[k*n + col];
//         }
//         C[row*n + col] = sum;
//     }
// }

// int main(){
//     int N = 2;
//     int matrixSize = N*N;
//     size_t matrixBytes = matrixSize * sizeof(int);

//     int *a,*b,*c; //host matrix
//     a = new int[matrixSize];
//     b = new int[matrixSize];
//     c = new int[matrixSize];


//     int *x,*y,*z; // device matrix
//     cudaMalloc(&x, matrixBytes);
//     cudaMalloc(&x, matrixBytes);
//     cudaMalloc(&x, matrixBytes);

//     for(int i=0; i< N*N; i++){ //matrix initialise
//         a[i] = b[i] = i;
//     }

//     cudaMemcpy(x,a, matrixBytes, cudaMemcpyHostToDevice);
//     cudaMemcpy(y,b, matrixBytes, cudaMemcpyHostToDevice);
//     // cudaMemcpy(z,c, matrixBytes, cudaMemcpyHostToDevice);

//     int THREADS = 2;
//     int BLOCKS = N/THREADS;

//     dim3 threads(THREADS, THREADS);
//     dim3 blocks(BLOCKS, BLOCKS);

//     multi<<<blocks, threads >>> (x,y,z,N);

//     cudaMemcpy(a,x, matrixBytes, cudaMemcpyDeviceToHost);
//     cudaMemcpy(b,y, matrixBytes, cudaMemcpyDeviceToHost);
//     cudaMemcpy(c,z, matrixBytes, cudaMemcpyDeviceToHost);

//     for(int i=0; i<N*N; i++){
//         cout << a[i] << " ";
//     if ((i + 1) % N == 0) {
//         cout << "\n";
//     }

//     }

//     for(int i=0; i<N*N; i++){
//         cout << a[i] << " ";
//     if ((i + 1) % N == 0) {
//         cout << "\n";
//     }

//     }

//     for(int i=0; i<N*N; i++){
//         cout << a[i] << " ";
//     if ((i + 1) % N == 0) {
//         cout << "\n";
//     }

//     }

// }


#include <iostream>
using namespace std;

__global__ void mul(int *a, int *b, int *c, int n){
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;

  if(row<n && col<n){
    int sum=0;
    for(int i=0; i<n; i++){
        sum += a[row * n + i] * b[i*n+col];
    }
    c[row*n+col]=sum;
  }

}

  int main(){

    int N= 3;

    int msize = N*N;
    size_t mbyte = msize*sizeof(int);

    int *a = new int[msize];
    int *b = new int[msize];
    int *c = new int[msize];

    int *x, *y, *z;
    cudaMalloc(&x, mbyte);
    cudaMalloc(&y, mbyte);
    cudaMalloc(&z, mbyte);

    for(int i=0; i<msize; i++){
        a[i]=b[i]=i;
    }

    cudaMemcpy(x,a, mbyte, cudaMemcpyHostToDevice);
    cudaMemcpy(y,b, mbyte, cudaMemcpyHostToDevice);

    dim3 thread(16,16);
    dim3 block ((N + thread.x - 1)/thread.x, (N+thread.y-1)/thread.y);

    mul<<<block, thread>>>(x,y,z,N);

    cudaMemcpy(c,z, mbyte, cudaMemcpyDeviceToHost);

    cout<<endl;
    cout<<"Matrix A : "<<endl;
    for(int row=0; row<N; row++){
        for(int col=0; col<N; col++){
            cout<<a[row*N + col]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;

    cout<<"Matrix B : "<<endl;
    for(int row=0; row<N; row++){
        for(int col=0; col<N; col++){
            cout<<b[row*N + col]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;


    cout<<"Matrix C : "<<endl;
    for(int row=0; row<N; row++){
        for(int col=0; col<N; col++){
            cout<<c[row*N + col]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;

    delete[] a;
    delete[] b;
    delete [] c;

    cudaFree(x);
    cudaFree(y);
    cudaFree(z);
    return 0;
  
}