# Minicurso GPU C++

## Containers

- https://catalog.ngc.nvidia.com/orgs/nvidia/containers/nvhpc
- https://docs.nvidia.com/hpc-sdk/hpc-sdk-container/index.html

```bash
docker pull nvcr.io/nvidia/nvhpc:25.3-devel-cuda_multi-ubuntu22.04
docker build . -t gpu_cpp
```

## Compute Shaders

- https://www.khronos.org/opengl/wiki/Compute_Shader
- https://learnopengl.com/Guest-Articles/2022/Compute-Shaders/Introduction

```bash
xhost +
code ./src/compute_shaders/

docker run -it --rm \
  --gpus all \
  --device /dev/dri:/dev/dri \
  -e XDG_SESSION_TYPE=x11 \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v "$(pwd)/src:/opt/gpu_cpp" \
  -w "/opt/gpu_cpp/compute_shaders/" \
  gpu_cpp

# Build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -Bbuild && pushd build && make && popd

# Run
./build/particle
```

### Exercício

Mude o parâmetro gravidade na simulação. Além disso, mude as cores das partículas.

Onde esses parâmetros são definidos?

## CUDA

- https://developer.nvidia.com/blog/even-easier-introduction-cuda/
- https://docs.nvidia.com/cuda/cuda-c-programming-guide/#introduction

```bash
code ./src/cuda

docker run -it --rm \
  --gpus all \
  -v "$(pwd)/src:/opt/gpu_cpp" \
  -w "/opt/gpu_cpp/cuda/" \
  gpu_cpp

make
```

### Exercício

Agora, nos arquivos `./src/cuda/monte_carlo_pi.c` e `./src/cuda/monte_carlo_pi.cu`
mude a constante para os valores **100, 100000 e 100000000**:

```c
#define NUM_SAMPLES 100000000
```

Para cada valor, rode o benchmark:

```bash
hyperfine "./monte_carlo_pi_cpu" "./monte_carlo_pi_gpu" --warmup 10 -N
```

Explique o resultado (diferença nos tempos).

## OpenACC

- https://openacc-best-practices-guide.readthedocs.io/en/latest/01-Introduction.html
- https://enccs.github.io/OpenACC-CUDA-beginners/1.02_openacc-introduction/
- https://github-pages.ucl.ac.uk/research-computing-with-cpp/08openmp/02_intro_openmp.html


```bash
code ./src/openacc

docker run -it --rm \
  --gpus all \
  -v "$(pwd)/src:/opt/gpu_cpp" \
  -w "/opt/gpu_cpp/openacc/" \
  gpu_cpp

make
```

### Exercício

Mude o tamanho dos vetores para pelo menos 3 valores diferentes nas três
implementações (`./src/openacc/saxpy_oacc.cpp`, `./src/openacc/saxpy_omp.cpp` e
`./src/openacc/saxpy_serial.cpp`):

```cpp
constexpr std::size_t N = 1 << 24;
```

Para cada valor, rode o benchmark:

```bash
hyperfine --warmup 10 ./saxpy_serial ./saxpy_oacc ./saxpy_omp
```

Compare os resultados.
