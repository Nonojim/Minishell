/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:54:42 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/06 17:43:46 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

volatile sig_atomic_t	g_signum = 0;

void	signal_handler(int signum)
{
	g_signum = signum;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		if (signum == SIGINT)
		{
			write(2, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	setup_signals(void)
{
	struct sigaction	signalusr;

	ft_memset(&signalusr, 0, sizeof(signalusr));
	signalusr.sa_handler = signal_handler;
	signalusr.sa_flags = 0;
	sigemptyset(&signalusr.sa_mask);
	sigaction(SIGINT, &signalusr, NULL);
	signal(SIGQUIT, SIG_IGN);
}
