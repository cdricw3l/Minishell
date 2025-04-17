// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tst_export.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/26 10:52:29 by cbouhadr          #+#    #+#             */
// /*   Updated: 2025/04/12 07:24:20 by cw3l             ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "test_unit.h"

/* 
    Error msg:  export 1hello = export: not an identifier: 1hello
                export hello# = export: not valid in this context: hello#
                export hello* = zsh: no matches found: hello*
                export =d     = zsh: d not found
                export a==1   = zsh: 1 not found

*/

// int ft_tst_check_variable(void)
// {
//     TEST_START;
//      // valide arg:
//     char *var_test_1 = "H=0000";
//     char *var_test_2 = "H00000";
//     char *var_test_3 = "H=hello";
//     char *var_test_4 = "HelloWorld";

//     // In valide args

//     char *invar_test_1 = "100H";
//     char *invar_test_2 = "H=hello*";
//     char *invar_test_3 = "H=hello*";
//     char *invar_test_4 = "1hello";
//     char *invar_test_5 = "hello#";
//     char *invar_test_6 = "hello*";
    

//     assert(ft_check_variable_export(var_test_1) == 1);
//     assert(ft_check_variable_export(var_test_2) == 1);
//     assert(ft_check_variable_export(var_test_3) == 1);
//     assert(ft_check_variable_export(var_test_4) == 1);

//     assert(ft_check_variable_export(invar_test_1) == 0);
//     assert(ft_check_variable_export(invar_test_2) == 0);
//     assert(ft_check_variable_export(invar_test_3) == 0);
//     assert(ft_check_variable_export(invar_test_4) == 0);
//     assert(ft_check_variable_export(invar_test_5) == 0);
//     assert(ft_check_variable_export(invar_test_6) == 0);
//     TEST_SUCCES;
//     return(1);
// }

// int ft_tst_count_variable(void)
// {
//     TEST_START;
    
//     char *str[] = {"H=0000", "H00000", "H=hello", "H=hello*", NULL};
//     assert(ft_count_valide_variable(str) == 3);
//     assert(ft_count_valide_variable(NULL) == 0);

//     char *str2[] = {"100H", "H=hello*", "H=hello", "H=hello*", NULL};
//     assert(ft_count_valide_variable(str2) == 1);
    
//     char *str3[] = {"100H", "H=hello*", "1hello", "H=hello#", NULL};
//     assert(ft_count_valide_variable(str3) == 0);
    
//     char *str4[] = {"E=0000", "HelloWorld", "F=hello", "G=world", NULL};
//     assert(ft_count_valide_variable(str4) == 4);
    
//     char *str5[] = {"E=00s00", NULL, "F=hello", "G=world", NULL};
//     assert(ft_count_valide_variable(str5) == 1);
    
//     TEST_SUCCES;
//     return (1);
// }

// int  ft_tst_add_var(void)
// {
//     TEST_START;
//     char *str = "hello world comment ca va ?";
//     char *str2 = "bien merci je t'en prie";
//     char **env = ft_split(str, 32);
//     char **add = ft_split(str2, 32);
    
//     char **new = ft_add_variable(env, add);
//     free(env);
//     free(add);
    
//     ft_split_clean(&new);
//     (void)new;
//     TEST_SUCCES;
//     return(1);    
// }

char **ft_get_empty_env(int n)
{
    char **env_simulation;
    int i;

    i = 0;
    env_simulation = malloc(sizeof(char *) * (n + 1));
    if(!env_simulation)
        return(NULL);
    while (i < n)
    {
        env_simulation[i] = NULL;
        i++;
    }
    env_simulation[i] = NULL;
    return(env_simulation);
}

int tst_export(char **envp)
{
    // REVOIR LA FONCTION DE TRIE DE L'ENV
    TEST_START;

    (void)envp;
    char **split_valide;
    char **split_invalide;
    char **env_simulation;

    // valide arg:
    char *invar_test_1 = "export 100H  H=hello*, export 1hello, export hello#, export hello*";
    char *var_test = "export H=0000 , export H00000, export H=hello, export HelloWorld";

      // invalide arg:
    env_simulation = ft_get_empty_env(10);
    if(!env_simulation)
        return(-1);
    split_valide = ft_split(var_test, ',');
    split_invalide = ft_split(invar_test_1, ',');
    if(!split_valide)
        return(-1);
    if(!split_invalide)
    {
        ft_split_clean(&split_valide);
        return(-1);
    }
    
    assert(ft_export(&envp, NULL) == -1);
    assert(ft_export(NULL, split_valide[0]) == -1);
    //printf("voici %s\n", trimed);
    //assert(ft_export(&env_simulation,trimed) == 1);
    int i = 0;
    while (split_valide[i])
    {
        char *trimed = ft_strtrim(split_valide[i], " ");
        assert(ft_export(&env_simulation,trimed) == 1);
        //ft_split_print(env_simulation);
        //printf("%s\n", env_simulation[i]);
        //char *cmp = ft_strchr(trimed, 't') + 1;
        // char *trimed2 = ft_strtrim(cmp, " ");
        // printf( "voici %s et %s et %s\n", trimed2, trimed, env_simulation[i]);
        // assert(ft_strncmp(trimed2,env_simulation[i], ft_strlen_longest(trimed2,env_simulation[i])) == 0);
        free(trimed);
        //free(trimed2);
        i++;
    }
    ft_split_clean(&split_invalide);
    ft_split_clean(&split_valide);
    ft_split_clean(&env_simulation);
    TEST_SUCCES;
    return(1);
}