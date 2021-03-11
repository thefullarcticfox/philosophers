# philosophers
42 philosophers project about mutexes, semaphores and threads

### Build and run
1. ```make``` in any subdirectory
2. ```./philo_* [philos_count] [ms_to_die] [ms_to_eat] [ms_to_sleep] [times_to_eat]```
> last argument is optional: if provided the simulation will stop when all philosophers eated ```times_to_eat``` or will be endless (until someone dies) if not provided

> simulation ends on any philosopher death anyway

> ```-fsanitize=thread``` helps a lot

> heavy system load impacts the test results (anyone may die even if it's supposed to be endless test)
