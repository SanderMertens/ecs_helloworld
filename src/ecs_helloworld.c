#include <include/ecs_helloworld.h>
#include <reflecs/reflecs.h>

typedef struct Location {
	int x;
	int y;
} Location;

typedef struct Speed {
	int x;
	int y;
} Speed;

typedef struct Color {
	char *color;
} Color;

void Move(EcsEntity *system, EcsEntity *e, void *data[]) {
	Location *location = data[0];
	Speed *speed = data[1];

	location->x += speed->x;
	location->y += speed->y;

	printf("%s: moved %d, %d\n", ecs_get_id(e), location->x, location->y);
}

void InitSpeed(EcsEntity *system, EcsEntity *e, void *data[]) {
	Speed *speed = data[0];

	speed->x = 1;
	speed->y = 1;

	printf("%s: init %d, %d\n", ecs_get_id(e), speed->x, speed->y);
}

int main(int argc, char *argv[]) {

	EcsWorld *world = ecs_world_new();

	ECS_COMPONENT(world, Location);
	ECS_COMPONENT(world, Speed);
	ECS_COMPONENT(world, Color);

	ECS_SYSTEM(world, InitSpeed, EcsOnInit, Speed);
	ECS_SYSTEM(world, Move, EcsPeriodic, Location, Speed);

	EcsEntity *e = ecs_new(world, "my_entity");
	Color *color = ecs_add(e, Color_e);
	color->color = "RED";
	ecs_add(e, Location_e);
	ecs_add(e, Speed_e);

	e = ecs_new(world, "my_2nd_entity");
	color = ecs_add(e, Color_e);
	color->color = "RED";
	ecs_add(e, Location_e);
	ecs_add(e, Speed_e);

	while (true) {
		ecs_world_progress(world);
		sleep(1);
	}

    return 0;
}
