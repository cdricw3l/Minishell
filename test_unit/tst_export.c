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

// #include "test_unit.h"

// /* 
//     Error msg:  export 1hello = export: not an identifier: 1hello
//                 export hello# = export: not valid in this context: hello#
//                 export hello* = zsh: no matches found: hello*
//                 export =d     = zsh: d not found
//                 export a==1   = zsh: 1 not found

// */

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
    

//     assert(ft_check_variable(var_test_1) == 1);
//     assert(ft_check_variable(var_test_2) == 1);
//     assert(ft_check_variable(var_test_3) == 1);
//     assert(ft_check_variable(var_test_4) == 1);

//     assert(ft_check_variable(invar_test_1) == 0);
//     assert(ft_check_variable(invar_test_2) == 0);
//     assert(ft_check_variable(invar_test_3) == 0);
//     assert(ft_check_variable(invar_test_4) == 0);
//     assert(ft_check_variable(invar_test_5) == 0);
//     assert(ft_check_variable(invar_test_6) == 0);
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

// int tst_export(char *envp[])
// {
//     // REVOIR LA FONCTION DE TRIE DE L'ENV
//     TEST_START;
//     (void)envp;

//     // char *ss = ft_strdup("hello=world");
    
//     // char *s = ft_extract_var(ss);
    
//     // printf("voici %s\n",s);

    
//     assert(ft_tst_check_variable() == 1);
//     assert(ft_tst_count_variable() == 1);
//     assert(ft_tst_add_var() == 1);
    
//     char **d = ft_duplicate_env(envp);
//     env_quick_s(d,ft_get_split_len(envp),ft_str_env_cmp);
//     ft_display_env(d);

//     // char **e = ft_duplicate_env(envp);
//     // char *env = "Z1=0 Z2=1 Z3=22";
//     // char **split = ft_split(env,32);

//     // assert(ft_is_split_sort(e));
    
//     //int actual_len = ft_get_split_len(e);

//     //ft_export(&e, &split);

//     // int new_len = ft_get_split_len(e);

//     // char *d = "Z22=101 Z2=101 ";
//     // char **pli = ft_split(d,32);
    
//     // actual_len = ft_get_split_len(e);
    
//     // PRINT_INT(actual_len);
//     // ft_export(&e, &pli);

//     // new_len = ft_get_split_len(e);
    
//     // PRINT_INT(new_len);
//     // assert(new_len == actual_len + 1);

    
//     // //test for dupplicate variable.
//     // char *p = "Z=0 Z=1 Z=2";
//     // char **plit = ft_split(p, 32);
    
//     // actual_len = ft_get_split_len(e);
    
//     // ft_export(&e, &plit);
    
//     // new_len = ft_get_split_len(e);
    
//     // assert(ft_is_env_sort(e));

//     // printf("voici la  len %d and %d\n", new_len, actual_len);
//     // assert(ft_is_env_sort(e) && new_len == actual_len + 1);


//     // char *ps = "Z33=2333 Z78=0";
//     // char **lit = ft_split(ps, 32);
//     // ft_export(&e, &lit);
    
//     //ft_split_clean(&e);
//     TEST_SUCCES;
//     return(1);
// }