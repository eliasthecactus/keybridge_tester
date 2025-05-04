#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

const char* USERNAME = "admin";
const char* PASSWORD = "password";

const char* get_default_font_path() {
#ifdef __APPLE__
    return "/System/Library/Fonts/Supplemental/Arial.ttf";
#elif __linux__
    return "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
#else
    return "C:\\Windows\\Fonts\\arial.ttf";
#endif
}

void render_text(SDL_Renderer *renderer, const char *text, int x, int y, TTF_Font *font, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) return;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int login_gui(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    char input_username[50] = "";
    char input_password[50] = "";
    int input_field = 0;  // 0 = username, 1 = password
    int running = 1;
    SDL_Event event;

    while (running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_text(renderer, "Username:", 50, 50, font, white);
        render_text(renderer, input_username, 200, 50, font, white);
        render_text(renderer, "Password:", 50, 100, font, white);
        render_text(renderer, "********", 200, 100, font, white);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return 0;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
                        return 1; // Successful login
                    } else {
                        render_text(renderer, "Invalid Credentials", 50, 200, font, red);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(1000);
                    }
                } else if (event.key.keysym.sym == SDLK_TAB) {
                    input_field = (input_field + 1) % 2;
                } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    if (input_field == 0 && strlen(input_username) > 0) {
                        input_username[strlen(input_username) - 1] = '\0';
                    } else if (input_field == 1 && strlen(input_password) > 0) {
                        input_password[strlen(input_password) - 1] = '\0';
                    }
                }
            } else if (event.type == SDL_TEXTINPUT) {
                if (input_field == 0 && strlen(input_username) < 49) {
                    strcat(input_username, event.text.text);
                } else if (input_field == 1 && strlen(input_password) < 49) {
                    strcat(input_password, event.text.text);
                }
            }
        }
    }
    return 0;
}

void main_window(SDL_Renderer *renderer, TTF_Font *font, int argc, char *argv[]) {
    SDL_Color white = {255, 255, 255, 255};
    int running = 1;
    SDL_Event event;

    while (running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        render_text(renderer, "Main Window - Arguments:", 50, 50, font, white);

        int y_offset = 100;
        for (int i = 0; i < argc; i++) {
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "Arg %d: %s", i, argv[i]);
            render_text(renderer, buffer, 50, y_offset, font, white);
            y_offset += 40;
        }
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() == -1) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Login System", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!window || !renderer) {
        printf("Error creating window or renderer: %s\n", SDL_GetError());
        return 1;
    }
    
    const char *font_path = get_default_font_path();
    TTF_Font *font = TTF_OpenFont(font_path, 24);
    if (!font) {
        printf("Error loading font: %s\n", TTF_GetError());
        return 1;
    }
    
    if (argc < 3 || strcmp(argv[1], USERNAME) != 0 || strcmp(argv[2], PASSWORD) != 0) {
        if (!login_gui(renderer, font)) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            return 1;
        }
    }
    
    main_window(renderer, font, argc, argv);
    
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
