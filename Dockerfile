FROM ubuntu:22.04 AS build

# Install CMake, and Boost + OpenSSL
RUN apt-get update && \
    apt-get install -y \
        build-essential \
        cmake \
        libboost-all-dev \
        libssl-dev \ 
        # enet lib
        libenet-dev \ 
        # curl
        libcurl4-openssl-dev

WORKDIR /app

# Copy source code
COPY src/ ./src/
COPY include/ ./include/
COPY cmake/ ./cmake/
COPY sentry/ ./sentry/
COPY CMakeLists.txt .


WORKDIR /app/build
RUN cmake -DCMAKE_BUILD_TYPE=Debug .. && \
    cmake --build . --parallel 8


FROM ubuntu:22.04 AS release

# Install Boost + OpenSSL
RUN apt-get update && \
    apt-get install -y \
        libboost-all-dev \
        libssl-dev \
        libenet-dev \ 
        libcurl4-openssl-dev        

RUN useradd --create-home --shell /bin/bash server-user
RUN mkdir /app
RUN chown -R server-user:server-user /app

USER server-user

COPY --chown=server-user:server-user --from=build \
    ./app/build/Server \
    ./app/

ENTRYPOINT [ "./app/Server" ]