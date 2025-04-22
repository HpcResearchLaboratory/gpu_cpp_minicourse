FROM nvcr.io/nvidia/nvhpc:25.3-devel-cuda12.8-ubuntu22.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
    pkg-config \
    xorg-dev \
    libx11-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/gpu_cpp
