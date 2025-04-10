/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/10 12:02:52 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


 #include "../include/main.h"


 int main(int argc, char **argv, char **envp)//
 {
	(void)argc;
	(void)argv;
	char **dupplicate_env;

	dupplicate_env = ft_duplicate_env(envp);
 	ft_start_minishell("minishell: ", dupplicate_env);
 	return(0);
 }
 


