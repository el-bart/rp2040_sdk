FROM debian:12

# basic tools
RUN apt-get update && apt-get install -y --no-install-recommends \
  gdb \
  gdb-multiarch \
  python3 \
  picocom \
  git \
  ca-certificates \
  make \
  cmake \
  ninja-build \
  g++

# tools for building RP2040 Pico SDK
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
# OPENOCD_VERSION must be taken from branch 'rp2040...' family!
ENV OPENOCD_VERSION=4d87f6dcae77d3cbcd8ac3f7dc887adf46ffa504
ENV OPENOCD_PATH=/opt/pico/openocd
RUN mkdir -p "$(dirname "$OPENOCD_PATH")" && \
    git clone \
          --branch "rp2040-v0.12.0" \
          "https://github.com/raspberrypi/openocd.git" \
          "$OPENOCD_PATH" \
          && \
    cd "$OPENOCD_PATH" && \
    git reset --hard "$OPENOCD_VERSION" && \
    ./bootstrap && \
    ./configure --enable-ftdi --enable-sysfsgpio --enable-bcm2835gpio --enable-picoprobe && \
    make -j$(nproc) && \
    make install

# install RP2040 Pico SDK
ENV PICO_SDK_PATH=/opt/pico/pico-sdk
ENV PICO_SDK_VERSION=1.5.1
RUN mkdir -p "$(dirname "$PICO_SDK_PATH")" && \
    git clone \
          -c 'advice.detachedHead=false' \
          --branch "$PICO_SDK_VERSION" \
          "https://github.com/raspberrypi/pico-sdk.git" \
          "$PICO_SDK_PATH" \
          && \
    cd "$PICO_SDK_PATH" && \
    git submodule update --init

COPY rp2040_* /usr/local/bin/
