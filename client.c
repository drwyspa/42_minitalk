/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:12:13 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/08/01 21:15:34 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//Client module - here user will input a message.
//This function takes signals from main and send as a bits, to the server.
//Bit 0 as SIGUSR1 and 1 as a SIGUSR2
void	send_signals(int pid, char *msg)
{
	int	letter;
	int	i;

	letter = 0;
	while (msg[letter])
	{
		i = 0;
		while (i++ < 8)
		{
			if (((unsigned char)(msg[letter] >> (7 - (i - 1))) & 1) == 0)
				kill(pid, SIGUSR1);
			else if (((unsigned char)(msg[letter] >> (7 - (i - 1))) & 1) == 1)
				kill(pid, SIGUSR2);
			usleep(50);
		}
		letter++;
	}
	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(50);
	}
}

//Takes PID and message as an input from the user.
//Convert PID to int.
//Sends signals using send_signals function.
//Handles errors.
int	main(int argc, char **argv)
{
	char	*msg;
	int		server_id;

	if (argc == 3)
	{
		server_id = ft_atoi(argv[1]);
		if (!server_id)
		{
			ft_printf("[ERROR]. Wrong PID");
			return (0);
		}
		msg = argv[2];
		if (msg[0] == 0)
		{
			ft_printf("[ERROR]. Please type a message.");
			return (0);
		}
		send_signals(server_id, msg);
	}
	else
	{
		ft_printf("[ERROR]. Check your input.\n");
		ft_printf("It should looks like this: ./client <PID> <MESSAGE>");
	}
	return (0);
}
