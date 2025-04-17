/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/17 10:08:18 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

void *ft_get_output(void *p)
{
    TEST_START;
    char *line;
    char *read_line;
    size_t stdout_len;
    int b_r;

    line = (char *)p;
    read_line = NULL;
    stdout_len = 0;
    b_r = 1;
    while(b_r  > 0)
    {
       b_r = getline(&read_line, &stdout_len, stdout);
       if(b_r < 0)
       {
            printf("Erreur\n");
       }
       if(read_line)
       {
           line =  ft_strdup(read_line);
        }
        printf("voici %s\n", read_line);
    }
    TEST_SUCCES;
    return(line);
}

void tst_cd(void)
{
    TEST_START;

    pthread_t get_output;
    
    char *path;
    char *stdout_line;

    stdout_line = NULL;
    
    assert(ft_cd(NULL) == -1);
    path = ft_strdup("cd");
    assert(ft_cd(path) == 1);
    free(path);

    path = ft_strdup("cd ~/Documents");
    assert(ft_cd(path) == 1);
    free(path);

    ft_pwd("pwd");
    if(pthread_create(&get_output, NULL, ft_get_output, &stdout_line) != 0)
        return ;
    
    pthread_join(get_output, NULL);
    
    if(stdout_line)
        printf("voici %s line\n", stdout_line);
    
    //assert(ft_cd("cd .") == 1);
    assert( 1 == 2);
    TEST_SUCCES;
}


int tst_builtin(int argc, char *envp[])
{
    (void)argc;
    (void)envp;
    
    tst_cd();

    return(1);
}