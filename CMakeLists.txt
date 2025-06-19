cmake_minimum_required(VERSION 3.16)

set(MYNAME dolls-studio)

project(${MYNAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/../fbx202037/include)
add_compile_definitions(FBXSDK_SHARED)

find_package(Qt6 REQUIRED
  Core
  Quick)

find_package(VTK REQUIRED
    CommonCore
    CommonColor
    GUISupportQtQuick)

set(PROJECT_SOURCES
    main.cpp
    SdkLoader.cpp
    SdkLoader.h
    MyVtkItem.cpp
    MyVtkItem.h
    qml.qrc)

qt_add_executable(${MYNAME}
  MANUAL_FINALIZATION
  ${PROJECT_SOURCES}
)

qt_import_qml_plugins(${MYNAME})
qt_finalize_executable(${MYNAME})

target_link_libraries(${MYNAME}
    PRIVATE
    Qt6::Quick
    ${VTK_LIBRARIES}
    ${PROJECT_SOURCE_DIR}/../fbx202037/lib/debug/libfbxsdk.so )

vtk_module_autoinit(TARGETS ${MYNAME} MODULES ${VTK_LIBRARIES} )

include(GNUInstallDirs)
install(TARGETS ${MYNAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} )

