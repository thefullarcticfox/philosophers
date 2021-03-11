# philosophers
42 philosophers project about mutexes, semaphores and threads

### Build and run
1. ```make``` in any subdirectory
2. ```./philo_* [philos_count] [ms_to_die] [ms_to_eat] [ms_to_sleep] [times_to_eat]```

> last argument is optional (it finishes the simulation when every philosopher has eaten at least times_to_eat)

> ```-fsanitize=thread``` helps a lot
