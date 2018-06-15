
cmake_minimum_required(VERSION 3.0)

project(taco-monitor)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/include/")
include_directories("/usr/local/include/")

link_directories("/usr/lib/")
link_directories("/usr/local/lib/")

file(GLOB HEADERS include/*.h)
file(GLOB SOURCES src/*.c*)

add_executable(taco_mon ${HEADERS} ${SOURCES})

include_directories(include)
target_link_libraries(taco_mon wiringPi)

#-L/usr/lib/python3.5/config-3.5m-arm-linux-gnueabihf -L/usr/lib -lpython3.5m -lpthread -#ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions

# /usr/bin/python3-config --ldflags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/usr/lib/python3.5/config-3.5m-arm-linux-gnueabihf -L/usr/lib -lpython3.5m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions")