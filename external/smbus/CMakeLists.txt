
file(GLOB HEADERS *.h)
file(GLOB SOURCES *.c*)

add_library(smbus ${HEADERS} ${SOURCES})

# target_compile_options(smbus PRIVATE
# 	"-Wno-tautological-pointer-compare"
# 	"-Wno-unused-function")
