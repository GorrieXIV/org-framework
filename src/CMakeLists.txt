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

target_link_libraries(orgengine PRIVATE
    -L/usr/local/
    -lSDL2
    -lSDL2_image
    -lSDL2_ttf
    -lSDL2_mixer
    )

if(USE_LOCAL_LIBS)
    target_link_libraries(orgengine PRIVATE nlohmann_json)
else()
    target_link_libraries(orgengine PRIVATE ${CONAN_LIBS})
endif()
