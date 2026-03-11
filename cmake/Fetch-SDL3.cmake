include(cmake/CPM.cmake)

set(SDL_VERSION release-3.4.2)
set(SDL_TESTS OFF CACHE BOOL "Disable SDL tests")

CPMAddPackage(
        NAME SDL3
        GITHUB_REPOSITORY libsdl-org/SDL
        GIT_TAG ${SDL_VERSION}
        GIT_SHALLOW TRUE
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)