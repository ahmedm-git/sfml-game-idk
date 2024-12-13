set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# Add spdlog
add_subdirectory(deps/spdlog)

# Add CLI11
add_subdirectory(deps/CLI11)

# Gather all source files except main.cpp into a library
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(FILTER PROJECT_SOURCES EXCLUDE REGEX "main.cpp")

add_library(CMakeSFMLProjectLib STATIC ${PROJECT_SOURCES})
target_include_directories(CMakeSFMLProjectLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Explicitly add spdlog include directory to ensure headers are found
target_include_directories(CMakeSFMLProjectLib PUBLIC deps/spdlog/include deps/CLI11/include)

target_link_libraries(CMakeSFMLProjectLib PRIVATE sfml-graphics spdlog::spdlog CLI11::CLI11)

add_executable(CMakeSFMLProject src/main.cpp ${PROJECT_SOURCES})
target_link_libraries(CMakeSFMLProject PRIVATE CMakeSFMLProjectLib)

# Copy OpenAL DLL on Windows
if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
            ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll 
            $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM
    )
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(CMakeSFMLProject PRIVATE -Wall -Wextra -pedantic -g)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(CMakeSFMLProject PRIVATE /W4 /O2)
endif()

option(ENABLE_TESTING "Enable testing" OFF)
if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS CMakeSFMLProject
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
