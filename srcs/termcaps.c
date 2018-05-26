#include <bomberman.h>

int		ft_putc(int c)
{
	int		fd;

	if (!(fd = open("/dev/tty", O_RDWR)))
		return (-1);
	write(fd, &c, 1);
	close(fd);
	return (c);
}

int		init_termcaps(void)
{
	char			*name_term;
	struct termios	term;

	if (!(name_term = getenv("TERM")) || tgetent(NULL, name_term) == -1 ||
			tcgetattr(0, &term) == -1)
	{
		return (-1);
	}
	// Passage en mode canonique. Echo permet d'eviter d'afficher les touches.
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	// Nombre minimum de caractere par lecture et vitesse de lecture.
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	// Modifier parametre du terminal.
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	// Doit etre mis pour fullcreen display cf. man
	tputs(tgetstr("ti", NULL), 1, ft_putc);
	// Curseur invisible "vi"
	tputs(tgetstr("vi", NULL), 1, ft_putc);
	return (1);
}

int		close_termcaps(void)
{
	struct termios	term;

	// Rendre le curseur visible de nouveau.
	tputs(tgetstr("ve", NULL), 1, ft_putc);
	tputs(tgetstr("te", NULL), 1, ft_putc);
	tputs(tgetstr("cl", NULL), 1, ft_putc);
	// Recupere les options du term
	if (tcgetattr(0, &term) == -1)
		return (-1);
	// Supression du monde canonique
	term.c_lflag ^= ~(ICANON | ECHO);
	// Mise en effet du mode
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (1);
}
