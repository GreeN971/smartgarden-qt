cmake_minimum_required(VERSION 3.16)

project(SmartGardenV2 VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Core)

qt_standard_project_setup()

qt_add_executable(appSmartGardenV2
    main.cpp
    resources.qrc
)
target_compile_options(appSmartGardenV2 PRIVATE "$<${gcc_like_cxx}:-Wall;-Wextra;-Wconversion;-std=c++17>"
    "$<${msvc_cxx}:/W3;/std:c++17>")

qt_add_qml_module(appSmartGardenV2
    URI SmartGardenV2
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES UI/HomeScreen/LeftSide/LeftSide.qml
    QML_FILES UI/HomeScreen/RightSide/RightSide.qml
    RESOURCES UI/Assets/thermometer.png
    RESOURCES UI/Assets/humidity.png
    RESOURCES UI/Assets/meter.png
    RESOURCES UI/Assets/water-control.png
    SOURCES data.h data.cpp
    SOURCES enviromentaldata.h enviromentaldata.cpp
    SOURCES ijsondeserialize.h ijsondeserialize.cpp
    SOURCES soilidlistmodel.h soilidlistmodel.cpp
    SOURCES SoilID.h
    SOURCES valveidlistmodel.h valveidlistmodel.cpp
    SOURCES ValveID.h
    SOURCES
    SOURCES httpclient.h httpclient.cpp
    #RESOURCES resources.qrc
)

#qt_add_resources (appSmartGardenV2
 #   FILES
 #       UI/Assets/thermometer.png
#)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSmartGardenV2 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSmartGardenV2
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include("${CMAKE_CURRENT_SOURCE_DIR}/Cmake/FetchCPM.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/Cmake/CPM/CPM.cmake")
if(NOT WIN32)
    set(CPM_LOCAL_PACKAGES_ONLY True)
endif()
CPMAddPackage(NAME curl
    GITHUB_REPOSITORY curl/curl
    VERSION 8.6.0
    GIT_TAG "curl-8_6_0"
    OPTIONS
        "BUILD_STATIC_LIBS ON"
        "BUILD_SHARED_LIBS OFF"
        "CURL_CA_PATH auto")

target_link_libraries(appSmartGardenV2
    PRIVATE Qt6::Quick Qt6::Core libcurl
)

include(GNUInstallDirs)
install(TARGETS appSmartGardenV2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
