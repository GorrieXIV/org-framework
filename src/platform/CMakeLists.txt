set(HEADERS
    platform.hpp
    Window.hpp
    )

set(SOURCES
    Window.cpp
    )

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

# Package the system library
add_library(platform STATIC ${SOURCES} ${HEADERS})

target_link_libraries(platform PUBLIC
    -L/usr/local/
    -lSDL2
    -lSDL2_image
    -lSDL2_ttf
    )
