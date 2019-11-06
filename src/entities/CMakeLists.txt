set(HEADERS
    entities.hpp
    Entity.hpp
    )

set(SOURCES
    Entity.cpp
    )

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

add_library(entities STATIC ${SOURCES} ${HEADERS})

target_include_directories(entities PRIVATE
    ../platform
    ../time
    ../math
    )

target_link_libraries(entities PRIVATE
    platform
    time
    math
    )
