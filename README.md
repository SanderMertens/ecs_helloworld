# ecs_helloworld
This project shows a simple hello world application for the reflecs framework. It demonstrates how components are plain C structs, how systems are plain C functions, and how they can be simply registered with reflecs using the `ECS_COMPONENT` and `ECS_SYSTEM` macro's. The following code shows how C struct `Position` is registered as component:

```c
ECS_COMPONENT(world, Position);
```

It also demonstrates two different kinds of systems. The `OnInit` system is ran once when a component is added to an entity (there is also a `OnDeinit` system kind which runs when a component is removed). The `OnPeriodic` system is ran whenever `ecs_progress` is invoked. Example from code:

```c
ECS_SYSTEM(world, Move, EcsPeriodic, Position, Speed);
```


Finally, it shows how to efficiently add components to an entity using `ecs_stage` and `ecs_commit`. Components in reflecs are stored in tables. Tables are automatically created for every combination of components that is found on entities. To prevent moving an entity between tables while adding multiple components, components are first staged, and only inserted into a table when `ecs_commit` is called. Example from code:

```c
EcsHandle e = ecs_new(world);
ecs_stage(world, e, Position_h);
ecs_stage(world, e, Speed_h);
ecs_commit(world, e);
```
