add_custom_target(systemConfigurationQml
    COMMAND /bin/bash ${CMAKE_CURRENT_SOURCE_DIR}/generateSystemConfiguration.sh ${CMAKE_SOURCE_DIR}/Interfaces/include/common/systemConfiguration.h ${CMAKE_CURRENT_BINARY_DIR}/systemConfigurationQml.h
    BYPRODUCTS systemConfigurationQml.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_library(precitecweldmasterguigeneral SHARED
    fileSystemNameValidator.cpp
    guiConfiguration.cpp
    languageSupport.cpp
    weldmasterPaths.cpp
    removableDevicePaths.cpp
)

target_link_libraries(precitecweldmasterguigeneral PUBLIC
    Qt5::Gui
    Qt5::Concurrent
    Precitec::precitecusermanagement
)

set(PLUGIN_SOURCES
    main.cpp
    systemConfigurationQml.cpp
)
qt_wrap_cpp(PLUGIN_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/systemConfigurationQml.h TARGET precitecweldmasterguigeneralplugin DEPENDS systemConfigurationQml)
add_library(precitecweldmasterguigeneralplugin MODULE ${PLUGIN_SOURCES})
set_target_properties(precitecweldmasterguigeneralplugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../qml/precitec/gui/general/")
target_link_libraries(precitecweldmasterguigeneralplugin
    Qt5::Quick
    precitecweldmasterguigeneral
)

install(TARGETS precitecweldmasterguigeneral DESTINATION ${WM_LIB_INSTALL_DIR})
install(TARGETS precitecweldmasterguigeneralplugin DESTINATION ${WM_LIB_INSTALL_DIR}/plugins/qml/precitec/gui/general)
install(FILES qmldir DESTINATION ${WM_LIB_INSTALL_DIR}/plugins/qml/precitec/gui/general)

if (CPPUNIT_FOUND)
    add_subdirectory(autotests)
endif()
