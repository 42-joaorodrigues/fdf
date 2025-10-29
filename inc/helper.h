/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:38:45 by joao-alm          #+#    #+#             */
/*   Updated: 2025/10/29 18:27:42 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include <stddef.h>

# define BUFFER_SIZE 1069
# define FD_MAX 69

// gnl
char	*get_next_line(int fd);

// split
char	**ft_split(const char *s, char c);
// free_split
void	free_split(char **split);

// atoi_base
int		ft_atoi_base(const char *str, int base);

// atoi
int		ft_atoi(const char *nptr);

// str_util
void	ft_swap(int *a, int *b);
int		ft_abs(int n);
void	ft_putstr_fd(char *s, const int fd);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);

// gnl_util
size_t	ft_strlen(const char *s);
void	*ft_memset(void *ptr, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(char *s1, char *s2);

#endif
