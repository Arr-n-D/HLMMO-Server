FROM ubuntu:22.04

# Install dependencies
# We need OpenSSL for DTLS, CMAKE for building, and CURL for downloading the source code
RUN apt-get update && apt-get install -y \
    openssl \
    make \
    cmake \
    curl


# download boost library 