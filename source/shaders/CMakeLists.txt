file(WRITE shaders.cpp "#include \"shaders.h\"

namespace Hippo3D {
namespace Shader {
")


# write fragment shaders to FRAGMENT_SHADERS map
file(APPEND shaders.cpp "
const std::map<std::string, std::string> FRAGMENT_SHADERS {
")

file(GLOB FILES "*.frag.glsl")

foreach(FILE ${FILES})
    get_filename_component(FILE_NAME ${FILE} NAME)
    string(REGEX REPLACE "\\.frag.glsl$" "" SHADER_NAME ${FILE_NAME})
    file(READ "${FILE}" SHADER)

    file(APPEND shaders.cpp "
    {
        \"${SHADER_NAME}\",
        R\"(${SHADER})\"
    },
")
endforeach()

file(APPEND shaders.cpp "};
")


# write vertex shaders to VERTEX_SHADERS map
file(APPEND shaders.cpp "
const std::map<std::string, std::string> VERTEX_SHADERS {
")

file(GLOB FILES "*.vert.glsl")

foreach(FILE ${FILES})
    get_filename_component(FILE_NAME ${FILE} NAME)
    string(REGEX REPLACE "\\.vert.glsl$" "" SHADER_NAME ${FILE_NAME})
    file(READ "${FILE}" SHADER)

    file(APPEND shaders.cpp "
    {
        \"${SHADER_NAME}\",
        R\"(${SHADER})\"
    },
")
endforeach()

file(APPEND shaders.cpp "};

}
}")