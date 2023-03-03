FROM debian:11

# basic tools
RUN apt-get update && apt-get install -y --no-install-recommends \
  picocom \
  git \
  ca-certificates \
  make \
  cmake \
  ninja-build \
  g++

# tools for building SDK
RUN apt-get update && apt-get install -y --no-install-recommends \
  cmake \
  gcc-arm-none-eabi \
  libnewlib-arm-none-eabi \
  build-essential \
  libstdc++-arm-none-eabi-newlib \
  pkg-config

# build and install OpenOCD for RP2040
RUN apt-get update && apt-get install -y --no-install-recommends \
  automake \
  autoconf \
  build-essential \
  texinfo \
  libtool \
  libftdi-dev \
  libusb-1.0-0-dev
# OPENOCD_VERSION must be taken from branch 'rp2040'!
ENV OPENOCD_VERSION=8e3c38f78730ce878ff81448bc3f6c1e6bb06e13
ENV OPENOCD_PATH=/opt/pico/openocd
RUN mkdir -p "$(dirname "$OPENOCD_PATH")" && \
    git clone \
          -c 'advice.detachedHead=false' \
          --branch "rp2040" \
          --recursive \
          --depth 1 \
          "https://github.com/raspberrypi/openocd.git" \
          "$OPENOCD_PATH" \
          && \
    cd "$OPENOCD_PATH" && \
    git reset --hard "$OPENOCD_VERSION" && \
    ./bootstrap && \
    ./configure --enable-ftdi --enable-sysfsgpio --enable-bcm2835gpio && \
    make -j$(nproc) && \
    make install
COPY openocd_rp2040 /usr/local/bin/

# install SDK
ENV PICO_SDK_PATH=/opt/pico/pico-sdk
ENV PICO_SDK_VERSION=1.5.0
RUN mkdir -p "$(dirname "$PICO_SDK_PATH")" && \
    git clone \
          -c 'advice.detachedHead=false' \
          --branch "$PICO_SDK_VERSION" \
          --depth 1 \
          "https://github.com/raspberrypi/pico-sdk.git" \
          "$PICO_SDK_PATH" \
          && \
    cd "$PICO_SDK_PATH" && \
    git submodule update --init
