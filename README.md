# particle-system-webgl

<p align="center">
      <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="cppLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/OpenGL-FFFFFF?style=for-the-badge&logo=opengl" alt="openglLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/190315147-ec9dc33f-0090-4f0d-98ab-514eb1463e01.png" alt="glfwLogo" style="height:60px;"/>
</p>

## TODO

- [ ] Parallel particle update (OpenMP) ?
- [ ] Put the UI in an init location

## Description

This is a particle system written in C++ and compiled to WebGL using
Emscripten. It is a port of my particle system written in C++ and OpenGL which can be
found [here](https://github.com/Im-Rises/Particlesystem).

## 🚀🚀[you can try the webgl build online by clicking here](https://im-rises.github.io/particle-system-webgl/) 🚀🚀

## Images and Video

[![Watch the video](https://user-images.githubusercontent.com/59691442/216751976-c06c492d-5dfb-466c-afe9-ec44e94e5db9.png)](https://www.youtube.com/watch?v=h5X1RaElC7Y)

[![Watch the video](https://user-images.githubusercontent.com/59691442/216753254-f3315a71-f073-420e-b4e3-86a024913683.png)](https://www.youtube.com/watch?v=h5X1RaElC7Y)

Click on the images to watch the video.

## Building

To build the project, you need to use a UNIX system, like Ubuntu or if you're on Windows you can use WSL.
Then you have to install Emscripten. You can find
instructions on how to install Emscripten here:  
<https://emscripten.org/docs/getting_started/downloads.html>

You also need to have CMake and make installed. You can find instructions on how to
install CMake here:  
<https://cmake.org/install/>

Make can be installed by running this command in the terminal:

```bash
sudo apt install make
```

Once you have Emscripten and CMake installed run this command in the project root directory:

```bash
emcmake cmake .
```

Then run this command in the same directory:

```bash
emmake make
```

## To test the website locally

To test the website locally, you need to have Python installed. You can find instructions on how to install Python here:

<https://www.python.org/downloads/>

Once you have Python installed, run this command in the project build directory:

```bash
python -m http.server
```

Then open your browser and go to this address:

<http://localhost:8000/>

## Controls

The speed and some parameters can be modified directly in the ImGui windows.

| Action              | Key                                 |
|---------------------|-------------------------------------|
| Translate camera    | WASD (← → ↑ ↓)                      |
| Pause/Resume        | P                                   |
| Move up/down camera | SPACE/SHIFT                         |
| Rotate camera       | Right Mouse Button + Mouse movement |
| Fullscreen          | F11                                 |
| Drag particles      | Left Mouse Button + Mouse movement  |

The keybinding is made for a QWERTY keyboard.

## GitHub Actions

This project uses GitHub Actions to build the project and deploy it to GitHub

[![CodeQL](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/codeql.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/codeql.yml)
[![CMake](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/cmake.yml)
[![flawfinder](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/flawfinder.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/flawfinder.yml)
[![cpp-linter](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/cpp-linter.yml/badge.svg?branch=main)](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/cpp-linter.yml)
[![Emscripten-CMake](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/emscripten-cmake.yml/badge.svg)](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/emscripten-cmake.yml)
[![Emscripten-Publish](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/emscripten-publish.yml/badge.svg)](https://github.com/Im-Rises/particle-system-webgl/actions/workflows/emscripten-publish.yml)

The project is set with a set of different scripts:

- CodeQL: This script is used to check the code for security issues.
- CMake: This script is used to build the project.
- Cpp Cmake Publish: This script is used to publish the project on GitHub.
- Flawfinder: This script is used to check the code for security issues.
- Microsoft C++ Code Analysis: This script is used to check the code for security issues.
- Cpp Linter: This script is used to check the code for security issues.
- Emscripten CMake: This script is used to test build of the project using Emscripten toolchain.
- Emscripten-Publish: This script build to webgl and publish the project on GitHub Pages.

## Libraries

glfw:  
<https://www.glfw.org/docs/latest/>

glm:  
<https://glm.g-truc.net/0.9.9/index.html>

glad:  
<https://glad.dav1d.de/>

stb (stb_image):  
<https://github.com/nothings/stb/blob/master/stb_image.h>

Dear ImGui:  
<https://github.com/ocornut/imgui>

OpenGL:  
<https://www.opengl.org/>

emscripten:  
<https://emscripten.org/docs/getting_started/downloads.html>

bin2c:  
<https://sourceforge.net/projects/bin2c/files/latest/download>  

## Documentation

learnopengl (OpenGL tutorial):  
<https://learnopengl.com/In-Practice/2D-Game/Particles>

unrealistic.dev (Change CMake working directory):  
<https://unrealistic.dev/posts/setting-debug-parameters-with-cmake-tools-for-visual-studio>

OpenGL ES 2.0 Reference Pages:  
<https://www.khronos.org/registry/OpenGL-Refpages/es2.0/>

Wikipedia (OpenGL versions):
<https://en.wikipedia.org/wiki/OpenGL_Shading_Language>

## Contributors

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/particle-system-webgl)](https://github.com/Im-Rises/particle-system-webgl/graphs/contributors)
