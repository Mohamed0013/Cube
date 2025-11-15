#ifndef PARSER_H
# define PARSER_H
#include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
// map color index 0 for floor 1 for sky
char	*get_next_line(int fd);
int		check_size(char **c, char **f);
void	freedouble(char **str);
char	**ft_splits(char *str);
char	**ft_spitv(char *str);
int		isallspace(char *line);
int		freefile(char **tofree);
int		freeelement(void);
int		checkmap(char *line);
void	charsinmap(void);
int		ft_strcmp(char *s1, char *s2);
size_t	get_longest_line(void);
void	fix_map(void);
void	issurrendbywalls(void);
void	ft_exit(char **floor, char **ceiling, char **toaoitc, char **toaoitf);
void	copymap(void);
void	isdupchars(void);
int		fixe_file(void);
#endif
