# Project definition
cmake_minimum_required(VERSION 3.10)
project(Mantis)

add_subdirectory(source/shaders)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(SOURCES "${SRC_DIR}/main.cpp" source/core/ShaderProgram.cpp source/core/ShaderProgram.h source/shaders/shaders.h source/shaders/shaders.cpp source/core/Texture.cpp source/core/Texture.h source/context/Window.cpp source/context/Window.h source/core/Renderer.cpp source/core/Renderer.h source/core/Camera.cpp source/core/Camera.h source/core/Scene.cpp source/core/Scene.h source/GL_impl.h source/core/Mesh.cpp source/core/Mesh.h source/core/Object.cpp source/core/Object.h source/core/Material.cpp source/core/Material.h source/context/InputManager.cpp source/context/InputManager.h)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if(EMSCRIPTEN)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_ES2=1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s DISABLE_EXCEPTION_CATCHING=0")
else()
# glfw
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")
endif(EMSCRIPTEN)

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# stb-image
set(STB_DIR "${LIB_DIR}/stb")
add_library("stb" "${STB_DIR}/src/stb_image.c")
target_include_directories("stb" PRIVATE "${STB_DIR}/include")
target_include_directories(${PROJECT_NAME}  PRIVATE "${STB_DIR}/include")
target_link_libraries(${PROJECT_NAME} "stb")

# glm
set(glm_DIR "${LIB_DIR}/glm")
target_include_directories(${PROJECT_NAME}  PRIVATE "${glm_DIR}/glm")

