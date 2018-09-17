#include <include/ecs_helloworld.h>
#include <reflecs/reflecs.h>
#include <unistd.h>
#include <stdio.h>

/* -- Components -- */

typedef struct Position {
    int x;
    int y;
} Position;

typedef int Speed;


/* -- Systems --*/

void Init(void *data[], EcsInfo *info) {
    Position *position = data[0];
    Speed *speed = data[1];
    position->x = 0;
    position->y = 0;
    *speed = 1;
}

void Move(void *data[], EcsInfo *info) {
    Position *position = data[0];
    Speed speed = *(Speed*)data[1];
    position->x += speed;
    position->y += speed * 2;
}

int main(int argc, char *argv[]) {
    EcsWorld *world = ecs_init();

    /* Register components and systems with world */
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Speed);
    ECS_SYSTEM(world, Init, EcsOnInit, Position, Speed);
    ECS_SYSTEM(world, Move, EcsPeriodic, Position, Speed);

    /* Create single entity with Position and Speed component */
    EcsHandle e = ecs_new(world);
    ecs_stage(world, e, Position_h);
    ecs_stage(world, e, Speed_h);
    ecs_commit(world, e);

    /* Progress world once a second */
    while (true) {
        ecs_progress(world);
        sleep(1);
    }

    return 0;
}
