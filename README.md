This is an experimental game engine. Currently it is under development the main goal is create a scriptable engine which can run under windows and Unix platforms, and during this time make some experience and try out some technique.

The current version uses 3 kind of windowed library. SDL, glfw and winapi. With the globalConfig.cmake one can setup which one will be used. All the dependencies are stored under the CommonLibs directory
There are 3 project currently:

1. The engine

2. A test framework, which contains some unit tests

3. A tutorial project. As a first step of the engine the goal is to 
implement a basic tutorial.