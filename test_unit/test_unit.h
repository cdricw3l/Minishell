/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:20 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/26 11:27:05 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  TEST_UNIT_H
#define TEST_UNIT_H

#include "../srcs/parser/parser.h"
#include "../srcs/builtin/builtin.h"
#include "../srcs/parser/lexer/precedence_climbing.h"
#include "../include/main.h"
#include <assert.h>


int tst_ast(void);
int tst_shutting(void);
int tst_tokenizer(void);
int tst_builtin(void);


#endif