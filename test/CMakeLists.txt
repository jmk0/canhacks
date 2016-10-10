add_executable(TeslaCAN0102_T TeslaCAN0102_T.cpp)
target_link_libraries(TeslaCAN0102_T teslacan)
set_target_properties(TeslaCAN0102_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0102_T
  COMMAND TeslaCAN0102_T)

add_executable(TeslaCAN0106_T TeslaCAN0106_T.cpp)
target_link_libraries(TeslaCAN0106_T teslacan)
set_target_properties(TeslaCAN0106_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0106_T
  COMMAND TeslaCAN0106_T)

add_executable(TeslaCAN0116_T TeslaCAN0116_T.cpp)
target_link_libraries(TeslaCAN0116_T teslacan)
set_target_properties(TeslaCAN0116_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0116_T
  COMMAND TeslaCAN0116_T)

add_executable(TeslaCAN0154_T TeslaCAN0154_T.cpp)
target_link_libraries(TeslaCAN0154_T teslacan)
set_target_properties(TeslaCAN0154_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0154_T
  COMMAND TeslaCAN0154_T)

add_executable(TeslaCAN0210_T TeslaCAN0210_T.cpp)
target_link_libraries(TeslaCAN0210_T teslacan)
set_target_properties(TeslaCAN0210_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0210_T
  COMMAND TeslaCAN0210_T)

add_executable(TeslaCAN0232_T TeslaCAN0232_T.cpp)
target_link_libraries(TeslaCAN0232_T teslacan)
set_target_properties(TeslaCAN0232_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0232_T
  COMMAND TeslaCAN0232_T)

add_executable(TeslaCAN0256_T TeslaCAN0256_T.cpp)
target_link_libraries(TeslaCAN0256_T teslacan)
set_target_properties(TeslaCAN0256_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0256_T
  COMMAND TeslaCAN0256_T)

add_executable(TeslaCAN0266_T TeslaCAN0266_T.cpp)
target_link_libraries(TeslaCAN0266_T teslacan)
set_target_properties(TeslaCAN0266_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0266_T
  COMMAND TeslaCAN0266_T)

add_executable(TeslaCAN0302_T TeslaCAN0302_T.cpp)
target_link_libraries(TeslaCAN0302_T teslacan)
set_target_properties(TeslaCAN0302_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0302_T
  COMMAND TeslaCAN0302_T)

add_executable(TeslaCAN0382_T TeslaCAN0382_T.cpp)
target_link_libraries(TeslaCAN0382_T teslacan)
set_target_properties(TeslaCAN0382_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0382_T
  COMMAND TeslaCAN0382_T)

add_executable(TeslaCAN03d2_T TeslaCAN03d2_T.cpp)
target_link_libraries(TeslaCAN03d2_T teslacan)
set_target_properties(TeslaCAN03d2_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN03d2_T
  COMMAND TeslaCAN03d2_T)

add_executable(TeslaCAN0562_T TeslaCAN0562_T.cpp)
target_link_libraries(TeslaCAN0562_T teslacan)
set_target_properties(TeslaCAN0562_T PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
add_test(NAME TeslaCAN0562_T
  COMMAND TeslaCAN0562_T)
