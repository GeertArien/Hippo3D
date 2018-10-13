set(SHADER_NAME shaders)
set(SHADER_INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_NAME}.glsl)
set(SHADER_GEN_TOOL "${CMAKE_SOURCE_DIR}/tools/shader-export.py")

add_custom_command(
        COMMAND ${PYTHON_EXECUTABLE} ${SHADER_GEN_TOOL} -i ${SHADER_INPUT_FILE} -o ${SHADER_NAME}.test -l glsl-100-es
        DEPENDS ${SHADER_GEN_TOOL} ${SHADER_INPUT_FILE}
        OUTPUT ${SHADER_NAME}.cpp ${SHADER_NAME}.h
        COMMENT "Generating code for ${SHADER_INPUT_FILE}."
)

add_custom_target(
        shaders
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.cpp ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.h
)

add_dependencies(Mantis shaders)
target_include_directories(Mantis PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_sources(Mantis PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_NAME}.cpp)