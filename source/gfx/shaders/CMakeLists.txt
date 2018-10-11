set(SHADER_NAME ${CMAKE_CURRENT_SOURCE_DIR}/flat.frag.glsl)
set(SHADER_GEN_TOOL "${CMAKE_SOURCE_DIR}/tools/shader-export.py")

add_custom_command(
        COMMAND ${PYTHON_EXECUTABLE} ${SHADER_GEN_TOOL} -i ${SHADER_NAME} -o ${SHADER_NAME}.test -l glsl-100-es
        DEPENDS ${SHADER_GEN_TOOL} ${SHADER_NAME}
        OUTPUT ${SHADER_NAME}.cpp ${SHADER_NAME}.h
        COMMENT "Generating code for ${SHADER_NAME}."
)

add_custom_target(
        shaders
        DEPENDS ${SHADER_NAME}.cpp ${SHADER_NAME}.h
)

add_dependencies(Mantis shaders)