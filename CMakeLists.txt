cmake_minimum_required(VERSION 3.18)
project(CanisTemplate)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME}>)
set(ASSETS_DIR_NAME assets)

add_definitions(
    #-c
    #-msse2
    #-mavx
    #-mavx2
    #-mavx512vl
    #-mavx512f
    #-march=skylake-avx512
    #-O
    #-ftime-report
    #-Ofast
)

add_definitions(-DCANIS_EDITOR)

# Some build settings required for Javascript build
if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(USE_FLAGS "-s USE_SDL=2 -s FULL_ES3=1 -s USE_FREETYPE=1 --preload-file ${PROJECT_SOURCE_DIR}/assets@/assets")
    set(OPENGL_LIBRARIES "-s USE_WEBGL2=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

add_subdirectory(external/canis)

file(GLOB_RECURSE SRC_SOURCES src/*.c*)
file(GLOB_RECURSE SRC_HEADERS src/*.h*)


add_executable(${PROJECT_NAME} ${SRC_SOURCES} ${SRC_HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE canis)

target_precompile_headers(${PROJECT_NAME}
    PRIVATE
    <Canis/App.hpp>
    <Canis/Math.hpp>
    <Canis/Canis.hpp>
    <Canis/Scene.hpp>
    <Canis/Entity.hpp>
    <Canis/ECS/Encode.hpp>
    <Canis/ECS/Decode.hpp>
    <Canis/SceneManager.hpp>
    <Canis/AssetManager.hpp>
    <Canis/ScriptableEntity.hpp>
    <Canis/External/entt.hpp>
    <Canis/ECS/Components/ScriptComponent.hpp>
    <Canis/ECS/Components/MeshComponent.hpp>
    <Canis/ECS/Components/SphereColliderComponent.hpp>
    <Canis/ECS/Components/TransformComponent.hpp>
    <Canis/ECS/Components/RectTransformComponent.hpp>
    <Canis/ECS/Components/Camera2DComponent.hpp>
    <Canis/ECS/Components/TextComponent.hpp>
    <Canis/ECS/Components/ColorComponent.hpp>
    <Canis/ECS/Components/Sprite2DComponent.hpp>
    <Canis/ECS/Systems/RenderHUDSystem.hpp>
    <Canis/ECS/Systems/RenderTextSystem.hpp>
    <Canis/ECS/Systems/SpriteRenderer2DSystem.hpp>
    <Canis/ECS/Systems/SpriteAnimationSystem.hpp>
    <Canis/ECS/Systems/CollisionSystem2D.hpp>
    <Canis/ECS/Systems/ButtonSystem.hpp>
    <Canis/ECS/Systems/RenderMeshWithShadowSystem.hpp>
    <Canis/GameHelper/StateMachine/StateMachine.hpp>
)

#create_symlink
#copy_directory
if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${ASSETS_DIR_NAME}/
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ASSETS_DIR_NAME})
else()
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_SOURCE_DIR}/${ASSETS_DIR_NAME}/
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ASSETS_DIR_NAME})
endif()