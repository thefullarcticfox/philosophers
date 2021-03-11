#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/*
**	int		pthread_create(pthread_t *thread, const pthread_attr_t *attr,
**				void *(*start_routine)(void *), void *arg);
**	int		pthread_detach(pthread_t thread);
**	int		pthread_join(pthread_t thread, void **value_ptr);
**	int		pthread_mutex_init(pthread_mutex_t *mutex,
**				const pthread_mutexattr_t *attr);
**	int		pthread_mutex_destroy(pthread_mutex_t *mutex);
**	int		pthread_mutex_lock(pthread_mutex_t *mutex);
**	int		pthread_mutex_unlock(pthread_mutex_t *mutex);
*/

# define TAKENFORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4
# define COMPLETE 5

# define BADARG -1
# define MALLOC -2
# define NEFORK -3
# define THREAD -4
# define MUTEXF -5

typedef struct timeval	t_time;

typedef struct			s_conf
{
	int					number;
	size_t				ms_to_die;
	size_t				ms_to_eat;
	size_t				ms_to_sleep;
	int					eating_times;
	size_t				ms_start;
	int					state;
	pthread_mutex_t		*state_lock;
	pthread_mutex_t		*write_lock;
}						t_conf;

typedef struct			s_fork
{
	pthread_mutex_t		*fork;
	int					lastphil;
}						t_fork;

typedef struct			s_philo
{
	int					n;
	int					eaten_times;
	t_conf				*conf;
	size_t				lastmeal_ms;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_mutex_t		*lastmeal_lock;
}						t_philo;

typedef struct			s_philo_one
{
	t_conf				*conf;
	t_philo				*philo;
	t_fork				*forks;
	pthread_t			**threads;
}						t_common;

size_t					ft_getms();
int						ft_checkstate(t_philo *ph);
int						ft_philowatch(t_common *ph);
int						ft_printstate(t_philo *philo, int state);
int						ft_printerror(int errnum, pthread_mutex_t *write_lock);
int						ft_initphilo(t_common *ph);
int						ft_runphilo(t_common *ph);
void					ft_cleanup(t_common *ph);

#endif
