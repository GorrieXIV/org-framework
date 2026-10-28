set(HEADERS
    DisplayEngine.hpp
    Texture.hpp
    Camera.hpp
    TexturedEntity.hpp
    Window.hpp
    Geometry.hpp
    Vectors.hpp
    PhysicsEngine.hpp
    Collider.hpp
    PolygonCollider.hpp
    CollisionDetection.hpp
    Timer.hpp
    Entity.hpp
    Controller.hpp
    Audio.hpp
    SDL.h
    )

set(SOURCES
    DisplayEngine.cpp
    Texture.cpp
    Camera.cpp
    TexturedEntity.cpp
    Window.cpp
    Geometry.cpp
    PhysicsEngine.cpp
    Collider.cpp
    PolygonCollider.cpp
    CollisionDetection.cpp
    Timer.cpp
    Entity.cpp
    Controller.cpp
    Audio.cpp
    )

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

add_library(orgengine STATIC ${SOURCES} ${HEADERS})

target_include_directories(orgengine PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/orgengine>"
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(nlohmann_json REQUIRED)

# PUBLIC: consumers of the installed static library must link the same deps.
target_link_libraries(orgengine PUBLIC
    SDL2::SDL2
    SDL2_image::SDL2_image
    sdl_ttf::sdl_ttf
    SDL2_mixer::SDL2_mixer
    nlohmann_json::nlohmann_json
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/orgengine"
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)

install(TARGETS orgengine EXPORT orgengineTargets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/orgengine"
)
