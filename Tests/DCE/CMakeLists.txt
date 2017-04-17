set(clang clang)
set(opt "${LLVM_TOOLS_BINARY_DIR}/opt;-load;$<TARGET_FILE:MyDCE>")

add_custom_target(DCE-test1
    COMMAND
        ${clang} -emit-llvm -S -c ${CMAKE_CURRENT_SOURCE_DIR}/test1.c -o test1.ll &&
        ${opt} -my-dce -S test1.ll -o test1.opt.ll &&
        vimdiff test1.ll test1.opt.ll
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    SOURCES test1.c)
add_dependencies(DCE-test1 MyDCE)
