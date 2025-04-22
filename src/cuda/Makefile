NVCC = nvcc
NVCC_FLAGS = -O3 -Wno-deprecated-gpu-targets
CC = gcc
CFLAGS = -O3
LDFLAGS = -lcurand

GPU_TARGET = monte_carlo_pi_gpu
CPU_TARGET = monte_carlo_pi_cpu

GPU_SRC = monte_carlo_pi.cu
CPU_SRC = monte_carlo_pi.c

all: $(GPU_TARGET) $(CPU_TARGET)

$(GPU_TARGET): $(GPU_SRC)
	$(NVCC) $(NVCC_FLAGS) $(GPU_SRC) -o $(GPU_TARGET) $(LDFLAGS)

$(CPU_TARGET): $(CPU_SRC)
	$(CC) $(CFLAGS) $(CPU_SRC) -o $(CPU_TARGET)

clean:
	rm -f $(GPU_TARGET) $(CPU_TARGET)

.PHONY: all clean
