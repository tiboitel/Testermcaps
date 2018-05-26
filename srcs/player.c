# include <bomberman.h>

t_player	*create_player()
{
	t_player	*player;

	player = NULL;
	if (!(player = (t_player *)malloc(sizeof(t_player))))
		return (NULL);
	player->x = 1;
	player->y = 1;
	player->health = 3;
	return (player);
}

void		player_move(t_game *game, int x, int y)
{
	if (game->map->data[y][x] != ' ')
		return ;
	game->player->x = x;
	game->player->y = y;
}

void		destroy_player(t_player *player)
{
	free(player);
	player = NULL;
}
