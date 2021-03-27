#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

/*
**	# include <pthread.h>
**	int		pthread_create(pthread_t *thread, const pthread_attr_t *attr,
**				void *(*start_routine)(void *), void *arg);
**	int		pthread_detach(pthread_t thread);
**	int		pthread_join(pthread_t thread, void **value_ptr);
**	sem_t	*sem_open(const char *name, int oflag, ...);
**	^ returns SEM_FAILED on error
**	others return -1 on error
**	int		sem_close(sem_t *sem);
**	int		sem_post(sem_t *sem);
**	int		sem_wait(sem_t *sem);
**	int		sem_unlink(const char *name);
**	+ fork, kill, exit allowed
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
# define SEMAPH -5
# define FORKER -6
# define WAITER -7
# define KILLER -6

typedef struct timeval	t_time;

typedef struct	s_conf
{
	int			number;
	size_t		ms_to_die;
	size_t		ms_to_eat;
	size_t		ms_to_sleep;
	int			eating_times;
	size_t		ms_start;
	int			state;
	sem_t		*state_lock;
	sem_t		*servant;
	sem_t		*write_lock;
}				t_conf;

typedef struct	s_philo
{
	int			n;
	pid_t		pid;
	int			eaten_times;
	t_conf		*conf;
	size_t		lastmeal_ms;
	sem_t		*forks;
}				t_philo;

typedef struct	s_philo_one
{
	t_conf		*conf;
	t_philo		*philo;
	sem_t		*forks;
}				t_common;

size_t			ft_getms();
void			ft_usleep(size_t ms);
int				ft_checkstate(t_philo *ph);
void			ft_philowatch(t_common *ph);
int				ft_printstate(t_philo *philo, int state);
int				ft_printerror(int errnum, sem_t *write_lock);
int				ft_initphilo(t_common *ph);
int				ft_runphilo(t_common *ph);
void			ft_cleanup(t_common *ph);

#endif
