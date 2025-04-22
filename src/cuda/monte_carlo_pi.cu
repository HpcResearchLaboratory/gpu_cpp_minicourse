#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <curand_kernel.h>

#define NUM_SAMPLES 100000000
#define BLOCK_SIZE 256

// Kernel to generate random points and count those inside the circle
__global__ void monte_carlo_pi(int *count, int n, unsigned int seed) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= n) return;

    // Create random number generator state
    curandState state;
    curand_init(seed, idx, 0, &state);

    // Generate random point in [0,1) x [0,1)
    float x = curand_uniform(&state);
    float y = curand_uniform(&state);

    // Check if point is inside circle
    if (x*x + y*y <= 1.0f) {
        atomicAdd(count, 1);
    }
}

int main() {
    int *d_count;
    int h_count = 0;
    int num_blocks = (NUM_SAMPLES + BLOCK_SIZE - 1) / BLOCK_SIZE;

    // Allocate device memory for counter
    cudaMalloc(&d_count, sizeof(int));
    cudaMemset(d_count, 0, sizeof(int));

    // Launch kernel
    monte_carlo_pi<<<num_blocks, BLOCK_SIZE>>>(d_count, NUM_SAMPLES, time(NULL));

    // Copy result back to host
    cudaMemcpy(&h_count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    // Calculate pi
    float pi = 4.0f * h_count / NUM_SAMPLES;
    printf("Estimated value of π: %f\n", pi);
    printf("Samples used: %d\n", NUM_SAMPLES);
    printf("Points inside circle: %d\n", h_count);

    // Cleanup
    cudaFree(d_count);

    return 0;
}
