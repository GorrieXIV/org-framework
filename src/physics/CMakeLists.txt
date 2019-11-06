set(HEADERS
    physics.hpp
    CollisionDetection.hpp
    )

set(SOURCES
    CollisionDetection.cpp
    )

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

# Package the system library
add_library(physics STATIC ${SOURCES} ${HEADERS})

target_include_directories(physics PRIVATE
    ../platform
    ../math
    )

target_link_libraries(physics PRIVATE
    platform
    math
    )
