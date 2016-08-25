cmake_minimum_required(VERSION 2.8.3)
project(logCenter)

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF) 


find_package(Threads)
find_package( Boost  REQUIRED COMPONENTS system    regex   )


include_directories(${Boost_INCLUDE_DIR})

FILE(GLOB_RECURSE SRC_LIST "src/*.cpp" )  
add_executable(logCenter
  ${SRC_LIST}
)

set(CC_PARAMS "-std=c++11 -Wall -pedantic -Winline -Wsign-conversion -Wsuggest-attribute=const -Wstrict-overflow=5 -Wunsafe-loop-optimizations -Wextra -Wcast-align -Wconversion -Wdisabled-optimization -fasynchronous-unwind-tables -fdiagnostics-show-option -Werror=format -Werror=return-type 
 -Werror=return-local-addr -Werror=write-strings -Wshadow -Wno-unused-parameter   -ggdb3")
 
target_include_directories (logCenter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


SET_TARGET_PROPERTIES(logCenter PROPERTIES COMPILE_FLAGS  ${CC_PARAMS})


target_link_libraries(logCenter
  ${Boost_SYSTEM_LIBRARY}     
   ${Boost_REGEX_LIBRARY}
   ${Boost_FILESYSTEM_LIBRARY}
   ${CMAKE_THREAD_LIBS_INIT}
)



