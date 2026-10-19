cmake_minimum_required(VERSION 3.16)

project(BetterClipboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED Gui Core Sql)

qt_add_executable(appBetterClipboard
    main.cpp
)

qt_add_qml_module(appBetterClipboard
    URI BetterClipboard
    VERSION 1.0
    QML_FILES
        qml/main.qml
        qml/Global.qml
    SOURCES
        include/listener.h
        include/const.h
        include/classify.h
        include/data.h
        include/database.h

        include/DataModel/datamodel.h
        include/DataModel/recentdatamodel.h
        include/DataModel/emaildatamodel.h
        include/DataModel/favoritedatamodel.h
        include/DataModel/urldatamodel.h
        include/DataModel/textdatamodel.h

        src/classify.cpp
        src/listener.cpp
        src/database.cpp
        src/datamodel.cpp
        src/recentdatamodel.cpp
        src/Emaildatamodel.cpp
        src/favoritedatamodel.cpp
        src/Textdatamodel.cpp
        src/Urldatamodel.cpp

    RESOURCES
        qml/images/header.jpg
        qml/Home/RecentPage.qml
        qml/component/SearchBar.qml
        qml/component/DataCard.qml
        qml/Home/HistoryPage.qml
        qml/Home/FavoritePage.qml

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appBetterClipboard PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appBetterClipboard
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appBetterClipboard
    PRIVATE Qt6::Quick Qt6::Gui Qt6::Core Qt6::Sql)

include(GNUInstallDirs)
install(TARGETS appBetterClipboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
