file(GLOB MOD_ANALYZER_SRCS
    "src/*.cpp"
)

add_library(Mod_Analyzer SHARED ${MOD_ANALYZER_SRCS})
target_link_libraries(Mod_Analyzer
    PUBLIC
        Analyzer_Interface
        Interfaces
        ${POCO_LIBS}
)

install(TARGETS Mod_Analyzer DESTINATION ${WM_LIB_INSTALL_DIR})
