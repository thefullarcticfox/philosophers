#include "philo_two.h"

static int		ft_takeforks(t_philo *ph)
{
	if (ft_checkstate(ph))
		return (1);
	if (sem_wait(ph->conf->servant) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	if (sem_wait(ph->forks) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	ft_printstate(ph, TAKENFORK);
	if (sem_wait(ph->forks) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	ft_printstate(ph, TAKENFORK);
	if (sem_post(ph->conf->servant) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	return (0);
}

static int		ft_eat(t_philo *ph)
{
	int		ret;

	ret = 0;
	if (ft_checkstate(ph))
		ret = 1;
	else
	{
		ph->lastmeal_ms = ft_getms();
		ph->eaten_times++;
		ft_printstate(ph, EATING);
		usleep(ph->conf->ms_to_eat * 1000);
	}
	if (sem_post(ph->forks) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	if (sem_post(ph->forks) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	return (ret);
}

void			*ft_thread(void *ptr)
{
	t_philo		*ph;

	ph = (t_philo*)ptr;
	while (ph->eaten_times != ph->conf->eating_times)
	{
		if (ft_takeforks(ph))
			break ;
		if (ft_eat(ph))
			break ;
		if (ft_checkstate(ph))
			break ;
		ft_printstate(ph, SLEEPING);
		usleep(ph->conf->ms_to_sleep * 1000);
		if (ft_checkstate(ph))
			break ;
		ft_printstate(ph, THINKING);
	}
	if (ph->eaten_times == ph->conf->eating_times)
		ft_philocomplete(ph);
	return (NULL);
}

int				ft_runphilo(t_common *ph)
{
	int		i;

	i = -1;
	ph->conf->ms_start = ft_getms();
	while (ph->philo && ++i < ph->conf->number)
	{
		ph->philo[i].lastmeal_ms = ph->conf->ms_start;
		ph->philo[i].conf = ph->conf;
		if (pthread_create(ph->threads[i], NULL, ft_thread, &(ph->philo[i])))
			return (THREAD);
	}
	ft_philowatch(ph);
	i = -1;
	while (ph->philo && ++i < ph->conf->number)
		if (pthread_join(*(ph->threads[i]), NULL))
			return (THREAD);
	return (0);
}
