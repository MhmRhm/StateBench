add_executable(statebench
	infrastructure.cpp
)
target_compile_options(statebench
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
target_include_directories(statebench INTERFACE
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(statebench PROPERTIES
    PUBLIC_HEADER src/infrastructure/include/infrastructure/infrastructure.h
    POSITION_INDEPENDENT_CODE 1
)
target_link_libraries(statebench PRIVATE precompiled Boost::statechart Qt6::Core "$<$<PLATFORM_ID:UNIX>:atomic>")
BuildInfo(statebench)

include(Format)
Format(statebench .)
include(Doxygen)
Doxygen(statebench src/infrastructure)
