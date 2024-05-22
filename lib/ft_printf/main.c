/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:09:09 by jcummins          #+#    #+#             */
/*   Updated: 2024/01/24 11:49:12 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*void	test_ptr(void)*/
/*{*/
	/*void	*a;*/
	/*void	*b;*/
	/*void	*c;*/
	/*void	*d;*/
	/*int	result;*/

	/*a = malloc(1);*/
	/*b = malloc(1);*/
	/*c = malloc(1);*/
	/*d = malloc(1);*/
	/*printf("\nTesting ft_printf pointers with %%p:\n\n");*/
	/*result = ft_printf("\t%p %p %p %p\n", a, b, c, d) -*/
		/*printf("\t%p %p %p %p\n", a, b, c, d);*/
	/*if (result == 0)*/
		/*printf("\tft_printf returns correct values\n");*/
	/*else*/
		/*printf("\tft_printf returns incorrect values\n");*/
	/*free(a);*/
	/*free(b);*/
	/*free(c);*/
	/*free(d);*/
/*}*/

/*void	test_hex(int a, int b, int c, int d)*/
/*{*/
	/*int	result;*/

	/*printf("\nTesting ft_printf lowercase hexadecimals with %%x:\n\n");*/
	/*result = ft_printf("\t%x %x %x %x\n", a, b, c, d) -*/
		/*printf("\t%x %x %x %x\n", a, b, c, d);*/
	/*if (result == 0)*/
		/*printf("\tft_printf returns correct values\n");*/
	/*else*/
		/*printf("\tft_printf returns incorrect values\n");*/
/*}*/

/*void	test_Hex(int a, int b, int c, int d)*/
/*{*/
	/*int	result;*/

	/*printf("\nTesting ft_printf uppercase hexadecimals with %%X:\n\n");*/
	/*result = ft_printf("\t%X %X %X %X\n", a, b, c, d) -*/
		/*printf("\t%X %X %X %X\n", a, b, c, d);*/
	/*if (result == 0)*/
		/*printf("\tft_printf returns correct values\n");*/
	/*else*/
		/*printf("\tft_printf returns incorrect values\n");*/
/*}*/

/*void	test_u(int a, int b, int c, int d)*/
/*{*/
	/*int	result;*/

	/*printf("\nTesting ft_printf unsigned integers with %%i:\n\n");*/
	/*result = ft_printf("\t%u %u %u %u\n", a, b, c, d) -*/
		/*printf("\t%u %u %u %u\n", a, b, c, d);*/
	/*if (result == 0)*/
		/*printf("\tft_printf returns correct values\n");*/
	/*else*/
		/*printf("\tft_printf returns incorrect values\n");*/
/*}*/

/*void	test_int(int a, int b, int c, int d)*/
/*{*/
	/*int	result;*/

	/*printf("\nTesting ft_printf integers with %%i:\n\n");*/
	/*result = ft_printf("\t%i %i %i %i\n", a, b, c, d) -*/
		/*printf("\t%i %i %i %i\n", a, b, c, d);*/
	/*if (result == 0)*/
		/*printf("\tft_printf returns correct values\n");*/
	/*else*/
		/*printf("\tft_printf returns incorrect values\n");*/
/*}*/

/*void	test_dec(int a, int b, int c, int d)*/
/*{*/
	/*int	result;*/

	/*printf("\nTesting ft_printf decimals with %%d:\n\n");*/
	/*result = ft_printf("\t%d %d %d %d\n", a, b, c, d) -*/
		/*printf("\t%d %d %d %d\n", a, b, c, d);*/
	/*if (result == 0)*/
		/*printf("\tft_printf returns correct values\n");*/
	/*else*/
		/*printf("\tft_printf returns incorrect values\n");*/
/*}*/

/*void	test_char(void)*/
/*{*/
	/*char	a;*/
	/*char	b;*/
	/*char	c;*/
	/*char	d;*/
	/*int		result;*/

	/*a = 'r';*/
	/*b = '&';*/
	/*c = '"';*/
	/*d = ' ';*/
	/*printf("\nTesting ft_printf with %%c for chars:\n\n");*/
	/*result = ft_printf("\t%d %d %d %d\n", a, b, c, d) -*/
		/*printf("\t%d %d %d %d\n", a, b, c, d);*/
	/*if (result == 0)*/
		/*printf("\tft_printf returns correct values\n");*/
	/*else*/
		/*printf("\tft_printf returns incorrect values\n");*/
/*}*/

/*void	test_str(void)*/
/*{*/
	/*char	*a;*/
	/*char	*b;*/
	/*char	*c;*/
	/*char	*d;*/
	/*int		result;*/

	/*a = "Hello there";*/
	/*b = "5 Gold Rings";*/
	/*c = "Four Calling Birds";*/
	/*d = "343toiredfgsrTy5 q45 W45tw 4ii hggw45t5 	43t";*/
	/*printf("\nTesting ft_printf with %%s for strings:\n\n");*/
	/*result = ft_printf("\t%s %s %s %s\n", a, b, c, d) -*/
		/*printf("\t%s %s %s %s\n", a, b, c, d);*/
	/*if (result == 0)*/
		/*printf("\tft_printf returns correct values\n");*/
	/*else*/
		/*printf("\tft_printf returns incorrect values\n");*/
/*}*/

/*int	main(void)*/
/*{*/
	/*int	a;*/
	/*int	b;*/
	/*int	c;*/
	/*int	d;*/

	/*a = 42;*/
	/*b = -42;*/
	/*c = 0;*/
	/*d = 2147483647;*/

	/*printf("Running tests\n");*/
	/*sleep (1);*/
	/*test_ptr();*/
	/*sleep (1);*/
	/*test_hex(a, b, c, d);*/
	/*sleep (1);*/
	/*test_Hex(a, b, c, d);*/
	/*sleep (1);*/
	/*test_u(a, b, c, d);*/
	/*sleep (1);*/
	/*test_int(a, b, c, d);*/
	/*sleep (1);*/
	/*test_dec(a, b, c, d);*/
	/*sleep (1);*/
	/*test_char();*/
	/*sleep (1);*/
	/*test_str();*/
	/*return (0);*/
/*}*/
