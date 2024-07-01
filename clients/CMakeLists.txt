cmake_minimum_required(VERSION 3.16)
project(client)

# General settings
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Integrate PAHO lib
## Set CMP0077 policy to NEW to make option() honor normal variables
if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()
set(PAHO_WITH_MQTT_C TRUE CACHE BOOL "Build C library")
set(PAHO_BUILD_STATIC TRUE CACHE BOOL "Build static library")
set(PAHO_WITH_SSL TRUE CACHE BOOL "Build library with SSL support")

add_subdirectory(lib/paho.mqtt.cpp)

# Publisher
add_executable(pub
    src/pub.cpp
)

target_link_libraries(pub PUBLIC paho-mqttpp3-static)

# Subsriber
add_executable(sub
    src/sub.cpp
)

target_link_libraries(sub PUBLIC paho-mqttpp3-static)
