# TASM #

This is a small auto runner game created using raylib and C++. I have larger ideas for aesthetic and features for this game that I will probably revisit using a more robust technology but this is a nice test and vibe check.

## Features & Technologies ##
- [C++](https://cplusplus.com/)
- [Raylib](https://www.raylib.com/)
- [Raymath](https://github.com/raysan5/raylib/blob/master/src/raymath.h)

### Required Features ###

- [X] Opens a window 
- [X] Has Sprites/3D Models: Includes textures, shapes, shaders, 3D models 
- [X] Capable of user input: Game controller, mouse input, keyboard input, use of camera 
- [X] Sprites/3D Models capable of: Movement, animation, collisions 
- [X] Plays audio: Background audio or individual audio clips 
- [X] Includes text: Load different fonts 
- [X] Uses git/github source control
- [X] Use of header and source files

### Additional Feature Targets ###

- [X] Power-ups / Invincibility
- [X] Score and reset game on completion
- [X] Parallax Backgrounds
- [ ] Different levels of difficulty

## Future Improvements ##

- Prevent crouching while jumping
- Better measure of difficulty

## Compiling and Running ##

I ran into a lot of trouble using the [Raylib Starter template](https://github.com/ItsAlanK/raylib-starter-template) copied from class. Running it on my Mac resulted in a lot of issues with compiling and it really didn't play nicewhich is something I found fairly quickly working on the 'main' branch. This like referencing header files within subdirectories broke as the compiler couldn't see them.

The solution was to start over with a fresh template using CMake which I grabbed [from here](https://github.com/grplyler/raylib-cmake-starter) so credit to [Grplyler](https://github.com/grplyler) for getting me to that start line to actually make the project here.

If cloning the repo you'll need to copy the steps of the starter template to build and run the project:

1. Clone this repository
2. Initialize the submodules: `git submodule update --init --recursive`
3. Build `./b`
4. Run `./r`


## Credits ##

- [Raylib CMake Starter Template](https://github.com/grplyler/raylib-cmake-starter)
- Sounds created using [fFXGen](https://raylibtech.itch.io/rfxgen)