cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(map_reduce VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

#Main target 
add_executable(map_reduce main.cpp)
add_library(lib_map_reduce lib.cpp)

set_target_properties(map_reduce lib_map_reduce PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(lib_map_reduce 
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(map_reduce PRIVATE
    lib_map_reduce
)

if (MSVC)
    target_compile_options(map_reduce PRIVATE
        /W4
    )
    target_compile_options(lib_map_reduce PRIVATE
        /W4
    )
else ()
    target_compile_options(map_reduce PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lib_map_reduce PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS map_reduce RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()