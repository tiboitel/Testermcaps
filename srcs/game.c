# include <bomberman.h>

t_game		*create_game()
{
	t_game	*game;

	game = NULL;
	if (!(game = (t_game *)malloc(sizeof(t_game))))
		return (NULL);
	return (game);
}

int			init_game(t_game *game)
{
	if (!(game->mod = load_mod(BASIC_MOD_NAME)))
		return (-1);
	if (!(game->player = create_player()))
		return (-1);
	if (!(game->map = create_map(BASIC_MAPS_PATH, game->mod->maps[0])))
		return (-1);
	return (1);
}

void		render(t_game *game)
{
	int		i;

	i = 0;
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	while (i < game->map->row)
	{
		write(1, game->map->data[i], strlen(game->map->data[i]));
		i++;
	}
	tputs(tgoto(tgetstr("cm", NULL), game->player->x, game->player->y), 1, ft_putc);
	write(1, "P", 1);
	tputs(tgetstr("ho", NULL), 1, ft_putc);
}

void		destroy_game(t_game *game)
{
	if (game->mod)
		release_mod(game->mod);
	if (game->player)
		destroy_player(game->player);
	if (game->map)
		destroy_map(game->map);
	free(game);
	game = NULL;
}

void		handle_key(t_game *game, long keycode)
{
	if (keycode == LEFT_ARROW)
		player_move(game, game->player->x - 1, game->player->y);
	else if (keycode == RIGHT_ARROW)
		player_move(game, game->player->x + 1, game->player->y);
	else if (keycode == UP_ARROW)
		player_move(game, game->player->x, game->player->y - 1);
	else if (keycode == DOWN_ARROW)
		player_move(game, game->player->x, game->player->y + 1);
	else if (keycode == ESC_KEY)
		game->is_running = 0;

}
