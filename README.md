# OpenCV4 C++ Sample

## Build and Install OpenCV4

https://github.com/m3y54m/build-opencv4-in-ubuntu

## Configure project

The recommended method for configuring OpenCV-based projects
is using CMake.

```console
sudo apt install cmake
```

The basic project configurations are written in
[`CMakeLists.txt`](https://github.com/opencv/opencv/blob/master/samples/cpp/example_cmake/CMakeLists.txt)
file which will be recognized by CMake tool. In order to generate the Makefile and other files used to
build this project in a directory called `build` run these commands:

```console
mkdir -p build
cd build
cmake ..
```