#include <bomberman.h>

int		main(int argc, char **argv)
{
	t_game			*game;
	struct pollfd	stdinfd[1];
	long			keycode;
	
	game = NULL;
	(void)argc;
	(void)argv;
	// Init termcaps
	init_termcaps();
	// Init game.
	game = create_game();
	init_game(game);
	stdinfd[0].fd = fileno(stdin);
	stdinfd[0].events = POLLIN;
	game->elapsed_time = 0;
	game->is_running = 1;
	while (game->is_running)
	{
		render(game);

		// Handle keyboard
		keycode = 0;
		if (poll(stdinfd, 1, 1000))
		{
			if (stdinfd[0].revents & POLLIN)
			{
				read(stdinfd[0].fd,  &keycode, 8);
				handle_key(game, keycode);
			}
		}
		game->elapsed_time++;
	}
	// Do some stuff
	destroy_game(game);
	close_termcaps();
	return (0);
}
