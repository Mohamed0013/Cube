#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "vec2.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <X11/extensions/XKB.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/time.h>

# define MLX_ERROR "Error\nmlx failed to initialize\n"

# define GREY 0x808080
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GREY 0x808080

# define MAX_DISTANCE 15

// #define INFINITY 1e30
# define PI 3.14159265359
# define FOV 80
# define R_FOV (FOV * M_PI / 180.0)

# define SPEED 1.3
# define ROT_SPEED 1.1

# define SCALE 60
# define MAP_SCALE 10
# define PLAYER_SIZE 10

# define HEIGHT 800
# define WIDTH 1200

# ifdef INPUT_MAC
# else
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define ESC_KEY 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
# endif
#define M_KEY 109
# define TEXTURE_WIDTH 64

typedef struct s_mlx		t_mlx;
typedef struct s_game		t_game;
typedef struct s_texture	t_texture;
typedef struct s_parse		t_parse;
typedef struct s_ray		t_ray;

enum						e_texture_indx
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_img
{
	void					*img;
	int						*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	int						width;
	int						height;
}							t_img;

typedef struct s_tex_info
{
	char					*north;
	char					*south;
	char					*west;
	char					*east;
	int						size;
	int						index;
	double					step;
	double					pos;
	int						x;
	int						y;
}							t_tex_info;

typedef struct s_img_wh
{
	int	*buffer;
	int	width;
	int	height;
}	t_img_wh;

typedef struct s_texture
{
	int						width;
	int						height;
	int						index;
	t_img_wh				*textures;
	int						**screen_pixels;
	t_tex_info				tex_info;
}							t_texture;

typedef struct s_parse
{
	size_t		longest;
	int			map_hight;
	int			map_width;
	char		**file;
	char		**map;
	int			pos[2];
	int			fd;
	int			lines;
	char		*elemets[6];
	char		direction;
	int			mapcolor[2][3];
}				t_parse;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_ray
{
	t_vec2		dir;
	t_vec2		delta_dist;
	t_vec2		side_dist;
	t_vec2		step;
	double		wall_dist;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			texel;
	int			tex_x;
	int			tex_y;
	double		wall_x;
}				t_ray;

typedef struct s_player
{
	double		angle;
	int			rotate;
	int			move_forward;
	int			move_back;
	int			move_left;
	int			move_right;
	double		move_speed;
	double		rot_speed;
	int			is_moving;
	t_vec2		pos;
	t_vec2		map_pos;
	t_vec2		dir;
	t_vec2		plane;
	t_ray		ray;
	int			last_mouse_x;
    int			mouse_active;
	int			is_sprinting;
}				t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;

}				t_mlx;

typedef struct s_game
{
	t_parse		*parsing;
	t_mlx		*mlx;
	t_player	*player;
	t_texture	*texture;
	t_img		current_scene;
	double		frame;
}				t_game;
int				ftx(t_texture *txxr);
void			setup_textures(t_game *game, t_texture *textrs,
					t_mlx *mlx);
void			init_img_clean(t_img *img);
void			get_txt_index(t_texture *texture, t_ray ray, int *index);
void			update_texture(t_game *game, t_ray *ray, size_t x);
int				*xpm_to_buffer(t_game *buffer, t_texture *txtr,
					t_mlx *mlx, char *path);
void			set_pixel_image(t_img *img, int x, int y,
					int color);
void			calculate_line_wall_x(t_game *game, t_ray *ray);
int				move_player(t_game *game);
int				render(t_game *game);
int				render_game(t_game *game);

t_parse			*data(void);
void			set_player_angle(t_game *game);
void			get_player_pos_and_ang(t_game *game);
double			degree_to_radian(double degree);
double			radian_to_degree(double radian);
void			handle_movement(t_player *player, t_vec2 *new_pos, int *moved);
void			handle_rotation(t_player *player, int *moved);
int				close_window(t_game *game);
void			listen_events(t_game *game);
int				key_press(int key, t_game *game);
void			interact(t_game *game);
int				is_blocking_tile(char c);
void			init_mlx_struct(t_game *game);
void			mlx(void);
int				handle_mouse(int x, int y, t_game *game);
void			toggle_mouse(t_game *game);
void			raycaster(t_game *game);
t_rgb			itorgb(int *color);
void			draw_floor(t_game *game, int x, int *y, unsigned int floor);
void			draw_ceil(t_game *game, int x, int y, unsigned int ceil);
t_rgb			clr_to_rgb(unsigned int color);
t_rgb			apply_shading(t_rgb rgb, double wall_dist);
unsigned int	rgb_to_uint(t_rgb rgb);
void			draw_floor_ceil(t_game *game);

void			setup_scene(t_game *game);
void			set_pixel_image(t_img *img, int x, int y, int color);

t_vec2			determine_first_side(t_vec2 pos, int map_x, int map_y,
					t_ray *ray);
t_vec2			calculate_plane(t_vec2 dir);

void			free_2d_array(void ***array, int size);
void			render_frame(t_game *game);

#endif
