cmake_minimum_required(VERSION 2.8.3)
project(logging)

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF) 


find_package(Threads)
find_package( Boost  COMPONENTS system filesystem date_time thread regex log REQUIRED )


FILE(GLOB_RECURSE SRC_LIST "filterListen/*.cpp"  "logSetting/*.cpp" "src/*.cpp")
add_library(logClientLibrary SHARED
  ${SRC_LIST}
)
  
add_executable(logClientTest
  test/test.cpp
)

set(CC_PARAMS "-std=c++11  -pedantic -Winline -Wsign-conversion -Wsuggest-attribute=const -Wstrict-overflow=5 -Wunsafe-loop-optimizations -Wextra -Wcast-align -Wconversion -Wdisabled-optimization -fasynchronous-unwind-tables -fdiagnostics-show-option -Werror=format -Werror=return-type 
 -Werror=return-local-addr -Werror=write-strings -Wshadow -Wno-unused-parameter   -ggdb3")
 
target_include_directories (logClientLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/logSetting ${CMAKE_CURRENT_SOURCE_DIR}/filterListen ${CMAKE_CURRENT_SOURCE_DIR})


SET_TARGET_PROPERTIES(logClientLibrary PROPERTIES COMPILE_FLAGS  ${CC_PARAMS})
SET_TARGET_PROPERTIES(logClientTest PROPERTIES COMPILE_FLAGS ${CC_PARAMS})


target_link_libraries(logClientLibrary
  ${Boost_SYSTEM_LIBRARY}   
   ${Boost_THREAD_LIBRARY}
   ${Boost_DATATIME_LIBRARY}
   ${Boost_REGEX_LIBRARY}
   ${Boost_FILESYSTEM_LIBRARY}
   ${Boost_LOG_LIBRARY}
   ${CMAKE_THREAD_LIBS_INIT}
)

target_link_libraries(logClientTest
 logClientLibrary
)

