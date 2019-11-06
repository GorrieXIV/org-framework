set(HEADERS
    controls.hpp
    Controller.hpp
    )

set(SOURCES
    Controller.cpp
    )

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

add_library(controls STATIC ${SOURCES} ${HEADERS})

target_include_directories(controls PRIVATE
    ../platform
    ../math
    ../entities
    ../display
    )

target_link_libraries(controls PRIVATE
    platform
    math
    entities
    display
    )
