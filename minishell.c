/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/09 12:59:39 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *str;
	char* username;

	username = getenv("USER"); 
	printf("\n\nUSER is: @%s", username); 
	str = readline("\n>>> "); 
	//printf()
	return (0);
}