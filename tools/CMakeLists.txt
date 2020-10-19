add_executable(canhexdump canhexdump.cpp)
target_link_libraries(canhexdump teslacan)
set_target_properties(canhexdump PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(canhexdump PROPERTIES OUTPUT_NAME canhexdump${BUILD_POSTFIX})

add_executable(canbindiff canbindiff.cpp)
target_link_libraries(canbindiff teslacan)
set_target_properties(canbindiff PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(canbindiff PROPERTIES OUTPUT_NAME canbindiff${BUILD_POSTFIX})

add_executable(tescandump tescandump.cpp)
target_link_libraries(tescandump teslacan)
set_target_properties(tescandump PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(tescandump PROPERTIES OUTPUT_NAME tescandump${BUILD_POSTFIX})

add_executable(speeddump speeddump.cpp)
target_link_libraries(speeddump teslacan)
set_target_properties(speeddump PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(speeddump PROPERTIES OUTPUT_NAME speeddump${BUILD_POSTFIX})
