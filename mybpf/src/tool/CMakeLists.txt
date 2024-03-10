SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/out/tool) 

aux_source_directory(./runbpf RUNBPF_SRC)
add_executable(runbpf ${RUNBPF_SRC})
target_link_libraries(runbpf sutil static_bs sutil static_bs dl pthread m elf)

