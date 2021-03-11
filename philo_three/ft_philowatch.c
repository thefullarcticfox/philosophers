#include "philo_three.h"

int			ft_checkstate(t_philo *ph)
{
	if (sem_wait(ph->conf->state_lock) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	if (ph->conf->state == DIED)
	{
		if (sem_post(ph->conf->state_lock) < 0)
			return (ft_printerror(SEMAPH, ph->conf->write_lock));
		return (1);
	}
	if (ft_getms() - ph->lastmeal_ms > ph->conf->ms_to_die)
	{
		if (ph->eaten_times != ph->conf->eating_times)
			ph->conf->state = DIED;
		if (ph->conf->state == DIED)
			ft_printstate(ph, DIED);
		if (sem_post(ph->conf->state_lock) < 0)
			return (ft_printerror(SEMAPH, ph->conf->write_lock));
		return (1);
	}
	if (sem_post(ph->conf->state_lock) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	return (0);
}

void		ft_philowatch(t_common *ph)
{
	int		i;
	int		status;
	int		finished;

	status = 0;
	finished = 0;
	while (status == 0 && finished < ph->conf->number)
	{
		if (waitpid(-1, &status, 0) < 0)
			ft_printerror(WAITER, ph->conf->write_lock);
		finished++;
	}
	if (status != 0)
	{
		i = -1;
		while (++i < ph->conf->number)
			kill(ph->philo[i].pid, SIGTERM);
	}
}
