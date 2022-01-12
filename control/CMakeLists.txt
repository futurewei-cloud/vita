set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../build/bin)

set(SOURCES
    ./src/kafka_producer.cpp
    ./src/pulsar_producer.cpp
    ./utils/randomstringgenerator.cpp
)

#Find libevent installation
find_path(LIBEVENT_INCLUDE_DIR
        NAMES event2/thread.h
        HINTS /usr/include
        REQUIRED)

FIND_LIBRARY(LIBUUID_LIBRARIES uuid)
FIND_LIBRARY(RDKAFKA rdkafka /usr/lib/x86_64-linux-gnu NO_DEFAULT_PATH)
FIND_LIBRARY(CPPKAFKA cppkafka /usr/local/lib NO_DEFAULT_PATH)
FIND_LIBRARY(PULSAR pulsar /usr/lib NO_DEFAULT_PATH)
FIND_LIBRARY(MESSAGEMANAGER messagemanager ${CMAKE_CURRENT_SOURCE_DIR}/../include NO_DEFAULT_PATH)
link_libraries(${RDKAFKA} ${CPPKAFKA} ${PULSAR})
include_directories(${RDKAFKA_INCLUDE_DIR} ${CPPKAFKA_INCLUDE_DIR} ${PULSAR_INCLUDE_DIR} ${LIBEVENT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)



add_library(AgentLib STATIC ${SOURCES})
target_link_libraries(AgentLib event) #Libevent linking is '-levent', thus linked lib is 'event' in the cmd


add_executable(Controller control_main.cpp)
target_link_libraries(Controller cppkafka)
target_link_libraries(Controller rdkafka)
target_link_libraries(Controller pulsar)
target_link_libraries(Controller AgentLib)
