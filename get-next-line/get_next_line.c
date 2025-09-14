#include "get_next_line.h"
#include "libft.h"

static char	*gnl_ft_strjoin(char *stash, const char *buffer)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	if (!stash)
		stash = ft_strdup("");
	if (!stash || !buffer)
		return (NULL);
	new_str = ft_calloc(1, (ft_strlen(stash) + ft_strlen(buffer) + 1));
	if (!new_str)
		return (NULL);
	len = ft_strlen(stash);
	while (i < len)
	{
		new_str[i] = stash[i];
		i++;
	}
	while (j < ft_strlen(buffer))
		new_str[i++] = buffer[j++];
	new_str[i] = '\0';
	return (new_str);
}
static char	*extract_line(char *stash)
{
	char	*newline;
	size_t	i;

	i = 0;
	if (!stash || stash[0] == '\0')
		return (NULL);
	newline = ft_strchr(stash, '\n');
	if (newline)
		i = (newline - stash) + 1;
	else
		i = ft_strlen(stash);
	return (ft_substr(stash, 0, i));
}

static char	*update_stash(char *stash)
{
	char	*new_stash;
	char	*new_line;

	if (!stash)
		return (NULL);
	new_line = ft_strchr(stash, '\n');
	if (!new_line)
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(new_line + 1);
	free(stash);
	return (new_stash);
}
static char	*read_line(int fd, char *stash)
{
	char	*buffer;
	ssize_t	read_byte;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	while (!stash || !ft_strchr(stash, '\n'))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			free(stash);
			stash = NULL;
			return (NULL);
		}
		if (read_byte == 0)
			break ;
		buffer[read_byte] = '\0';
		stash = gnl_ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	stash = read_line(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}
