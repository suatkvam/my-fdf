#include "libft.h"
#include"get_next_line_bonus.h"

char	*ft_strjoin(const char *stash, const char *buffer)
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
	free((void *)stash);
	return (new_str);
}

char	*extract_line(char *stash)
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

char	*update_stash(char *stash)
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

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*buffer;
	ssize_t		read_byte;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash[fd], '\n'))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
			return (free(buffer), NULL);
		if (read_byte == 0)
			break ;
		buffer[read_byte] = '\0';
		stash[fd] = ft_strjoin(stash[fd], buffer);
	}
	free(buffer);
	line = extract_line(stash[fd]);
	stash[fd] = update_stash(stash[fd]);
	return (line);
}
