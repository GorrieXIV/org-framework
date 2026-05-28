set(HEADERS
    DisplayEngine.hpp
    Texture.hpp
    Camera.hpp
    TexturedEntity.hpp
    Window.hpp
    Geometry.hpp
    Vectors.hpp
    Lines.hpp
    PhysicsEngine.hpp
    Collider.hpp
    PolygonCollider.hpp
    BasicCollisions.hpp
    SATCollisions.hpp
    DiagonalCollisions.hpp
    LookAheadCollisions.hpp
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
    BasicCollisions.cpp
    SATCollisions.cpp
    DiagonalCollisions.cpp
    LookAheadCollisions.cpp
    Timer.cpp
    Entity.cpp
    Controller.cpp
    Audio.cpp
    )

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

add_library(orgengine STATIC ${SOURCES} ${HEADERS})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(orgengine PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    sdl_ttf::sdl_ttf
    SDL2_mixer::SDL2_mixer
    nlohmann_json::nlohmann_json
)
