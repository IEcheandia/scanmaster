set(plugin_SRCS
    main.cpp 
    postProcessing.cpp
    postProcessingController.cpp
    postProcessingCommandServer.cpp
)
#qt5_add_resources(plugin_SRCS precitecpostprocessingcomponentplugin.qrc)

add_library(precitecpostprocessingcomponentplugin MODULE ${plugin_SRCS})
set_target_properties(precitecpostprocessingcomponentplugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../qml/precitec/gui/components/postProcessing/")
target_link_libraries(precitecpostprocessingcomponentplugin
    Qt5::Core
    Qt5::Concurrent
    Qt5::Quick
    Precitec::precitecplotter
)

# copy qml files to build dir
# required for executing from build directory
#configure_file(qml/qmldir "${CMAKE_CURRENT_BINARY_DIR}/../qml/precitec/gui/components/postProcessing/qmldir" COPYONLY)

install(TARGETS precitecpostprocessingcomponentplugin DESTINATION ${WM_LIB_INSTALL_DIR}/plugins/qml/precitec/gui/components/postProcessing)
install(FILES qml/qmldir DESTINATION ${WM_LIB_INSTALL_DIR}/plugins/qml/precitec/gui/components/postProcessing)


#if (Qt5Test_FOUND)
#    add_subdirectory(autotests)
#endif()
