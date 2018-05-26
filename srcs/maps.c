# include <bomberman.h>

static char			*get_file_path(const char *path, int id)
{
	char			*file_path;
	int				i;

	if (!(file_path = (char *)malloc(sizeof(char) * strlen(path) + 2)))
		return (NULL);
	memcpy(file_path, path, strlen(path));
	i = strlen(path);
	file_path[i] = id + 48;
	file_path[i + 1] = '\0';
	return (file_path);
}

t_map				*create_map(const char *path, int id)
{
	t_map	*map;
	FILE	*fp;
	char	*file_path;
	ssize_t	bytes_read;
	size_t	length;
	char	*buffer;
	size_t	row;
	int		i = 0;

	map = NULL;
	file_path = NULL;
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	if (!(file_path = get_file_path(path, id)))
		return (NULL);
	if (!(fp = fopen(file_path, "r+")))
	{
		return (NULL);
	}
	free(file_path);
	bytes_read = 0;
	row = 0;
	while ((bytes_read = getline(&buffer, &length, fp)) != -1)
		row++;
	bytes_read = 0;
	rewind(fp);
	if (!(map->data = (char **)malloc(sizeof(char *) * row)))
		return (NULL);
	while ((bytes_read = getline(&buffer, &length, fp)) != -1)
	{
		if (i == 0)
		{
			map->row = atoi(buffer);
			map->col = atoi(strchr(buffer, ' '));
		}
		else
		{
	 		map->data[i - 1] = strndup(buffer, strlen(buffer));
		}
		i++;
	}
	map->data[i - 1] = NULL;
	fclose(fp);
	return (map);
}

void				destroy_map(t_map *map)
{
	int		i;

	i = 0;
	while (i++ < map->row)
		free(map->data[i]);
	free(map->data);
	free(map);
	map = NULL;
}
