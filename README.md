# TASM #


## Features & Technologies ##


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

- [ ] Power-ups 
- [ ] Particle effects on death
- [ ] Different levels of difficulty

## Future Improvements ##


## Compiling and Running ##

I ran into a lot of trouble using the [Raylib Starter template](https://github.com/ItsAlanK/raylib-starter-template) copied from class. Running it on my Mac resulted in a lot of issues with compiling and it really didn't play nicewhich is something I found fairly quickly working on the 'main' branch. This like referencing header files within subdirectories broke as the compiler couldn't see them.

The solution was to start over with a fresh template using CMake which I grabbed [from here](https://github.com/grplyler/raylib-cmake-starter) so credit to [Grplyler](https://github.com/grplyler) for getting me to that start line to actually make the project here.

If cloning the repo you'll need to copy the steps of the starter template to build and run the project:

1. Clone this repository
2. Initialize the submodules: `git submodule update --init --recursive`
3. Build `./b`
4. Run `./r`


## Credits ##