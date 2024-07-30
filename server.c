/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 21:43:34 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/07/30 22:50:25 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//Count power for a taken number.
//Need this as part of function which changes bits to ASCII.
int	ft_recursive_power(int nb, int power)
{
	int	res;

	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	else
	{
		res = nb * ft_recursive_power(nb, power -1);
		return (res);
	}
}

//Adding letter at the end of a string.
char	*letter_to_string(char const *s1, char const letter)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	str[j++] = letter;
	str[j] = '\0';
	free((void *)(s1));
	return (str);
}

//Handling signals and changing bits to ASCII.
//Building strings from signals.
void	signal_handler(int signum)
{
	static int	counter = 0;
	static int	result = 0;
	static int	len = 0;
	static char	*final;

	if (!final)
		final = ft_strdup("");
	if (signum == SIGUSR1)
		result = result + 0;
	else if (signum == SIGUSR2)
		result = result + (1 * ft_recursive_power(2, 7 - counter));
	counter++;
	if (counter == 8)
	{
		final = letter_to_string(final, result);
		if (result == '\0')
		{
			ft_printf("%s\n", final);
			final = NULL;
		}
		counter = 0;
		result = 0;
		len += 1;
	}
}

//Configure and run server for receiving the signals.
int	main(void)
{
	struct sigaction	signal_received;

	ft_printf("Hello! It's Przemek's server.\n");
	ft_printf("My PID is: %d\n", getpid());
	signal_received.sa_handler = signal_handler;
	signal_received.sa_flags = 0;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	while (1)
		usleep(50);
}
