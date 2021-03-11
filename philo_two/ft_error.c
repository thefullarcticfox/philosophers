#include "philo_two.h"

static void		ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = 0;
	while (s && s[len])
		len++;
	write(fd, s, len);
}

int				ft_printerror(int errnum, sem_t *write_lock)
{
	if (write_lock && sem_wait(write_lock) < 0)
		return (ft_printerror(SEMAPH, NULL));
	if (errnum == BADARG)
		ft_putstr_fd("Error: bad arguments\n", 2);
	else if (errnum == MALLOC)
		ft_putstr_fd("Error: malloc failed\n", 2);
	else if (errnum == NEFORK)
		ft_putstr_fd("Error: less than two forks available\n", 2);
	else if (errnum == THREAD)
		ft_putstr_fd("Error: pthread failed\n", 2);
	else if (errnum == SEMAPH)
		ft_putstr_fd("Error: semaphore failed\n", 2);
	if (write_lock && sem_post(write_lock) < 0)
		return (ft_printerror(SEMAPH, NULL));
	return (1);
}

static void		ft_cleanthreads(t_common *ph)
{
	int		i;

	i = -1;
	while (ph->threads && ++i < ph->conf->number)
		free(ph->threads[i]);
	free(ph->threads);
	if (ph->forks && sem_close(ph->forks) < 0)
		ft_printerror(SEMAPH, NULL);
	sem_unlink("/forks_sem");
}

void			ft_cleanup(t_common *ph)
{
	ft_cleanthreads(ph);
	if (ph->conf->state_lock && sem_close(ph->conf->state_lock) < 0)
		ft_printerror(SEMAPH, NULL);
	sem_unlink("/state_lock");
	if (ph->conf->write_lock && sem_close(ph->conf->write_lock) < 0)
		ft_printerror(SEMAPH, NULL);
	sem_unlink("/write_lock");
	if (ph->conf->servant && sem_close(ph->conf->servant) < 0)
		ft_printerror(SEMAPH, NULL);
	sem_unlink("/servant");
	if (ph->conf->statuses_lock && sem_close(ph->conf->statuses_lock) < 0)
		ft_printerror(SEMAPH, NULL);
	sem_unlink("/statuses_lock");
	free(ph->philo);
	free(ph->conf->statuses);
}
