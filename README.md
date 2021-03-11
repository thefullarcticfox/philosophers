# philosophers
42 philosophers project about mutexes, semaphores and threads

### Build and run
1. ```make``` in any subdirectory
2. ```./philo_* [philos_count] [ms_to_die] [ms_to_eat] [ms_to_sleep] [times_to_eat]```
> last argument is optional: the simulation will stop when all philosophers had ```times_to_eat``` meals if provided. otherwise the test will be endless (until someone dies)

> Endless test example ```./philo_* 5 800 200 200```

Simulation ends on any philosopher death anyway

Heavy system load impacts the test results and any philo may die even if it's supposed to be an endless test

> ```-g -fsanitize=thread``` helps a lot with deadlocks and data races
