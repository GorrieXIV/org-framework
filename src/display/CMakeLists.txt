set(HEADERS
    display.hpp
    DisplayEngine.hpp
    Texture.hpp
    Camera.hpp
    TexturedEntity.hpp
    )

set(SOURCES
    DisplayEngine.cpp
    Texture.cpp
    Camera.cpp
    TexturedEntity.cpp
    )

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

add_library(display STATIC ${SOURCES} ${HEADERS})

target_include_directories(display PRIVATE
    ../platform
    ../math
    ../time
    ../entities
    )

target_link_libraries(display PRIVATE
    platform
    math
    time
    entities
    )
