#include "philo_three.h"

static int	ft_argtoi(char *str, int *numint, size_t *numszt)
{
	if (numint != NULL)
	{
		*numint = 0;
		while (*str >= '0' && *str <= '9')
		{
			*numint = (*numint) * 10 + (*str - '0');
			str++;
		}
	}
	else if (numszt != NULL)
	{
		*numszt = 0;
		while (*str >= '0' && *str <= '9')
		{
			*numszt = (*numszt) * 10 + (*str - '0');
			str++;
		}
	}
	if (*str != 0)
		return (-1);
	return (0);
}

static int	ft_parseconf(int ac, char **av, t_conf *c)
{
	int		i;

	if (ac < 5 || ac > 6)
		return (-1);
	i = 0;
	while (++i < ac)
	{
		if (i == 1 && ft_argtoi(av[i], &(c->number), NULL) < 0)
			return (-1);
		else if (i == 2 && ft_argtoi(av[i], NULL, &(c->ms_to_die)) < 0)
			return (-1);
		else if (i == 3 && ft_argtoi(av[i], NULL, &(c->ms_to_eat)) < 0)
			return (-1);
		else if (i == 4 && ft_argtoi(av[i], NULL, &(c->ms_to_sleep)) < 0)
			return (-1);
		else if (i == 5 && ft_argtoi(av[i], &(c->eating_times), NULL) < 0)
			return (-1);
	}
	if (ac == 5)
		c->eating_times = -1;
	return (0);
}

int			main(int ac, char **av)
{
	int				ret;
	t_conf			config;
	t_common		ph;

	memset(&ph, 0, sizeof(t_common));
	config.state = 0;
	config.state_lock = NULL;
	ph.conf = &config;
	if ((ret = ft_parseconf(ac, av, &config)) < 0)
		return (ft_printerror(ret, NULL));
	if (config.number < 2)
		return (ft_printerror(NEFORK, NULL));
	if (config.eating_times == 0)
		return (0);
	if ((ret = ft_initphilo(&ph)) < 0)
		return (ft_printerror(ret, NULL));
	if ((ret = ft_runphilo(&ph)) < 0)
		return (ft_printerror(ret, NULL));
	ft_cleanup(&ph);
	return (0);
}
