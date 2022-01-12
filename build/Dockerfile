FROM fwnetworking/ubuntu:18.04
RUN rm -rf /var/local/git && mkdir -p /var/local/git

RUN echo "--- installing common dependencies ---" && \
    apt-get update -y && apt-get install -y \
    rpcbind \
    rsyslog \
    build-essential \
    make \
    g++ \
    unzip \
    cmake \
    clang-9 \
    llvm-9 \
    libelf-dev \
    doxygen \
    zlib1g-dev \
    libssl-dev \
    libboost-program-options-dev \
    libboost-all-dev \
    iproute2  \
    net-tools \
    iputils-ping \
    ethtool \
    curl \
    python3 \
    python3-pip \
    netcat \
    libcmocka-dev \
    lcov \
    git \
    autoconf \
    automake \
    dh-autoreconf \
    pkg-config \
    libtool \
    wget \
    uuid-dev \


RUN pip3 install httpserver netaddr

RUN echo "--- installing librdkafka ---" && \
    apt-get install -y --no-install-recommends\
    librdkafka-dev \
    && apt-get clean

RUN echo "--- installing cppkafka ---" && \
    git clone https://github.com/mfontanini/cppkafka.git /var/local/git/cppkafka && \
    cd /var/local/git/cppkafka && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    ldconfig && \
    rm -rf /var/local/git/cppkafka && \
    cd ~

ENV PULSAR_RELEASE_TAG='pulsar-2.6.1'
RUN echo "--- installing pulsar dependacies ---" && \
    mkdir -p /var/local/git/pulsar && \
    wget https://archive.apache.org/dist/pulsar/${PULSAR_RELEASE_TAG}/DEB/apache-pulsar-client.deb -O /var/local/git/pulsar/apache-pulsar-client.deb && \
    wget https://archive.apache.org/dist/pulsar/${PULSAR_RELEASE_TAG}/DEB/apache-pulsar-client-dev.deb -O /var/local/git/pulsar/apache-pulsar-client-dev.deb && \
    cd /var/local/git/pulsar && \
    apt install -y ./apache-pulsar-client*.deb && \
    rm -rf /var/local/git/pulsar

RUN echo "--- installing rabbitmq ---" && \
    git clone https://github.com/CopernicaMarketingSoftware/AMQP-CPP.git /var/local/git/rabbitmq && \
    cd /var/local/git/rabbitmq && \
    mkdir build && \
    cd build %% \
    cmake .. && \
    cmake --build . --target install && \
    rm -rf /var/local/git/rabbitmq &&\
    cd ~
    
# installing grpc and its dependencies
# ENV GRPC_RELEASE_TAG v1.24.x
# RUN echo "4--- cloning grpc repo ---" && \
#     git clone -b ${GRPC_RELEASE_TAG} https://github.com/grpc/grpc /var/local/git/grpc && \
#     cd /var/local/git/grpc && \
#     git submodule update --init && \
#     echo "--- installing c-ares ---" && \
#     cd /var/local/git/grpc/third_party/cares/cares && \
#     git fetch origin && \
#     git checkout cares-1_15_0 && \
#     mkdir -p cmake/build && \
#     cd cmake/build && \
#     cmake -DCMAKE_BUILD_TYPE=Release ../.. && \
#     make -j4 install && \
#     cd ../../../../.. && \
#     rm -rf third_party/cares/cares && \
#     echo "--- installing protobuf ---" && \
#     cd /var/local/git/grpc/third_party/protobuf && \
#     mkdir -p cmake/build && \
#     cd cmake/build && \
#     cmake -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release .. && \
#     make -j4 install && \
#     cd ../../../.. && \
#     rm -rf third_party/protobuf && \
#     echo "--- installing grpc ---" && \
#     cd /var/local/git/grpc && \
#     mkdir -p cmake/build && \
#     cd cmake/build && \
#     cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DgRPC_PROTOBUF_PROVIDER=package -DgRPC_ZLIB_PROVIDER=package -DgRPC_CARES_PROVIDER=package -DgRPC_SSL_PROVIDER=package -DCMAKE_BUILD_TYPE=Release ../.. && \
#     make -j4 install && \
#     echo "--- installing google test ---" && \
#     cd /var/local/git/grpc/third_party/googletest && \
#     cmake -Dgtest_build_samples=ON -DBUILD_SHARED_LIBS=ON . && \
#     make && \
#     make install && \
#     rm -rf /var/local/git/grpc && \
#     cd ~