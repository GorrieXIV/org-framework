set(HEADERS
    time.hpp
    Timer.hpp
    )

set(SOURCES
    Timer.cpp
    )

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

# Package the system library
add_library(time STATIC ${SOURCES} ${HEADERS})

target_include_directories(time PUBLIC
    ../platform
    )

target_link_libraries(time PUBLIC
    platform
    )
