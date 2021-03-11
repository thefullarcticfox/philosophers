#include "philo_three.h"

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
	else if (errnum == FORKER)
		ft_putstr_fd("Error: fork failed\n", 2);
	else if (errnum == WAITER)
		ft_putstr_fd("Error: waitpid failed\n", 2);
	else if (errnum == KILLER)
		ft_putstr_fd("Error: kill failed\n", 2);
	if (write_lock && sem_post(write_lock) < 0)
		return (ft_printerror(SEMAPH, NULL));
	return (1);
}

void			ft_cleanup(t_common *ph)
{
	if (ph->forks && sem_close(ph->forks) < 0)
		ft_printerror(SEMAPH, NULL);
	sem_unlink("/forks_sem");
	if (ph->conf->state_lock && sem_close(ph->conf->state_lock) < 0)
		ft_printerror(SEMAPH, NULL);
	sem_unlink("/state_lock");
	if (ph->conf->write_lock && sem_close(ph->conf->write_lock) < 0)
		ft_printerror(SEMAPH, NULL);
	sem_unlink("/write_lock");
	if (ph->conf->servant && sem_close(ph->conf->servant) < 0)
		ft_printerror(SEMAPH, NULL);
	sem_unlink("/servant");
	free(ph->philo);
}
