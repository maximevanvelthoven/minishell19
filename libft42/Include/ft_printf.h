/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:02:58 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/06/12 15:17:23 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int			ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_putnbr(int n, int total);
int			ft_putnbrunsigned(unsigned int n, int total);
int			ft_hexaconvert(unsigned int n, int total, char c);
int			ft_hexaconvert2(unsigned long long n, int total);
int			ft_printf(const char *str, ...);

#endif