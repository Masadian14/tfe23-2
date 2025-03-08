cmake_minimum_required(VERSION 3.10)

# Set the project name
project(my_project VERSION 0.1 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include dependencies
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

# Include Paho MQTT C++ library
find_package(PahoMqttCpp REQUIRED)

# Configure the include path
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/include/config.h" @ONLY)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include") # Add the output path to the include PATH
include_directories("${CMAKE_CURRENT_SOURCE_DIR}") # Add the source path to the include PATH

# Add the executable
#add_executable(${PROJECT_NAME} main.cpp sms_notification.cpp email_notification.cpp mqtt_notification.cpp)

add_executable(my_project main.cpp sms_notification.cpp email_notification.cpp mqtt_notification.cpp)
# Link the libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
                                        CURL::libcurl
                                        nlohmann_json::nlohmann_json
                                        PahoMqttCpp::paho-mqttpp3
)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2 # Aktuelle Version prüfen!
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests test_main.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)