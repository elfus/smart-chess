include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

file(GLOB smartchess_SRC
    "*.h"
    "*.cpp"
    "*.cxx"
)

find_package(PkgConfig)
pkg_check_modules (GTKMM gtkmm-3.0)

link_directories (${GTKMM_LIBRARY_DIRS})
include_directories (${GTKMM_INCLUDE_DIRS})

add_executable (smartchess ${smartchess_SRC} GRadioColorGroup.cpp GRadioColorGroup.h Util.cpp)

target_link_libraries(smartchess ${GTKMM_LIBRARIES})
