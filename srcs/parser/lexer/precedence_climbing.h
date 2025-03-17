/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precedence_climbing.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:58:58 by cw3l              #+#    #+#             */
/*   Updated: 2025/03/17 21:51:43 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../../libft/libft.h"

#ifndef AST_H
#define AST_H


typedef struct s_node
{
    char value;
    
    void *right;
    void *left;

} t_node;

t_node      **ft_get_token_lst(char *str);


#endif