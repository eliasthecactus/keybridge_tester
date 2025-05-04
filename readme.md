# KeyBridge Tester

KeyBridge Tester is a lightweight C application designed to simulate and test the graphical login interface of the KeyBridge kiosk system. It utilizes SDL2 and related libraries to render and interact with UI components in a graphical environment.

## Features
- Graphical login screen prototype
- Built using SDL2, SDL2_image, and SDL2_ttf

## Requirements

Make sure you have the following libraries installed on your system:
- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)

On macOS with Homebrew:
```bash
brew install sdl2 sdl2_image sdl2_ttf
```

## Build Instructions
To compile the project, use the following `gcc` command:

```bash
gcc -o keybridge_tester arger.c \
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -lSDL2 -lSDL2_image -lSDL2_ttf
```

Alternatively, you can use `sdl2-config` for portable builds:
```bash
gcc -o keybridge_tester arger.c \
  $(sdl2-config --cflags --libs) \
  -lSDL2_image -lSDL2_ttf
```

## Usage
After building, run the application with:

```bash
./keybridge_tester
```

You should see a graphical login screen prototype. This can be extended to integrate authentication logic or additional UI components.

## Notes

- This is an early prototype used for development and testing purposes.
- Intended for internal use within the KeyBridge development process.

## License

This project is licensed under the custom KeyBridge License. See the [LICENSE](LICENSE) file for details.

