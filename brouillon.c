/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:02:29 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/07 13:02:57 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Ajout traitement des tokens variable $
		/*	if (line[i] == '$')
			{
				start = i;
				//i++;
				if (line[i + 1] && ft_istokenword(line[i + 1]) == 1)
				{
					start = i;
					while(ft_istokenword(line[i]) && line[i]
					&& !is_operator_logical(line[i]))
						i++;
					str = ft_substr(line, start, i - start);
					type = type_token(str);
					add_token_end(&token, create_token(type, str));
				}
				else
				{
					i++;
					str = ft_substr(line, start, 1);
					type = type_token(str);
					add_token_end(&token, create_token(type, str));
				}
			}*/
