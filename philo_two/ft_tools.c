#include "philo_two.h"

size_t			ft_getms(void)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return ((size_t)now.tv_sec * 1000 + (size_t)now.tv_usec / 1000);
}

/*
**	this fixes usleep on darwin: calling usleep(ms * 1000)
**	like i did on linux takes much more time on darwin
*/
void			ft_usleep(size_t ms)
{
	size_t	start = ft_getms();
	while (ft_getms() - start < ms)
		usleep(100);
}

static size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = -1;
	while (src && src[++i])
		dst[i] = src[i];
	dst[i] = 0;
	return (i);
}

static int		ft_numinsert(char *dst, size_t n)
{
	int		i;
	int		len;
	size_t	tmp;

	len = 1;
	tmp = n;
	while (tmp / 10 != 0)
	{
		tmp /= 10;
		len++;
	}
	i = len;
	while (n / 10 != 0)
	{
		dst[--i] = n % 10 + '0';
		n /= 10;
	}
	dst[--i] = n % 10 + '0';
	return (len);
}

int				ft_printstate(t_philo *philo, int state)
{
	char		buf[50];
	int			len;

	len = ft_numinsert(buf, ft_getms() - philo->conf->ms_start);
	len += ft_strcpy(&buf[len], "ms ");
	len += ft_numinsert(&buf[len], philo->n);
	if (state == 0)
		len += ft_strcpy(&buf[len], " has taken a fork\n");
	else if (state == 1)
		len += ft_strcpy(&buf[len], " is eating\n");
	else if (state == 2)
		len += ft_strcpy(&buf[len], " is sleeping\n");
	else if (state == 3)
		len += ft_strcpy(&buf[len], " is thinking\n");
	else if (state == 4)
		len += ft_strcpy(&buf[len], " died\n");
	if (sem_wait(philo->conf->write_lock) < 0)
		ft_printerror(SEMAPH, NULL);
	write(1, buf, len);
	if (sem_post(philo->conf->write_lock) < 0)
		ft_printerror(SEMAPH, NULL);
	return (0);
}
