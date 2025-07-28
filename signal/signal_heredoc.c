/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:20:19 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/28 09:20:47 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	signal_heredoc_handler(int signum)
{
	g_signum = signum;
	write(2, "\n", 1);
	exit(130);
}

void	setup_signal_heredoc(void)
{
	signal(SIGINT, signal_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(EOF, SIG_IGN);
}
