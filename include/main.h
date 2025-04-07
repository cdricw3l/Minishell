/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:15:28 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/02 08:51:24 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>

#include "../srcs/exec/exec.h"
#include "../srcs/parser/parser.h"
//#include "../srcs/parser/tokenizer/tokenize.h" circular include issues
#include "../libft/libft.h"
#include "../srcs/builtin/builtin.h"
#include "../srcs/execution/execution.h"
#include "../srcs/parser/tokenizer/tokenize.h"

#include <string.h>

#define DEBUGG printf("DEBUGG\n");
#define PRINT_INT(msg) printf("\x1b[31m" "DEBBUG  INT " "%d\n", msg);
#define PSTR(msg) printf("\x1b[31m" "DEBBUG  str >>> " "%s\n", msg);
#define PPTR(msg) printf("\x1b[31m" "DEBBUG  de pointeur: >>> "  "%p\n" "\x1b[0m", msg);
#define DEBUGG printf("DEBUGG\n");
#define TEST_START printf("\033[0;33m" "Initiating function test: %s\n" "\x1b[0m", __func__);
#define TEST_SUCCES printf("\033[0;32m" "Function: %s executed successfully.\n" "\x1b[0m", __func__);

#endif 