qtTestCase(
    NAME
        testDbServer
    SRCS
        testDbServer.cpp
        ../src/dbServer.cpp
    LIBS
        Interfaces
        Mod_Storage
        ${POCO_LIBS}
        fliplib
        Qt5::Concurrent
        Precitec::precitecusermanagement
        Precitec::precitecplotter
)

qtTestCase(
    NAME
        testStorageUpdateServer
    SRCS
        testStorageUpdateServer.cpp
        ../src/storageUpdateServer.cpp
        ../src/dbServer.cpp
    LIBS
        Mod_Storage
        Interfaces
        ${POCO_LIBS}
        fliplib
)

qtTestCase(
    NAME
        testDeviceServer
    SRCS
        testDeviceServer.cpp
        ../src/deviceServer.cpp
    LIBS
        Interfaces
        System
        ${POCO_LIBS}
)
target_include_directories(testDeviceServer BEFORE PRIVATE ./)
