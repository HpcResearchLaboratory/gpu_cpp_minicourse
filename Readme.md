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
cmake -Bbuild && pushd build && make && popd

#Run
./build/particle
```

# CUDA

- https://docs.nvidia.com/cuda/cuda-c-programming-guide/
