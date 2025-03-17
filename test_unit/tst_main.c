/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:17:01 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/03/17 23:31:01 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

int main(void)
{
    t_node **arbre;
    char str[] = "cat < file.txt | hello";
    
    arbre = ft_get_token_lst(str);
    if(!arbre)
        return(1);
    free(arbre);


    return(0);
}