file(GLOB FILTER_UTILITY_SRCS
    "*.cpp"
)
include_directories(${CMAKE_SOURCE_DIR}/thirdParty/nlohmann)

add_library(Filter_Utility MODULE ${FILTER_UTILITY_SRCS})

install(TARGETS Filter_Utility DESTINATION ${WM_LIB_INSTALL_DIR})

if (BUILD_TESTING)
    add_subdirectory(autotests)
endif ()
