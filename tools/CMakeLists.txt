add_executable(tescandump tescandump.cpp)
target_link_libraries(tescandump teslacan)
set_target_properties(tescandump PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(tescandump PROPERTIES OUTPUT_NAME tescandump${BUILD_POSTFIX})
