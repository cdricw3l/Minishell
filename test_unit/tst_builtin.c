/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/17 11:42:17 by cbouhadr         ###   ########.fr       */
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
    int is_read;

    line = (char *)p;
    read_line = NULL;
    stdout_len = 0;
    
    is_read = 0;
    while (1 && !is_read)
    {

        b_r = 1;
        while(b_r  > 0)
        {
            b_r = getline(&read_line, &stdout_len, stdout);
            if(b_r < 0)
            {
                    printf("No read\n");
                    break;
            }
            if(read_line)
            {
                line =  ft_strdup(read_line);
                printf("voici %s\n", read_line);
                is_read = 1;
                assert(1 == 2);
            }
        }
    }
    
    
    TEST_SUCCES;
    return(line);
}

void tst_cd(void)
{
    TEST_START;

    char *path;
    
    assert(ft_cd(NULL) == -1);
    path = ft_strdup("cd");
    assert(ft_cd(path) == 1);
    free(path);

    path = ft_strdup("cd ~/Documents");
    assert(ft_cd(path) == 1);
    free(path);
    
    path = ft_strdup("cd ~");
    assert(ft_cd(path) == 1);
    free(path);
    
    path = ft_strdup("cd ..");
    assert(ft_cd(path) == 1);
    free(path);

    path = ft_strdup("cd .");
    assert(ft_cd(path) == 1);
    free(path);

    path = ft_strdup("cd feqffq");
    assert(ft_cd(path) == -1);
    free(path);
    
    path = ft_strdup("cd ~/Documents fqe");
    assert(ft_cd(path) == -1);
    free(path);


    TEST_SUCCES;
}


int tst_builtin(int argc, char *envp[])
{
    (void)argc;
    (void)envp;
    
    tst_cd();

    return(1);
}