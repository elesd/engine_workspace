# Status
Abandond experimental game engine. The project had two main purpose:
 - Getting familiar with ECS (Entity Component Systems). See more about it: https://www.intel.com/content/dam/develop/external/us/en/documents/designing-a-parallel-game-engine-593584.pdf
 - Having a common graphics API on the top of DirectX and OpenGl

It got abbandond mainly because of the common graphics API. It might gonna be continues with Vulkan and DirectX
# Content
This is an experimental game engine. Currently it is under development the main goal is create a scriptable engine which can run under windows and Unix platforms, and during this time make some experience and try out some technique.

The current version uses 3 kind of windowed library. SDL, glfw and winapi. With the globalConfig.cmake one can setup which one will be used. All the dependencies are stored under the CommonLibs directory
There are 3 project currently:

1. The engine

2. A test framework, which contains some unit tests

3. A tutorial project. As a first step of the engine the goal is to 
implement a basic tutorial.
