# SimpleCanvas

## Introduction
Yet another simple 3D OpenGl game engine

SimpleCanvas is using [Cmake](https://cmake.org/), [GLFW](https://www.glfw.org/)([GitHub](https://github.com/glfw/glfw)),  [Glad](https://glad.dav1d.de/)([GitHub](https://github.com/Dav1dde/glad)), [googletest](https://github.com/google/googletest)

## License

TODO

## Building SimpleCanvas

### Supported Platforms

* Microsoft Windows
* Linux

### Building SimpleCanvas from Scratch

Before build, make sure that you have installed latest graphic card drivers that supports OpenGL 4.5 or later.

If you are using laptop with a dual grahic cards(e.g Intel and Nvidia), you can use this [INSTRUCTION](https://www.linuxbabe.com/desktop-linux/switch-intel-nvidia-graphics-card-ubuntu) to check how to use Nvidia.

Building SimpleCanvas in virtualized systems like Linux on VirtualBox or WSL(2) may not work since they not support such OpenGL versions.

#### Linux

You will need to have a C++ compiler (supporting C++17), python (for [googletest](https://github.com/google/googletest)s), [Cmake](https://cmake.org/) (supporting v3.16) and ``make`` installed.
You may also need to install following packages in order to compile

* libxrandr-dev
* libxinerama-dev
* libxcursor-dev
* libxi-dev
* libgl1-mesa-dev

```
  $ sudo apt-get install libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev -y
```

Init and update submodules. [GLFW](https://www.glfw.org/) and [googletest](https://github.com/google/googletest)s will be downloaded.
Then run cmake and build with make:

```
  $ git submodule init && git submodule update
  $ mkdir build && cd build
  $ cmake ..
  $ make -j
```

You can also specify the build type:

```
  $ cmake -DCMAKE_BUILD_TYPE=Debug ..
```
  or
```
  $ cmake -DCMAKE_BUILD_TYPE=Release ..
```

#### Windows

You will need to download and install a binary release of [CMake](https://cmake.org/download) and [python](https://www.python.org/downloads/windows/).
Generate build system for Visual Studio 15 2017 or later.
Make sure that SimpleGame is "Set as StartUp Projekt"
If you do not have any enviornment, you can use easy and lightweight Visual Studio Code. You can follow this [INSTRUCTION](https://code.visualstudio.com/docs/cpp/config-msvc).
