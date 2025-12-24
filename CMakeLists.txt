cmake_minimum_required(VERSION 3.15)
project(GLBW LANGUAGES C VERSION 0.1.0)

# ----------------------------- 
# Options
# -----------------------------
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
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        glfw 
        GIT_REPOSITORY https://github.com/glfw/glfw.git 
        GIT_TAG latest 
    ) 
    FetchContent_MakeAvailable(glfw) 
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERFACE_LINK_LIBRARIES "" 
    INTERFACE_LINK_LIBRARIES_DEBUG "" 
    INTERFACE_LINK_LIBRARIES_RELEASE ""
)

set_property(TARGET ${PROJECT_NAME} PROPERTY EXPORT_LINK_INTERFACE_LIBRARIES OFF)

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

    add_executable(${PROJECT_NAME}demo ${DEMO_SRC_FILES})

    target_link_libraries(${PROJECT_NAME}demo PRIVATE ${PROJECT_NAME})
    target_include_directories(${PROJECT_NAME}demo PRIVATE ${PROJECT_SOURCE_DIR}/include)
endif()

# -----------------------------
# Install
# -----------------------------
include(CMakePackageConfigHelpers)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY docs/ DESTINATION docs)

# Export targets
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

# Generate version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install config + version
install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)
