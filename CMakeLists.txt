cmake_minimum_required(VERSION 3.22)
Include(FetchContent)
set(CMAKE_GENERATOR_PLATFORM Win32)
cmake_policy(SET CMP0048 NEW)

project(WotLKExtensions)

add_subdirectory(Patcher)
add_subdirectory(WotLKExtensions)

# Made by xidk
# Optional: Auto-copy addon to WoW Interface\AddOns directory
set(WOW_CLIENT_PATH "" CACHE PATH "Path to WoW 3.3.5a client directory (optional)")

if(WOW_CLIENT_PATH AND EXISTS "${WOW_CLIENT_PATH}")
    set(ADDON_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/DevelopmentAddon")
    set(ADDON_DEST_DIR "${WOW_CLIENT_PATH}/Interface/AddOns/DevelopmentAddon")
    
    if(EXISTS "${ADDON_SOURCE_DIR}")
        # Create a custom target that copies the addon folder
        add_custom_target(CopyAddon ALL
            COMMAND ${CMAKE_COMMAND} -E make_directory "${WOW_CLIENT_PATH}/Interface/AddOns"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${ADDON_SOURCE_DIR}" "${ADDON_DEST_DIR}"
            COMMENT "Copying DevelopmentAddon to ${ADDON_DEST_DIR}"
            VERBATIM
        )
        message(STATUS "Addon auto-copy enabled: DevelopmentAddon will be copied to ${ADDON_DEST_DIR}")
    endif()
endif()
