cmake_minimum_required(VERSION 3.16)

project(SmartGardenV2 VERSION 0.1 LANGUAGES CXX C)

include("${CMAKE_CURRENT_SOURCE_DIR}/Cmake/FetchCPM.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/Cmake/CPM/CPM.cmake")
if(NOT WIN32)
    set(CPM_LOCAL_PACKAGES_ONLY True)
endif()

CPMAddPackage(NAME CURL
    GITHUB_REPOSITORY curl/curl
    VERSION 8.6.0
    GIT_TAG "curl-8_6_0"
    OPTIONS
        "BUILD_STATIC_LIBS ON"
        "BUILD_SHARED_LIBS OFF"
        "BUILD_TESTING OFF"
        "BUILD_CURL_EXE OFF"
        "CURL_DISABLE_INSTALL ON"
        "CURL_CA_PATH auto")

#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Core)

qt_standard_project_setup()

qt_add_executable(SmartGardenV2
    main.cpp
)

target_compile_options(SmartGardenV2 PRIVATE "$<${gcc_like_cxx}:-Wall;-Wextra;-Wconversion;-std=c++17>"
    "$<${msvc_cxx}:/W3;/std:c++17>")

qt_add_qml_module(SmartGardenV2
    URI SmartGardenV2
    VERSION 1.0
    SOURCES data.h data.cpp
    SOURCES enviromentaldata.h enviromentaldata.cpp
    SOURCES Context.h Context.cpp
    SOURCES soilidlistmodel.h soilidlistmodel.cpp
    SOURCES SoilID.h
    SOURCES valveidlistmodel.h valveidlistmodel.cpp
    SOURCES ValveID.h
    SOURCES httpclient.h httpclient.cpp
    SOURCES provider.h provider.cpp
    SOURCES worker.h worker.cpp
    RESOURCES qml.qrc


)

#qt_add_resources (appSmartGardenV2
 #   FILES
 #       UI/Assets/thermometer.png
#)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(SmartGardenV2 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSmartGardenV2
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(WIN32)
    target_link_libraries(SmartGardenV2
        PRIVATE Qt6::Quick Qt6::Core libcurl
    )
else()
    target_link_libraries(SmartGardenV2
        PRIVATE Qt6::Quick Qt6::Core CURL::libcurl
    )
endif()

include(GNUInstallDirs)
install(TARGETS SmartGardenV2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


qt_generate_deploy_app_script(TARGET SmartGardenV2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
    NO_TRANSLATIONS
)
install(SCRIPT ${deploy_script})

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME smartgarden)
set(CPACK_PACKAGE_VENDOR green)
set(CPACK_GENERATOR "ZIP")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/installers/${CPACK_GENERATOR}")

#this must be a last entry in this file
include(CPack)
