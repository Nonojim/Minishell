/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:53:33 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/03 17:44:31 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../minishell.h"

extern volatile sig_atomic_t	g_signum;

void	signal_handler(int signum);
void	setup_signals(void);
void	setup_signal_heredoc(void);
void	signal_heredoc_handler(int signum);

#endif
