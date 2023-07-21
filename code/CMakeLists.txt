cmake_minimum_required (VERSION 3.10)

#这两行的路径改成自己所需使用的编译器所在的路径
set (CMAKE_C_COMPILER "C:/Qt/Tools/mingw1120_64/bin/gcc.exe")
set (CMAKE_CXX_COMPILER "C:/Qt/Tools/mingw1120_64/bin/g++.exe")

project (BNB)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SRC_LIST "main.cpp"
	"app/bombapp.cpp"
	"app/bombapp.h"
	"view/mainwindow.cpp"
	"view/mainwindow.ui"
	"view/mainwindow.h"
	"viewmodel/viewmodel.cpp"
	"viewmodel/viewmodel.h"
	"viewmodel/command/propcommand.cpp"
	"viewmodel/command/propcommand.h"
	"viewmodel/command/playercommand.cpp"
	"viewmodel/command/playercommand.h"
	"common/block.h"
	"common/character.h"
	"common/map.h"
	"common/prop.h"
        "common/weapon.h"
	)



    qt_add_executable(BNB
        MANUAL_FINALIZATION
        ${SRC_LIST}
    )

target_link_libraries(BNB PRIVATE Qt6::Widgets)


