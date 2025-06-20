# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AES_autogen"
  "CMakeFiles\\AES_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AES_autogen.dir\\ParseCache.txt"
  )
endif()
