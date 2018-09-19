#include  <iostream>
#include  <math.h>
 
__global__
void add(int n, float *x, float *y)
{
  for (int i = 0; i < n; i++)
      y[i] = x[i] + y[i];
}

int main(void)
{
  int N = 1<<20; // 1M elements

  // float *x = new float[N];
  // float *y = new float[N];
  float *x, *y;
  cudaMallocManaged(&x, N*sizeof(float));
  cudaMallocManaged(&y, N*sizeof(float));
  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }
  add<<<1, 1>>>(N, x, y);

  // wait for cuda to finish before continuing
  cudaDeviceSynchronize();


  float maxError = 0.0f;
  for (int i = 0; i < N; i++) {
    maxError = fmax(maxError, fabs(y[i]-3.0f));
  }
  std::cout << "Max error: " << maxError << std::endl;

  cudaFree(x);
  cudaFree(y);
  // delete [] x;
  // delete [] y;

  return 0;
}

