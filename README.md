# CPPND: Capstone Project - Pixel Asteroids

## Intro

This game is based on SnakeGame from https://github.com/udacity/CppND-Capstone-Snake-Game.
This game is like [Asteroids](<https://en.wikipedia.org/wiki/Asteroids_(video_game)>) but pixelized.

Space ship positioned in a limited space where asteroid are constandtly appearing in random places.
Objective is to **destroy asteroids** as much as you can.

Use keyboard arrow keys to navigate and space to shoot.

## Folder and class structures

```
.
├── cmake
│   └── FindSDL2_image.cmake
├── CMakeLists.txt
├── README.md
└── src
    ├── asteroid.cpp
    ├── asteroid.h
    ├── controller.cpp
    ├── controller.h
    ├── direction.cpp
    ├── direction.h
    ├── game.cpp
    ├── game.h
    ├── main.cpp
    ├── point.cpp
    ├── point.h
    ├── renderer.cpp
    ├── renderer.h
    ├── ship.cpp
    └── ship.h
```

`main` initializes `Renderer`, `Controller` and `Game` classes. `Renderer` is working with graphics, `Controller` - with user inputs, `Game` - with game logic. In `Game.Run`(main enrty point) there are two threads:

- `thead_asteroids` - additional thread is started to add more asteriods when user destroy at least one
- `main`/`current` - checks user input, updates game logic and state, and renders graphics

Other classes:

- `Point` class represents point with `x` and `y` on a game field.
- `Direction` enum class represents direction where asteroid/ship/bullet can go.
- `Asteroid` class represents asteroid with `Point`, `Direction`, `id` and `is_destroyer`, `is_destroyer` is boolean flag to mark asteroid which hit the ship.
- `Ship` class represents ship on game field. Ship can move around, change direction and shoot bullets. Bullets are represented with `Bullet` class.
  - `Bullet` class represents bullet point on game field and defined with `Point` and `Direction`.

## Rubric

### README

| Criteria                                                           | Comment             |
| ------------------------------------------------------------------ | ------------------- |
| A README with instructions is included with the project            | Check `./README.md` |
| The README indicates which project is chosen.                      | Check `./README.md` |
| The README includes information about each rubric point addressed. | Check `./README.md` |

### Compiling and Testing

| Criteria                             | Comment                                        |
| ------------------------------------ | ---------------------------------------------- |
| The submission must compile and run. | Check "Basic Build Instructions" `./README.md` |

### Loops, Functions, I/O

| Criteria                                                                                       | Comment                                                 |
| ---------------------------------------------------------------------------------------------- | ------------------------------------------------------- |
| The project demonstrates an understanding of C++ functions and control structures.             | Check `Game::Run` in `src/game.cpp`                     |
| The project reads data from a file and process the data, or the program writes data to a file. | Check `main` in `src/main.cpp`                          |
| The project accepts user input and processes the input.                                        | Check `Controller::HandleInput` in `src/controller.cpp` |

### Object Oriented Programming

| Criteria                                                                         | Comment                  |
| -------------------------------------------------------------------------------- | ------------------------ |
| The project uses Object Oriented Programming techniques.                         | Check `Ship` class       |
| Classes use appropriate access specifiers for class members.                     | Check `Ship` class       |
| Class constructors utilize member initialization lists.                          | Check `Ship` class       |
| Classes abstract implementation details from their interfaces.                   | Check `Ship` class       |
| Classes encapsulate behavior.                                                    | Check `Ship` class       |
| Classes follow an appropriate inheritance hierarchy.                             | Check `Ship` class       |
| Overloaded functions allow the same function to operate on different parameters. | Check `Ship` class       |
| Derived class functions override virtual base class functions.                   | Check `Ship` class       |
| Templates generalize functions in the project.                                   | Check `Ship::IsOnBorder` |

### Memory Management

| Criteria                                                                                  | Comment                        |
| ----------------------------------------------------------------------------------------- | ------------------------------ |
| The project makes use of references in function declarations.                             | Check `Ship::Overlap`          |
| The project uses destructors appropriately.                                               | Default destructors used       |
| The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. | No need                        |
| The project follows the Rule of 5.                                                        | No need                        |
| The project uses move semantics to move data, instead of copying it, where possible.      | Check `main` in `src/main.cpp` |
| The project uses smart pointers instead of raw pointers.                                  | Check `Game::ship`             |

### Concurrency

| Criteria                                     | Comment                             |
| -------------------------------------------- | ----------------------------------- |
| The project uses multithreading.             | Check `Game::Run` in `src/game.cpp` |
| A promise and future is used in the project. | Check `Game::Run` in `src/game.cpp` |
| A mutex or lock is used in the project.      | Check `Game::Run` in `src/game.cpp` |
| A condition variable is used in the project. | No need                             |

## Dependencies for Running Locally

- cmake >= 3.7
  - All OSes: [click here for installation instructions](https://cmake.org/install/)
- make >= 4.1 (Linux, Mac), 3.81 (Windows)
  - Linux: make is installed by default on most Linux distros
  - Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  - Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
- SDL2 >= 2.0
  - All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
    > Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
- gcc/g++ >= 5.4
  - Linux: gcc / g++ is installed by default on most Linux distros
  - Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  - Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Asteroids`
