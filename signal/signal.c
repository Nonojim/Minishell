/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 07:54:42 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 07:56:44 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

/*
signal 	void (*signal(int sig, void (*handler)(int)))(int); 	Définit un gestionnaire de signal

sigaction 	int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact); 	Gestion des signaux

sigemptyset 	int sigemptyset(sigset_t *set); 	Initialise un ensemble vide de signaux.

sigaddset 	int sigaddset(sigset_t *set, int signum); 	Ajoute un signal à un ensemble.

kill 	int kill(pid_t pid, int sig); 	Envoie un signal à un processus.

*/
