SimpleCanvas
************

Introduction
============
Yet another simple 3D OpenGl game engine

SimpleCanvas is using [Cmake](https://cmake.org/), [GLFW](https://www.glfw.org/)([GitHub](https://github.com/glfw/glfw)),  [Glad](https://glad.dav1d.de/)([GitHub](https://github.com/Dav1dde/glad)), [googletest](https://github.com/google/googletest)

License
=======

TODO

Building SimpleCanvas
=====================

Supported Platforms
-------------------

* Microsoft Windows
* Linux

Building SimpleCanvas from Scratch
----------------------------------

Linux
^^^^^

You will need to have a C++ compiler (supporting C++17), python (for [googletest](https://github.com/    google/googletest)s), [Cmake](https://cmake.org/) (supporting v3.16) and ``make`` installed.
You may also need to install following packages in order to compile

  libxrandr-dev
  libxinerama-dev
  libxcursor-dev
  libxi-dev


Init and update submodules. [GLFW](https://www.glfw.org/) and [googletest](https://github.com/google/googletest)s will be downloaded.

  $ git submodule init && git submodule update
  $ mkdir build && cd build
  $ cmake ..
  $ make

Windows
^^^^^^^

You will need to download and install a binary release of CMake. You can get
these releases from the https://cmake.org/download.
Compile with MSVC from VS 2017 or later with Visual C++ 2017 Redistributable.
