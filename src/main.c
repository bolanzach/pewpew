#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "util.h"
#include "display.h"
#include "mesh.h"
#include "vector.h"

// const int POINTS_SIZE = 9 * 9 * 9;
// Vector3 cube_points[POINTS_SIZE];
// Vector2 projected_points[POINTS_SIZE];
float field_of_view_factor = 640;

Vector3 camera_position = { .x = 0, .y = 0, .z = -6 };

Vector3 cube_rotation = { .x = 0, .y = 0, .z = 0 };

Triangle2 triangles_to_render[NUMBER_MESH_FACES];

bool is_running = false;
uint previous_frame_time = 0;

void setup(void) {
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
    
    // Texture used to display the color_buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
}

Vector2 project(Vector3 point) {
    Vector2 projected_point = {
        .x = (point.x * field_of_view_factor) / point.z,
        .y = (point.y * field_of_view_factor) / point.z,
    };

    return projected_point;
}

bool process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }
            break;
    }
}



void update(void) {
    int wait_time = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
    if (wait_time > 0 && wait_time < FRAME_TARGET_TIME) {
        SDL_Delay(wait_time);
    }

    previous_frame_time = SDL_GetTicks();

    cube_rotation.y += 0.01;
    cube_rotation.x += 0.01;
    cube_rotation.z += 0.01;

    // Iterate all the triangle faces in the mesh
    for (int i = 0; i < NUMBER_MESH_FACES; i++) {
        Face mesh_face = mesh_faces[i];

        // The 3 vertices that make up this face
        Vector3 face_vertices[3] = {
            mesh_vertices[mesh_face.a - 1],
            mesh_vertices[mesh_face.b - 1],
            mesh_vertices[mesh_face.c - 1]
        };

        Triangle2 projected_triangle;

        // Apply transformations to each vertex
        for (int j = 0; j < ARRAY_LENGTH(face_vertices); j++) {
            Vector3 transformed_vertex = face_vertices[j];

            transformed_vertex = rotate_vector3_x(transformed_vertex, cube_rotation.x);
            transformed_vertex = rotate_vector3_y(transformed_vertex, cube_rotation.y);
            transformed_vertex = rotate_vector3_z(transformed_vertex, cube_rotation.z);

            // Translate away from the camera
            transformed_vertex.z -= camera_position.z;

            Vector2 projected_point = project(transformed_vertex);

            // Scale and translate points to the middle of the screen
            projected_point.x += (window_width / 2);
            projected_point.y += (window_height / 2);

            projected_triangle.points[j] = projected_point;
        }

        // Save the projected triangle to our triangles that we are going to render
        triangles_to_render[i] = projected_triangle;
    }
}

void render(void) {
    // Iterate each projected triangle and render them
    for (int i = 0; i < NUMBER_MESH_FACES; i++) {
        Triangle2 triangle_to_render = triangles_to_render[i];

        draw_rect(
            triangle_to_render.points[0].x,
            triangle_to_render.points[0].y,
            3,
            3,
            0xFFFFFF00
        );
        draw_rect(
            triangle_to_render.points[1].x,
            triangle_to_render.points[1].y,
            3,
            3,
            0xFFFFFF00
        );
        draw_rect(
            triangle_to_render.points[2].x,
            triangle_to_render.points[2].y,
            3,
            3,
            0xFFFFFF00
        );
    }

    //draw_grid();

    render_color_buffer();

    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}


int main(void) {
    printf("sup\n");

    is_running = initialize_window();
    
    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    printf("done\n");
    destroy_window();

    return 0;
}

