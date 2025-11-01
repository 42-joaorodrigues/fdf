/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:38:45 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/01 19:51:17 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

# define BUFFER_SIZE 1069
# define FD_MAX 69

// gnl
char	*get_next_line(int fd);
// gnl_util
size_t	ft_strlen(const char *s);
void	*ft_memset(void *ptr, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(char *s1, char *s2);

// split
char	**ft_split(const char *s, char c);
// free_split
void	free_split(char **split);

// atois
int		ft_atoi_base(const char *str, int base);
int		ft_atoi(const char *nptr);

// int_util
void	ft_swap(int *a, int *b);
int		ft_abs(int n);

// str_util
void	ft_putstr_fd(char *s, const int fd);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);

#endif
