
# Location of the GLM distribution
GLM_INCLUDE_PATH = /Users/daw/.local/glm

CONFIG += debug testcase c++11

TEMPLATE = app
win32 {
  # Generate a Visual Studio project on Windows.
  TEMPLATE = vcapp
}

QT += gui widgets testlib

# Location for all object and MOC files
MOC_DIR=build
OBJECTS_DIR=build

# Name and directory of target executable
DESTDIR = .
TARGET = raycast

# Add GLM to include path
INCLUDEPATH += /Users/Rebecca/glm

# All source files
SOURCES += src/*.cpp
HEADERS += src/*.h
