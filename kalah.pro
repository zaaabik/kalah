TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game.cpp \
    tree.cpp \
    tree_node.cpp

HEADERS += \
    game.h \
    tree.h \
    tree_node.h
