# Help CMake to find custom Qt6 installation path
set(Qt6_DIR /usr/local/Qt-6.5.1/lib/cmake/Qt6)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()
