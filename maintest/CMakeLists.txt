project(maintest)

aux_source_directory(. CURRENT_SRC_FILES)
message(STATUS  "------${CURRENT_SRC_FILES}")
add_executable(maintets ${CURRENT_SRC_FILES})
target_link_libraries(maintets ${HV_LIBRARIES})

