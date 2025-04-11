/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/11 13:11:19 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


 #include "../include/main.h"


 int main(int argc, char **argv, char **envp)
 {
	(void)argc;
	(void)argv;
	char **dupplicate_env;

	dupplicate_env = ft_duplicate_env(envp);
 	ft_start_minishell("minishell: ", dupplicate_env);
 	return(0);
 }
 


