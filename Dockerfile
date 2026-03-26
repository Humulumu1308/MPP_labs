FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
	git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

RUN git clone https://github.com/Humulumu1308/MPP_lab0 .

WORKDIR /app/build

RUN cmake .. && cmake --build . --config Release
