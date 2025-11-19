FROM ubuntu:25.10

RUN apt-get update && apt-get install -y \
	wget \
	build-essential \
	git \
	pkg-config \
	libssl-dev \
	curl \
	binutils-arm-none-eabi \
	gcc-arm-none-eabi \
	libnewlib-arm-none-eabi \
	stlink-tools

RUN	apt-get install -y fish

ARG CMAKE_VERSION=4.1.3
RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz \
    && tar -xzf cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz \
    && mv cmake-${CMAKE_VERSION}-linux-x86_64 /opt/cmake \
    && ln -s /opt/cmake/bin/* /usr/local/bin/
