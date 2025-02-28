cmake_minimum_required (VERSION 3.10.2)

# Set the project name to your project name, template isn't very descriptive
project (gas-assist VERSION 0.0.1 LANGUAGES CXX)
string(TIMESTAMP BUILD_DATE "%Y-%m-%dT%H:%M:%S")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Include dependencies
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(Catch2 3 REQUIRED)

find_package(CURL REQUIRED) 

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/include/config.h.in" @ONLY)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include") # add the output path to the include PATH

# add the executable
add_executable(${PROJECT_NAME} main.cpp)

# Add libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
                                        fmt::fmt
                                        CLI11::CLI11
                                        nlohmann_json::nlohmann_json
                                        CURL::libcurl
)
project(my_project)

# Manually set the path to the Paho MQTT C library
set(PahoMqttC_DIR /usr/local/lib/cmake/PahoMqttC)
find_package(PahoMqttC REQUIRED)

# Find the Paho MQTT C++ library
find_package(PahoMqttCpp REQUIRED)

add_executable(my_project main.cpp)

# Link the Paho MQTT libraries
target_link_libraries(my_project PahoMqttC::paho-mqtt3as PahoMqttCpp::paho-mqttpp3)