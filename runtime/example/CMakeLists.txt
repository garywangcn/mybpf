SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/out/example) 

aux_source_directory(./user_example SRC)
add_executable(user_example ${SRC})
target_link_libraries(user_example sutil dl pthread m elf)

