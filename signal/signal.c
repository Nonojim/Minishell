/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:54:42 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/13 10:38:57 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

volatile sig_atomic_t	g_signum = 0;

void	signal_handler(int signum)
{
//	g_signum = signum;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		if (signum == SIGINT)
		{
			g_signum = 1;
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	//return ;
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

void	signal_heredoc_handler(int signum)
{
	(void)signum;
	g_signum = 1;
//	printf("ctrl+c");
	write(1, "\n", 1);
	exit(130); //probleme
	//signal(signum, SIG_DFL);
	//kill(getpid(), signum); 
}

void	setup_signal_heredoc(void)
{
	signal(SIGINT, signal_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(EOF, SIG_IGN); //semble servir a rien
}
