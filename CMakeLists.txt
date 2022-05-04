cmake_minimum_required(VERSION 3.5)

project(libhv)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)



set(LIBHV_SRCDIRS ${CMAKE_SOURCE_DIR})

include_directories(${LIBHV_SRCDIRS}/base)

file(GLOB LIBHV_SRC_C_FILSE ${LIBHV_SRCDIRS}/base/*.c)
file(GLOB LIBHV_SRC_CPP_FILSE ${LIBHV_SRCDIRS}/base/*.cpp)

set(LIBHV_SRCS ${LIBHV_SRC_C_FILSE} ${LIBHV_SRC_CPP_FILSE})

message(status ">>> ${CMAKE_BINARY_DIR}")
add_library(hv_static STATIC ${LIBHV_SRCS})

#为hv_static库增加 HV_STATICLIB 宏
target_compile_definitions(hv_static PRIVATE HV_STATICLIB)
#指定编译给定目标时要使用的包含目录或目标。切目标必须由 add_executable() or add_library()创建
target_include_directories(hv_static PRIVATE ${LIBHV_SRCDIRS})
# TARGETS 指定目标为hv_static, DESTINATION 指定安装路径，需要执行make install才会执行安装
install(TARGETS hv_static DESTINATION ${CMAKE_BINARY_DIR}/lib)
add_custom_target(libhv_static DEPENDS hv_static)

set(HV_LIBRARIES hv_static CACHE INTERNAL "link hv libraries")
#file(INSTALL ${LIBHV_HEADERS} DESTINATION include/hv)
#install(FILES ${LIBHV_HEADERS} DESTINATION include/hv)

add_subdirectory(maintest)
#将etc文件夹安装到${CMAKE_BINARY_DIR}
#file(INSTALL etc DESTINATION ${CMAKE_BINARY_DIR})
#file(INSTALL etc DESTINATION ${CMAKE_BINARY_DIR}/bin)
#file(INSTALL etc DESTINATION ${CMAKE_BINARY_DIR}/examples)