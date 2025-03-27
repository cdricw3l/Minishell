/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:20 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/27 17:52:47 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  TEST_UNIT_H
#define TEST_UNIT_H

#include "../srcs/parser/parser.h"
#include "../srcs/execution/execution.h"
#include "../srcs/builtin/builtin.h"
#include "../srcs/parser/lexer/precedence_climbing.h"
#include "../include/main.h"
#include <assert.h>


int tst_ast(void);
int tst_shutting(void);
int tst_tokenizer(void);
int tst_builtin(int argc, char *envp[]);
int tst_exe(void);

#endif