# include <bomberman.h>

t_mod	*load_mod(const char *path)
{
	int			fd;
	char		buffer[BUFFER_SIZE];
	t_mod		*mod;
	size_t		i;
	int			j;

	if (!(fd = open(path, O_RDONLY)))
		return (NULL);
	if (!(read(fd, buffer, BUFFER_SIZE)))
		return (NULL);
	if (!(mod = (t_mod *)malloc(sizeof(t_mod))))
		return (NULL);
	// nom de la maps
	mod->name = strndup(buffer, strlen(buffer) - strlen(strchr(buffer, '\n')));	
	mod->name[strlen(mod->name)] = '\0';
	i = 0;
	mod->maps_count = 0;
	// nombre de maps
	while (i < strlen(buffer))
	{
		if (buffer[i] == '\n')
			mod->maps_count++;
		i++;
	}
	// Allocation de l'ordre des maps
	if (!(mod->maps = (int *)malloc(sizeof(int) * mod->maps_count)))
		return (NULL);
	i = strlen(mod->name) + 1;
	j = 0;
	// Attention parsing naif remplacer par copie de chaine (la ligne) + atoi
	while (i < strlen(buffer))
	{
		if (buffer[i] != '\n')
		{
			mod->maps[j] = buffer[i] - 48;
			j++;
		}
		i++;
	}
	close(fd);
	return (mod);
}

void	release_mod(t_mod *mod)
{
	free(mod->name);
	free(mod->maps);
	free(mod);
	mod = NULL;
}
