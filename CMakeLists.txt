cmake_minimum_required(VERSION 3.16)
project(frontend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

add_library(sqlite3 STATIC third_party/sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC third_party/sqlite3)

add_executable(appMyApp
    main.cpp

    backend/src/SystemMonitor.cpp
    backend/src/ProcessTracker.cpp
    backend/src/EnergyEstimator.cpp
    backend/src/ContextSwitchAnalyzer.cpp
    backend/src/DataLogger.cpp

    qtbridge/MonitorController.cpp
    qtbridge/ProcessModel.cpp
    qtbridge/EnergyController.cpp
)

target_include_directories(appMyApp PRIVATE
    backend/include
    backend/src
    qtbridge
    third_party/sqlite3
)

add_executable(carbonqt
    carbonqt_cli.cpp

    backend/src/SystemMonitor.cpp
    backend/src/ProcessTracker.cpp
    backend/src/EnergyEstimator.cpp
    backend/src/ContextSwitchAnalyzer.cpp
    backend/src/DataLogger.cpp
)

qt_add_qml_module(appMyApp
    URI MyApp
    VERSION 1.0
    RESOURCE_PREFIX /qt/qml

    QML_FILES
        Main.qml
        pages/Dashboard.qml
        pages/Processes.qml
        pages/EnergyEstimator.qml
        components/SidebarButton.qml
        components/StatCard.qml
        components/DoughnutStat.qml
        components/PidThreadsChart.qml
        components/TableHeader.qml
        components/RingChart.qml
        components/Theme.qml
    RESOURCES
        assets/icons/refresh.svg
)

target_link_libraries(appMyApp
    PRIVATE Qt6::Quick sqlite3
)

target_include_directories(carbonqt PRIVATE
    backend/include
    backend/src
    third_party/sqlite3
)

target_link_libraries(carbonqt
    Qt6::Core
    sqlite3
)
