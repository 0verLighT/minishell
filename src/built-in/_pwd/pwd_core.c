/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 10:24:40 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/01 10:42:45 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*get_current_dir_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("pwd");
	return (cwd);
}

int	pwd_core(void)
{
	char	*cwd;
	size_t	len;

	len = 0;
	cwd = get_current_dir_pwd();
	if (!cwd)
		return (1);
	while (cwd[len])
		len++;
	write(1, cwd, len);
	write(1, "\n", 1);
	free(cwd);
	return (0);
}
