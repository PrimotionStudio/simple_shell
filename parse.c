#include "prime.h"

/**
 * p_is_cmd - checks if a file is executable
 * @p_info: the info structure
 * @path: the path
 * Return: 1, 0
 */
int p_is_cmd(info_t *p_info, char *path)
{
	struct stat st;

	(void)p_info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * p_dup_chars - strdup
 * @path: the path
 * @p_start: start
 * @p_stop: stop
 * Return: duplicate
 */
char *p_dup_chars(char *path, int p_start, int p_stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = p_start; i < p_stop; i++)
		if (path[i] != ':')
			buf[k++] = path[i];
	buf[k] = 0;
	return (buf);
}

/**
 * p_get_path - gets the path of a command
 * @p_info: the info structure
 * @paths: the paths
 * @p_cmd: the command
 * Return: fullpath or NULL
 */
char *p_get_path(info_t *p_info, char *paths, char *p_cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!paths)
		return (NULL);
	if ((_strlen(p_cmd) > 2) && p_starts(p_cmd, "./"))
	{
		if (p_is_cmd(p_info, p_cmd))
			return (p_cmd);
	}
	while (1)
	{
		if (!paths[i] || paths[i] == ':')
		{
			path = p_dup_chars(paths, curr_pos, i);
			if (!*path)
				_strcat(path, p_cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, p_cmd);
			}
			if (p_is_cmd(p_info, path))
				return (path);
			if (!paths[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
