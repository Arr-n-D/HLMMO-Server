# FROM alpine:3.18 AS build

# RUN apk update && \ 
#     apk add --no-cache \
#         build-base=0.5-r3 \
#         cmake=3.24.3-r0 \
#         boost1.80-dev=1.80.0-r3

FROM ubuntu:22.04 AS build

# Install CMake, and Boost + OpenSSL
RUN apt-get update && \
    apt-get install -y \
        build-essential \
        cmake \
        libboost-all-dev \
        libssl-dev \ 
        # enet lib
        libenet-dev

WORKDIR /app

# Copy source code
COPY src/ ./src/
COPY include/ ./include/
COPY cmake/ ./cmake/
COPY CMakeLists.txt .


WORKDIR /app/build

# Build

RUN cmake -DCMAKE_BUILD_TYPE=Debug .. && \
    cmake --build . --parallel 8

FROM ubuntu:22.04 AS release

# Install Boost + OpenSSL
RUN apt-get update && \
    apt-get install -y \
        libboost-all-dev \
        libssl-dev \
        # enet lib
        libenet-dev


# Create a user dedicated to running the application (for security purposes)
RUN useradd --create-home --shell /bin/bash server-user
USER server-user

COPY --chown=server-user:server-user --from=build \
    ./app/build/src/Server \
    ./app/

ENTRYPOINT [ "./app/Server" ]