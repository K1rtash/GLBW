cmake_minimum_required(VERSION 3.15)
project(GLBW VERSION 0.1.0)

option(GLBW_BUILD_DEMO "Build demo binaries" ON)

# ----------------------------- 
# Source files 
# -----------------------------
file(GLOB SRC_FILES "src/*.c")
set(GLAD_SRC_FILES "third-party/glad/src/glad.c")

add_library(${PROJECT_NAME} 
    ${SRC_FILES} 
    ${GLAD_SRC_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/third-party/glad/include>
    $<INSTALL_INTERFACE:include>
)

# ----------------------------- 
# GLFW3
# -----------------------------
if(DEFINED GLFW_DIR) 
    list(APPEND CMAKE_PREFIX_PATH "${GLFW_DIR}") 
endif()

find_package(glfw3 QUIET)

if(NOT glfw3_FOUND) 
    message(STATUS "GLFW not found, using FetchContent") 
    include(FetchContent) 

    set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE) 
    set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE) 

    FetchContent_Declare(
        glfw 
        GIT_REPOSITORY https://github.com/glfw/glfw.git 
        GIT_TAG latest 
    ) 
    FetchContent_MakeAvailable(glfw) 
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# ----------------------------- 
# OpenGL
# -----------------------------
if(WIN32)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
endif()

# ----------------------------- 
# Demo
# -----------------------------
if(${GLBW_BUILD_DEMO})
    file(GLOB DEMO_SRC_FILES "demo/*.c")

    add_executable(glbw_demo ${DEMO_SRC_FILES})

    target_link_libraries(glbw_demo PRIVATE ${PROJECT_NAME})
    target_include_directories(glbw_demo PRIVATE ${PROJECT_SOURCE_DIR}/include)
endif()

# ----------------------------- 
# Install
# -----------------------------
include(CMakePackageConfigHelpers)

install(TARGETS GLBW 
    EXPORT GLBWTargets
    ARCHIVE DESTINATION lib 
    LIBRARY DESTINATION lib 
    RUNTIME DESTINATION bin 
) 

install(DIRECTORY include/ DESTINATION include)

install(EXPORT GLBWTargets 
    FILE GLBWTargets.cmake 
    NAMESPACE GLBW:: 
    DESTINATION lib/cmake/GLBW 
)

write_basic_package_version_file( 
    "${CMAKE_CURRENT_BINARY_DIR}/GLBWConfigVersion.cmake" 
    VERSION ${PROJECT_VERSION} 
    COMPATIBILITY SameMajorVersion 
) 

install(FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GLBWConfig.cmake" 
    "${CMAKE_CURRENT_BINARY_DIR}/GLBWConfigVersion.cmake" 
    DESTINATION lib/cmake/GLBW 
)