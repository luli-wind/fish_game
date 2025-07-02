cmake_minimum_required(VERSION 3.16)

project(fish VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
qt_add_resources(QRC_FILES "Resources/resources.qrc")
set(PROJECT_SOURCES
        main.cpp
        mainwidget.cpp
        mainwidget.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(fish
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        easyview.h easyview.cpp
        illustration.h illustration.cpp
        fish_illustration/clownfish_illustration.h fish_illustration/clownfish_illustration.cpp
        qfish/qfish.cpp qfish/qfish.h
        qfish/clownfish.cpp qfish/clownfish.h
        qfish/rays.cpp qfish/rays.h
        qfish/turtle.cpp qfish/turtle.h
        qpixmapitem/qbullet.cpp qpixmapitem/qbullet.h
        qpixmapitem/qgun.cpp qpixmapitem/qgun.h
        qpixmapitem/qnet.cpp qpixmapitem/qnet.h
        qpixmapitem/qpixmapitem.cpp qpixmapitem/qpixmapitem.h
        fish_illustration/goldenfish_illustration.h fish_illustration/goldenfish_illustration.cpp
        fish_illustration/pufferfish_illustration.h fish_illustration/pufferfish_illustration.cpp
        fish_illustration/turtle_illustration.h fish_illustration/turtle_illustration.cpp
        fish_illustration/rays_illustration.h fish_illustration/rays_illustration.cpp
        fish_illustration/lanternfish_illustration.h fish_illustration/lanternfish_illustration.cpp
        fish_illustration/shark_illustration.h fish_illustration/shark_illustration.cpp
        fish_illustration/goldenshark_illustration.h fish_illustration/goldenshark_illustration.cpp
        qpixmapitem/qcoin.h qpixmapitem/qcoin.cpp
        qpixmapitem/qcoincounter.h qpixmapitem/qcoincounter.cpp
        shop.h shop.cpp
        cannonmanager.h cannonmanager.cpp
        qfish/goldenfish.h qfish/goldenfish.cpp
        qfish/lanternfish.h qfish/lanternfish.cpp
        qfish/pufferfish.h qfish/pufferfish.cpp
        qfish/shark.h qfish/shark.cpp
        qfish/goldenshark.h qfish/goldenshark.cpp



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET fish APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(fish SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(fish
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(fish PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.fish)
endif()
set_target_properties(fish PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS fish
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(fish)
endif()
