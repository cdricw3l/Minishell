/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:02:58 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 12:09:51 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
#define BUILTIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/main.h"

 
char *ft_pwd(void);
void ft_echo(char *str, int option, int fd);

#endif