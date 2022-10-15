#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;

// Notice that this is a pointer.
// In practice, this acts as an array of memory. The pointer points to the first element
uint32_t* color_buffer = NULL;

int window_width = 800;
int window_height = 600;

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL!\n");
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    window_width = display_mode.w;
    window_height = display_mode.h;

    window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        window_width, 
        window_height, 
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL Window!\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer!\n");
        return false;
    }

    // !Uncomment this??
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void draw_pixel(int x, int y, uint32_t color) {
    if (x < window_width && y < window_height) {
        color_buffer[(window_width * y) + x] = color;
    }
}

void draw_grid() {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            if (x % 100 == 0 || y % 100 == 0) {
                draw_pixel(x, y, 0xFFFF000);
            }
        }
    }
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int ix = x; ix < x + width; ix++) {
        for (int iy = y; iy < y + height; iy++) {
            draw_pixel(ix, iy, color);
        }
    }
}

void render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int) (window_width * sizeof(uint32_t))
    );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            draw_pixel(x, y, color);
        }
    }
}

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}