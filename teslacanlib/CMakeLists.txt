add_library(teslacan SHARED TeslaCAN0102.cpp TeslaCAN0106.cpp TeslaCAN0116.cpp
  TeslaCAN0154.cpp TeslaCAN0210.cpp TeslaCAN0232.cpp TeslaCAN0256.cpp
  TeslaCAN0266.cpp TeslaCAN0302.cpp TeslaCAN0382.cpp TeslaCAN03d2.cpp
  TeslaCAN0562.cpp TeslaCAN06f2.cpp
  canDecoder.cpp)

set_target_properties(teslacan PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(teslacan PROPERTIES OUTPUT_NAME teslacan${BUILD_POSTFIX})
