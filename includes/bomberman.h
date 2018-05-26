/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 17:35:32 by tiboitel          #+#    #+#             */
/*   Updated: 2018/05/27 00:23:38 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BOMBERMAN_H
# define FT_BOMBERMAN_H

# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <poll.h>

# define BASIC_MAPS_PATH "./basic_mod/niveaux/"
# define BASIC_MOD_NAME "./basic_mod/deroulement"
# define BUFFER_SIZE 1024
# define UP_ARROW 4283163
# define DOWN_ARROW	4348699
# define LEFT_ARROW	4479771
# define RIGHT_ARROW 4414235
# define ESC_KEY 27

typedef struct			s_game
{
	struct s_mod		*mod;
	struct s_map		*map;
	struct s_player		*player;
	int					elapsed_time;
	int					is_running;
}						t_game;

t_game					*create_game();
int						init_game(t_game *game);
void					destroy_game(t_game *game);
void					render();
void					handle_key(t_game *game, long keycode);
/*
 ** 1. Termcaps section.
 */

int			ft_putc(int c);
int			init_termcaps(void);
int			close_termcaps(void);

/*
 ** 2. Mods section.
 */

typedef struct		s_mod
{
	char			*name;
	size_t			maps_count;
	int				*maps;
}					t_mod;

t_mod				*load_mod(const char *path);
void				release_mod(t_mod *mod);
/*
 ** 3. Maps section.
 */

typedef struct		s_map
{
	char			**data;
	int				row;
	int				col;
}					t_map;

t_map				*create_map(const char *path, int id);
void				destroy_map(t_map *map);

/*
 ** 4. Player section.
 */
typedef struct		s_player
{
	int				x;
	int				y;
	int				health;
}					t_player;					

t_player			*create_player();
void				player_move(t_game *game, int x, int y);
void				destroy_player();

/*
 ** 5. Tools
 */
#endif
