cmake_minimum_required(VERSION 3.15)

project(ezmorib-dehash LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIRECTORY ${${PROJECT_NAME}-source_SOURCE_DIR}/include)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
	main.cpp
	ezmorib-dehash/Actions/Hasher.cpp
	ezmorib-dehash/Assets/Data.qrc
	ezmorib-dehash/Assets/Images.qrc
	ezmorib-dehash/Log/BasicLogEvent.cpp
	ezmorib-dehash/Log/Logger.cpp
	ezmorib-dehash/Utilities/MessageBoxHelper.cpp
	ezmorib-dehash/Windows/About/AboutWindow.cpp
	ezmorib-dehash/Windows/About/AboutWindow.ui
	ezmorib-dehash/Windows/Log/LogWindow.cpp
	ezmorib-dehash/Windows/Log/LogWindow.ui
	ezmorib-dehash/Windows/MainWindow.cpp
	ezmorib-dehash/Windows/MainWindow.ui
	${INCLUDE_DIRECTORY}/ezmorib-dehash/Windows/About/AboutWindow.hpp
	${INCLUDE_DIRECTORY}/ezmorib-dehash/Windows/Log/LogWindow.hpp
	${INCLUDE_DIRECTORY}/ezmorib-dehash/Windows/MainWindow.hpp
)

qt_add_executable(${PROJECT_NAME}
	MANUAL_FINALIZATION
	${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORY})
