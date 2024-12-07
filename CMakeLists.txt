cmake_minimum_required(VERSION 3.28)
project(autotech_task)

set(CMAKE_CXX_STANDARD 17)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(autotech_task
        main.cpp
        Application/Public/XY.h
        Application/Public/XYTransmitter.h
        Application/Public/XYReceiver.h
        TransportLayer/Public/TransportInterface.h
        Application/Public/Protocol.h
        Application/Public/Protocol.h
        TransportLayer/Public/TransportInterfaceFabric.h
        Utils/ThreadSafeLogger.cpp
        Utils/ThreadSafeLogger.h
        PhysicalLayerEmulator/Private/PhysicalLayerEmulator.cpp
        PhysicalLayerEmulator/Public/PhysicalLayerEmulator.h
        Utils/CommonDefs.h
        TransportLayer/Private/TransportLayerInterfaceFabric.cpp
        TransportLayer/Private/Can/CanInterface.cpp
        TransportLayer/Private/Can/CanInterface.h
        Application/Private/XYTransmitter.cpp
        Application/Private/XYReceiver.cpp
        Application/Private/XYTransceiver.cpp
        Application/Public/XYTransceiver.h
        Application/Private/XYTransmitter.cpp
)