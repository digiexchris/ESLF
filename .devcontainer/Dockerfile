FROM ubuntu:22.04
LABEL Description="ELSF Build environment"

ENV HOME /root

SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang \
    clangd \
    lld \
    cmake \
    gdb \
    wget \
    git \
    ninja-build \
    python3 \
    python3-pip 

run apt install llvm-14 llvm-14-tools curl -y

run update-alternatives --install /usr/bin/llvm-cov llvm-cov /usr/bin/llvm-cov-14 100
run update-alternatives --install /usr/bin/llvm-profdata llvm-profdata /usr/bin/llvm-profdata-14 100

# uncomment to use code completion using continue.dev extension run curl -fsSL https://ollama.com/install.sh | sh

# Let us add some heavy dependency
# RUN cd ${HOME} && \
#     wget --no-check-certificate --quiet \
#         https://boostorg.jfrog.io/artifactory/main/release/1.77.0/source/boost_1_77_0.tar.gz && \
#         tar xzf ./boost_1_77_0.tar.gz && \
#         cd ./boost_1_77_0 && \
#         ./bootstrap.sh && \
#         ./b2 install && \
#         cd .. && \
#         rm -rf ./boost_1_77_0