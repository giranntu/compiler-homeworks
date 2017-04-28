macro(test_pass TARGET_NAME PASS_LIB PASS SOURCE)
    set(clang clang)
    set(opt "${LLVM_TOOLS_BINARY_DIR}/opt;-load;$<TARGET_FILE:${PASS_LIB}>")

    add_custom_target(${TARGET_NAME}
        COMMAND
            ${clang} -emit-llvm -S -c ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}.c -o ${SOURCE}.ll &&
            ${opt} ${PASS} -S ${SOURCE}.ll -o ${SOURCE}.opt.ll &&
            vimdiff ${SOURCE}.ll ${SOURCE}.opt.ll
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        SOURCES ${SOURCE}.c)
    add_dependencies(${TARGET_NAME} ${PASS_LIB})
endmacro(test_pass)

add_subdirectory(DCE)
