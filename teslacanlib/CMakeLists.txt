add_library(teslacan SHARED TeslaCAN0102.cpp TeslaCAN0106.cpp TeslaCAN0154.cpp
  TeslaCAN0256.cpp
  canDecoder.cpp)

set_target_properties(teslacan PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(teslacan PROPERTIES OUTPUT_NAME teslacan${BUILD_POSTFIX})
