#include "minishell.h"

char    *check_char(char c)
{
    if (c == '|')
        return ("|");
    if (c == '>')
        return (">");
    if (c == '<')
        return ("<");
    return (NULL);
}

int    ft_is_space(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

int    check_char_expand (char c)
{
    if (c == 32 || (c >= 9 && c <= 13) || c == '|'
        || c == '>' || c == '<' || c == '"' || c == '=' || c == '$' || c == '\'' || c == '\0' || c == '_')
        return (0);
    return (1);
}

int char_stop(char c)
{
    if (c == 32 || (c >= 9 && c <= 13) || c == '|'
        || c == '>' || c == '<' || c == '$' ||  c == '\0')
        return (1);
    return (0);
}
int char_continue(char c)
{
    if (c == '=' ||  c == '\'' || c == '"')
        return (1);
    return (0);
}
int check_after_d(char c)
{
    if (c == 32 || (c >= 9 && c <= 13) || c == '|'
        || c == '>' || c == '<' || c == '"' || c == '=' || c == '$' || c == '\0')
        return (0);
    return (1);
}
int    end_point(char c,int *sign)
{
    if (*sign == 0)
    {
        if (c == 32 || (c >= 9 && c <= 13) || c == '|'
            || c == '>' || c == '<' || c == '\0')
            return (0);
    }
    return (1);
}
// int    check_space(char c,char c1, int *sign)
// {
//     if (*sign == 0)
//     {
//         if (c == 32 || (c >= 9 && c <= 13) || c == '|'
//             || c == '>' || c == '<' || c == '\'' || c == '\0')
//             return (0);
//     }
//     if (*sign != 1)
//     {
//         if (c == '$' && check_after_d(c1) == 1)
//             return (0);
//     }
//     return (1);
// }
int c_after_add(char c)
{
    if ( c != '$' && c != '\'' && c != '"')
        return (1);
    return (0);
}