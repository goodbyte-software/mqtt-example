# Variables
BUILD_DIR := "clients/build"

clean:
    rm -rf {{BUILD_DIR}}/CMakeCache.txt

build:
    mkdir -p {{BUILD_DIR}}
    cmake -B {{BUILD_DIR}} -S clients
    cmake --build {{BUILD_DIR}}

rebuild: clean build

# Publisher
publish:
    ./{{BUILD_DIR}}/pub

# Subscriber
subscribe:
    ./{{BUILD_DIR}}/sub

# Broker
run_broker:
    ./brokers/start_broker_tls_anonymous.sh