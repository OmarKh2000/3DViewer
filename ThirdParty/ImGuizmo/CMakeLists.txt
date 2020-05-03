cmake_minimum_required (VERSION 3.11)
 
project (ImGuizmo C CXX)
# Collect headers into the variable HEADER_FILES
file (GLOB HEADER_FILES "ImGuizmo/*.h")
# Collect sources into the variable SOURCE_FILES
file (GLOB SOURCE_FILES "ImGuizmo/*.cpp")
# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
# source_group("" FILES ${SOURCE_FILES})
source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Header Files" FILES ${HEADER_FILES})
include_directories("ImGuizmo")
# Set Properties->General->Configuration Type to Application(.exe)
# Creates app.exe with the listed sources (main.cpp)
# Adds sources to the Solution Explorer
add_library (${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
# Creates a folder "ImGuizmo" and adds target 
# project (app.vcproj) under it
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${PROJECT_NAME})
