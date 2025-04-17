/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_read_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:25:19 by cbouhadr          #+#    #+#             */
/*   Updated: 2025/04/17 13:29:40 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_unit.h"

typedef struct s_read_output
{
    int *on;
    pthread_mutex_t mut;

} t_read_output;


void *ft_get_output(void *p)
{
    TEST_START;
    
    int i;
    t_read_output *th;

    th = (t_read_output *)p;
    i = 1;
    while (i)
    {
        ft_pwd("pwd");
        sleep(1);
        pthread_mutex_lock(&th->mut);
        i = *(th->on);
        pthread_mutex_unlock(&th->mut);
    }
    TEST_SUCCES;
    return(p);
}

int tst_pwd_thread(char **envp)
{
    TEST_START;
    
    pthread_t thread;
    //char *line;
    char *read_line;
    size_t stdout_len;
    int is_read;
    t_read_output read_s;

    (void)envp;
    read_line = NULL;
    stdout_len = 0;
    is_read = 1;
    
    read_s.on = &is_read;
    
    if(pthread_mutex_init(&read_s.mut,NULL) != 0)
        return(-1);

    if(pthread_create(&thread, NULL, ft_get_output, &read_s) != 0)
        return(-1);

    while (1 && is_read)
    {

        getline(&read_line, &stdout_len, stdout);
        if(read_line)
        {
            printf("\n%s\n", read_line);
            // PRINT_INT((int)stdout_len);
            // //line =  ft_strdup(read_line);
            // pthread_mutex_lock(&read_s.mut);
            // is_read = 0;
            // pthread_mutex_unlock(&read_s.mut);
        }
        sleep(1);
    }
    
    if(pthread_join(thread, NULL) == 0)
        printf("thread succes\n");
    if(pthread_mutex_destroy(&read_s.mut) == 0)
        printf("thread  destroy succes\n");
    TEST_SUCCES;
    return(1);
}