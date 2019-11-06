set(HEADERS
    math.hpp
    Geometry.hpp
    Vectors.hpp
    )

set(SOURCES
    Geometry.cpp
    Vectors.cpp
    )

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

# Package the system library
add_library(math STATIC ${SOURCES} ${HEADERS})

target_include_directories(math PUBLIC
    ../platform
    )

target_link_libraries(math PUBLIC
    platform
    )
