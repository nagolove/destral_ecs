#include "raymath.h"
#include "raylib.h"
#include "rlgl.h"

#define DESTRAL_ECS_IMPL
#include "destral_ecs.h"
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

struct Component_Position {
    Vector2 p;
    float   angle;
};

const int screenWidth = 800;
const int screenHeight = 450;

static const de_cp_type component_position = {
    .cp_id = 0,
    .cp_sizeof = sizeof(struct Component_Position),
    .name = "position"
};

static const de_cp_type component_velocity = {
    .cp_id = 1,
    .cp_sizeof = sizeof(struct Vector2),
    .name = "velocity",
};

static const de_cp_type component_angular_velocity = {
    .cp_id = 2,
    .cp_sizeof = sizeof(float),
    .name = "angular_velocity",
};

static const de_cp_type componet_color = {
    .cp_id = 3,
    .cp_sizeof = sizeof(Color),
    .name = "color",
};
static de_ecs* r = NULL;

void particle_build(de_ecs *r) {
    de_entity e = de_create(r);

    struct Component_Position* pos = de_emplace(r, e, component_position);
    pos->p.x = rand() % GetScreenWidth();
    pos->p.y = rand() % GetScreenHeight();
    pos->angle = (rand() / (double)RAND_MAX) * 2. * M_PI;

    Vector2* v = de_emplace(r, e, component_velocity);
    v->x = rand() / (double)RAND_MAX;
    v->y = rand() / (double)RAND_MAX;

    float* angular_v = de_emplace(r, e, component_angular_velocity);
    *angular_v = (rand() / (double)RAND_MAX);
}

void update() {

    puts("single view transform component");
}

const float particle_radius = 20.;

void render() {
    BeginDrawing();
    for (de_view_single v = de_create_view_single(r, component_position);
            de_view_single_valid(&v); de_view_single_next(&v)) {
        de_entity e = de_view_single_entity(&v);
        struct Component_Position* p = de_view_single_get(&v);
        Color *c = de_view_single_get(&v);

        Vector2 vert, displacement;


        rlBegin(RL_TRIANGLES);

        displacement = (Vector2) {
            cosf(p->angle) * particle_radius,
            sinf(p->angle) * particle_radius,
        };
        vert = Vector2Add(p->p, displacement);
        rlVertex2f(vert.x, vert.y);
        rlColor4ub(c->r, c->g, c->b, c->a);

        displacement = (Vector2) {
            cosf(p->angle) * particle_radius,
            sinf(p->angle) * particle_radius,
        };
        vert = Vector2Add(p->p, displacement);
        rlVertex2f(vert.x, vert.y);
        rlColor4ub(c->r, c->g, c->b, c->a);

        displacement = (Vector2) {
            cosf(p->angle) * particle_radius,
            sinf(p->angle) * particle_radius,
        };
        vert = Vector2Add(p->p, displacement);
        rlVertex2f(vert.x, vert.y);
        rlColor4ub(c->r, c->g, c->b, c->a);

        rlEnd();
    }
    EndDrawing();
}

int main() {
    InitWindow(screenWidth, screenHeight, "particles engine");

    r = de_ecs_make();
    
    for (int i = 0; i < 4096; i++) {
        particle_build(r);
    }

    /*
    puts("single view transform component");
    for (de_view_single v = de_create_view_single(r, transform_type);
            de_view_single_valid(&v); de_view_single_next(&v)) {
        de_entity e = de_view_single_entity(&v);
        transform* c = de_view_single_get(&v);
        printf("transform  entity: %d => x=%d, y=%d, z=%d\n", de_entity_identifier(e).id, c->x, c->y, c->z);
    }

    puts("\nsingle view velocity component");
    for (de_view_single v = de_create_view_single(r, velocity_type);
            de_view_single_valid(&v); de_view_single_next(&v)) {
        de_entity e = de_view_single_entity(&v);
        velocity* c = de_view_single_get(&v);
        printf("velocity  entity: %d => w=%f\n", de_entity_identifier(e).id, c->v);
    }

    puts("\nmulti view entities with (transform AND velocity) components");
    for (de_view v = de_create_view(r, 2, (de_cp_type[2]) {transform_type, velocity_type });
            de_view_valid(&v); de_view_next(&v)) {
        de_entity e = de_view_entity(&v);
        transform* tr = de_view_get(&v, transform_type);
        velocity* tc = de_view_get(&v, velocity_type);
        printf("transform  entity: %d => x=%d, y=%d, z=%d\n", de_entity_identifier(e).id, tr->x, tr->y, tr->z);
        printf("velocity  entity: %d => w=%f\n", de_entity_identifier(e).id, tc->v);
    }
    */

    // SetRandomSeed(0xaabbccff);   // Set a custom random seed if desired, by default: "time(NULL)"

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        update();
        render();
    }

    de_ecs_destroy(r);

    CloseWindow();        

}
