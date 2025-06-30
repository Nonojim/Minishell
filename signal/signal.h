/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:53:33 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 20:23:44 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../minishell.h"

extern volatile sig_atomic_t	g_signum;

void	signal_handler(int signum);
void	setup_signals(void);

#endif
