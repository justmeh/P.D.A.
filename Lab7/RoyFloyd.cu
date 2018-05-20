#include<iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
using namespace std;

#define N 5
#define INF 99999

// Device code
__global__ void matrixFloyd(float* graph, int k)
{
    int i = blockIdx.x + threadIdx.x;
    int j = blockIdx.y + threadIdx.y;
	
    if(graph[procid][k] + graph[k][j] < graph[procid][j])
		graph[procid][j] = graph[procid][k] + graph[k][j];
}
            
// Host code
int main()
{
    size_t size = N * N * sizeof(int);

    // Allocate input vectors h_A and h_B in host memory

    // Initialize input vectors
    int h_graph[N][N] = {
	0,3,9,8,3,
	5,0,1,4,2,
	6,6,0,4,5,
	2,9,2,0,7,
       	7,9,3,2,0,
   };
	
    // Allocate vectors in device memory
    int* d_graph;
    cudaMalloc(&d_graph, size);
	
    // Copy vectors from host memory to device memory
    cudaMemcpy(d_graph, h_graph, size, cudaMemcpyHostToDevice);

    // Invoke kernel
    dim3 threadsPerBlock(N, N);
    int numBlocks= 1;

    for(int k = 0; k < N; k++)
    {
	    matrixFloyd<<<numBlocks, threadsPerBlock>>>(d_graph, k);
    }
		
    // Copy result from device memory to host memory
    // h_C contains the result in host memory
    cudaMemcpy(h_graph, d_graph, size, cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(d_graph);
            
    // Free host memory
    for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (h_graph[i][j] == INF)
				cout << "INF ";
			else
				cout << h_graph[i][j] << " ";
		}
		cout << endl;
	}
}
