cmake_minimum_required(VERSION 3.20)
project(Lab1 C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS "/TC /Gz")
set(CMAKE_SHARED_LINKER_FLAGS "/DYNAMICBASE")
set(CMAKE_EXE_LINKER_FLAGS "/DYNAMICBASE")

add_definitions(-DECO_WINDOWS)
add_definitions(-D_DEBUG)
add_definitions(-DECO_DLL)
add_definitions(-DUGUID_UTILITY)
add_definitions(-DECO_WIN32)
add_definitions(-DWIN32)
add_definitions(-D_WINDOWS)
add_definitions(-D_CONSOLE)

include_directories(HeaderFiles)
include_directories(SharedFiles)
include_directories(Components/SharedFiles)
include_directories(UnitTestFiles/HeaderFiles)


include_directories(
        $ENV{ECO_FRAMEWORK}/Eco.List1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.Core1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.System1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/SharedFiles
)


add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3A
        SHARED
        SourceFiles/CEcoLab1.c
        SourceFiles/CEcoLab1Factory.c
        SharedFiles/IdEcoLab1.h
        SharedFiles/IEcoLab1.h
        HeaderFiles/CEcoLab1.h
        HeaderFiles/CEcoLab1Factory.h

        Components/SharedFiles/IEcoCalculatorY.h
        Components/SharedFiles/IEcoCalculatorX.h
        Components/SharedFiles/IdEcoCalculatorD.h
        Components/SharedFiles/IdEcoCalculatorE.h
        Components/SharedFiles/IdEcoCalculatorA.h
        Components/SharedFiles/IdEcoCalculatorB.h

        HeaderFiles/CEcoLab1ConnectionPoint.h
        HeaderFiles/CEcoLab1EnumConnectionPoints.h
        HeaderFiles/CEcoLab1EnumConnections.h

        SharedFiles/IEcoConnectionPoint.h
        SharedFiles/IEcoConnectionPointContainer.h
        SharedFiles/IEcoEnumConnectionPoints.h
        SharedFiles/IEcoEnumConnections.h
        SharedFiles/IEcoLab1Events.h

        SourceFiles/CEcoLab1ConnectionPoint.c
        SourceFiles/CEcoLab1EnumConnectionPoints.c
        SourceFiles/CEcoLab1EnumConnections.c
        )

add_executable(
        Lab1
        UnitTestFiles/SourceFiles/EcoLab3.c
        SharedFiles/IdEcoLab1.h
        SharedFiles/IEcoLab1.h
        Components/SharedFiles/IEcoCalculatorY.h
        Components/SharedFiles/IEcoCalculatorX.h
        Components/SharedFiles/IdEcoCalculatorD.h
        Components/SharedFiles/IdEcoCalculatorE.h
        Components/SharedFiles/IdEcoCalculatorA.h
        Components/SharedFiles/IdEcoCalculatorB.h
        UnitTestFiles/HeaderFiles/CEcoLab1Sink.h
        UnitTestFiles/SourceFiles/CEcoLab1Sink.c

)

target_link_libraries(
        Lab1
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000042757331.lib
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/BuildFiles/Windows/x86/StaticRelease/0000000000000000000000004D656D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000046534D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.System1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000000000100.lib
        $ENV{ECO_FRAMEWORK}/Eco.List1/BuildFiles/Windows/x86/StaticRelease/53884AFC93C448ECAA929C8D3A562281.lib
        1F5DF16EE1BF43B999A434ED38FE8F3A
)