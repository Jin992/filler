#include "lib/includes/libft.h"
#include "filler.h"
#include "lib/includes/ft_printf.h"


char	**make_map(char **map, char **line, size_t row)
{
	size_t i;
	char *tmp;

	i = 0;
	if ((map = ft_new_str_arr(map, row)) == NULL)
		return (NULL);
	while (i < row)
	{
		free(*line);
		get_next_line(0, line);
		if (!(tmp = ft_strchr(*line, ' ')))
		{
			//free(*line);
			return (NULL);
		}
		if ((map[i++] = ft_strdup(tmp + 1)) == NULL)
			return (NULL);
	}
	free(*line);
	return (map);
}

char **get_map(char **line, char *player, t_fdata *data)
{
	char		**map;

	map = NULL;
	while (get_next_line(0, line) == 1)
	{
		if (ft_strncmp("$$$ exec", *line, 8) == 0)
		{
			if (ft_strcmp("$$$ exec p1 : [./earteshc.filler]", *line) == 0)
				*player = 'O';
			else
				*player = 'X';
		}
		if (ft_strncmp(*line,"Plateau", 7) == 0)
		{
			data->row = (int)ft_atoi(*(line) + 7);
			if (data ->row >= 100)
				data->col = (int)ft_atoi(*(line) + 12);
			else
				data->col = (int)ft_atoi(*(line) + 10);
			free(*line);
			get_next_line(0, line);
			break;
		}
		free(*line);
	}
	return (make_map(map, line, (size_t)data->row));
}

char	**make_piece(char **piece, char **line, size_t row)
{
	size_t i;

	i = 0;
	if ((piece = ft_new_str_arr(piece, row)) == NULL)
		return (NULL);
	while (i < row)
	{

		get_next_line(0, line);
		if ((piece[i++] = ft_strdup(*line)) == NULL)
			return (NULL);
		//free(*line);
	}
	//free(*line);
	return (piece);
}

char **get_piece(char **line)
{
	size_t		row;
	char		**piece;

	piece = NULL;
	row = 0;
	while (get_next_line(0, line) == 1)
	{
		if (ft_strncmp(*line,"Piece", 5) == 0)
		{
			row = (size_t)ft_atoi(*(line) + 5);
			break;
		}
		free(*line);
	}
	return (make_piece(piece, line, row));
}


void *ft_realloc_mod(void *ptr, size_t size, size_t old_size)
{
	void *tmp;

	if (old_size > 0)
	{
		if (!(tmp = malloc(old_size)))
			return (NULL);
		ft_memcpy(tmp, ptr, old_size);
		free(ptr);
	}
	if (!(ptr = ft_memalloc(size)))
		return (NULL);
	if (old_size > 0)
	{
		ft_memcpy(ptr, tmp, old_size);
		//free(tmp);
	}
	return (ptr);

}
int get_piece_cords(t_fdata *piece)
{
	int i;
	int j;
	int pieces;

	i = 0;
	pieces = 0;
	piece->x = NULL;
	piece->y = NULL;
	while (piece->piece[i] != 0)
	{
		j = 0;
		while (piece->piece[i][j] != '\0')
		{
			if (piece->piece[i][j] == '*')
			{
				pieces++;
				if (!(piece->x = ft_realloc_mod(piece->x, sizeof(int) * (pieces + 1), sizeof(int) * (pieces - 1))))
					return (-1);
				piece->x[pieces] = -1;
				piece->x[pieces - 1] = j;
				if (!(piece->y = ft_realloc_mod(piece->y, sizeof(int) * (pieces + 1), sizeof(int) * (pieces - 1))))
					return (-1);
				piece->y[pieces] = -1;
				piece->y[pieces - 1] = i;
				piece->arr_size = pieces;
			}
			j++;
		}
		i++;
	}
	return (0);
}

_Bool	zero_exist(t_fdata *data, _Bool mode)
{
	int 	i;

	i = data->arr_size;
	while (i--)
	{
		if (mode && (data->x)[i] == 0)
			return (1);
		else if (!mode && (data->y)[i] == 0)
			return (1);
	}
	return (0);
}

void	decrement(t_fdata *data, _Bool mode)
{
	int 	i;

	i = data->arr_size;
	while (i--)
	{
		if (mode)
			((data->x)[i])--;
		else
			((data->y)[i])--;
	}
}

int  cords_init_position(t_fdata *data)
{
	data->zero_point[0] = 0;
	data->zero_point[1] = 0;
	while (!zero_exist(data, 1))
	{
		((data->zero_point)[0])--;
		decrement(data, 1);
	}
	while (!zero_exist(data, 0))
	{
		((data->zero_point)[1])--;
		decrement(data, 0);
	}
	return (0);
}

_Bool check_possibility(t_fdata *data)
{
	int dot_point;
	int overlay_point;
	int i;

	dot_point = 0;
	overlay_point = 0;
	i = 0;
	while (i < data->arr_size)
	{
		if (data->map[data->y[i]][data->x[i]] == '.' )
			dot_point++;
		if (data->map[data->y[i]][data->x[i]] == data->player
			|| data->map[data->y[i]][data->x[i]] == ft_tolower(data->player))
			overlay_point++;
		i++;
	}
	if (dot_point == data->arr_size - 1 && overlay_point == 1)
		return (1);
	return (0);
}

int shift_x_cord(t_fdata *data)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < data->arr_size)
		if (data->x[i++] >= data->col - 2)
		{
			while (j < data->arr_size)
				data->x[j++] -= data->x_shift;
			data->x_shift = 0;
			return (1);
		}
	while (k < data->arr_size)
		data->x[k++]++;
	data->x_shift++;
	return (0);
}

int shift_y_cord(t_fdata *data)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (i < data->arr_size)
	{
		if (data->y[i++] > data->row - 2)
			return (1);
	}
	while (k < data->arr_size)
		data->y[k++]++;
	data->y_shift++;
	return (0);
}



int search_position(t_fdata *data)
{
	int i;

	data->x_shift = 0;
	data->y_shift = 0;
	data->decision_x = NULL;
	data->decision_y = NULL;
	data->decisions_cnt = 0;
	i = 0;
	while (i < data->row)
	{
		if (i == 1)
		{

		}
		while (1) {
		if (check_possibility(data))
			{
				data->decisions_cnt++;
				data->decision_x = ft_realloc_mod(data->decision_x, sizeof(int) * (data->decisions_cnt),
												  sizeof(int) * (data->decisions_cnt - 1));
				data->decision_x[data->decisions_cnt - 1] = data->zero_point[0] + data->x_shift;
				data->decision_y = ft_realloc_mod(data->decision_y, sizeof(int) * (data->decisions_cnt), sizeof(int) * (data->decisions_cnt - 1));
				data->decision_y[data->decisions_cnt - 1] = data->zero_point[1] + data->y_shift;
			}
			if (shift_x_cord(data) != 0)
				break;
		}
		if (shift_y_cord(data) != 0)
			break ;
		i++;
	}
	return (0);
}

/*_Bool		check_pos(char marker, t_fdata *data, int i, int j)
{
	if ((data->map)[i][j + 1] == marker ||
			((data->map[i] && (data->map)[i + 1][j] == marker))
}
*/
int enemy_marker(char marker, t_fdata *data)
{
	int i;
	int j;
	int paste;

	i = 0;
	j = 0;
	paste = 0;
	while (data->map[i] != 0)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (i > 0 && data->map[i][j] == '.' && data->map[i - 1][j] == marker)
			{
				data->map[i][j] = (marker + 1);
				paste++;
			}
			if (i < data->row - 1 && data->map[i][j] == '.' && data->map[i + 1][j] == marker)
			{
				data->map[i][j] = (marker + 1);
				paste++;
			}
			if (data->map[i][j] == '.' && data->map[i][j + 1 ] == marker)
			{
				data->map[i][j] = (marker + 1);
				paste++;
			}
			if (j > 0)
				if (data->map[i][j] == '.' && data->map[i][j - 1 ] == marker)
				{
					data->map[i][j] = (marker + 1);
					paste++;
				}
			j++;
		}
		i++;
	}
	if (paste > 0)
		enemy_marker(marker + 1, data);
	return (0);
}

int find_origin(t_fdata *data)
{
	int i;
	int j;

	i = 0;

	while (data->piece[i] != 0)
	{
		j = 0;
		while (data->piece[i][j] != '\0')
		{
			if (data->piece[i][j] == '*')
				break;
			j++;
		}
		if (data->piece[i][j] == '*')
			break ;
		i++;
	}
	data->origin_y = i;
	data->origin_x = j;
	return (0);
}

int best_place(t_fdata *data)
{
	int i;
	int index;
	int min;
	int tmp;


	min = 2147483647;
	i = 0;
	index = 0;
	data->origin_y = 0;
	data->origin_x = 0;
	find_origin(data);
	while (i < data->decisions_cnt)
	{
		//int a = data->decision_y[i] + data->origin_y;
		//int b = data->decision_x[i] + data->origin_x;
		if ((tmp = (unsigned char)data->map[data->decision_y[i] + data->origin_y][data->decision_x[i] + data->origin_x])  < min)
		{
			min = tmp;
			index = i;
		}
		i++;
	}
	data->decision_x[0] = data->decision_x[index];
	data->decision_y[0] = data->decision_y[index];
	return (0);
}

int transform_mapl(t_fdata *data)
{
	int i;
	int j;
	char marker;
	char enemy;

	i = 0;
	enemy = 'X';
	marker = '1';
	if (data->player == 'X')
		enemy = 'O';
	while (data->map[i] != 0)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == enemy || data->map[i][j] == enemy + ('a' - 'A'))
				data->map[i][j] = marker;
			if (data->map[i][j] == data->player || data->map[i][j] == data->player + ('a' - 'A'))
				data->map[i][j] = '.';
			j++;
		}
		i++;
	}
	enemy_marker('1', data);
	if (data->decision_y != NULL && data->decision_x != NULL)
		best_place(data);
	return (0);
}




int main()
{
	char *line;
	t_fdata *data;
	data = (t_fdata *)malloc(sizeof(t_fdata));
	while (1)
	{
		if (!(data->map = get_map(&line, &data->player, data)))
			return (0);
		if (!(data->piece = get_piece(&line)))
			return (0);
		/*i = 0;
		while (data->map[i] != 0)
		{
			ft_putstr_fd(data->map[i++], 2);
			ft_putstr_fd("\n",2);
		}
		ft_putstr_fd("\n", 2);
		i = 0;
		while (data->piece[i] != 0)
		{
			ft_putstr_fd(data->piece[i++], 2);
			ft_putstr_fd("\n",2);
		}*/
		get_piece_cords(data);
		cords_init_position(data);
		search_position(data);
		transform_mapl(data);

		size_t i;
		i = 0;
		while (data->map[i] != 0)
		{
			ft_putstr_fd(data->map[i++], 2);
			ft_putstr_fd("\n",2);
		}
		ft_putstr_fd("\n", 2);
		/*i = 0;
		while ((int)i < data->arr_size)
		{
			ft_putstr_fd("[",2);
			ft_putnbr_fd(data->x[i], 2);
			ft_putstr_fd(",",2);
			ft_putnbr_fd(data->y[i], 2);
			ft_putstr_fd("]  ",2);
			ft_putstr_fd("arr size[",2);
			ft_putnbr_fd(data->arr_size, 2);
			ft_putstr_fd("]  \n",2);
			i++;
		}
		i = 0;
		while ((int)i < data->arr_size)
		{
			ft_putstr_fd("\nPositions [",2);
			ft_putnbr_fd(data->decision_x[i], 2);
			ft_putstr_fd(",",2);
			ft_putnbr_fd(data->decision_y[i], 2);
			ft_putstr_fd("]  \n",2);
			i++;
		}
		ft_putstr_fd("default point [",2);
		ft_putnbr_fd(data->zero_point[0], 2);
		ft_putstr_fd(",",2);
		ft_putnbr_fd(data->zero_point[1], 2);
		ft_putstr_fd("]  ",2);
		ft_putstr_fd("\n",2);
		ft_free_str_arr(data->map);
		ft_free_str_arr(data->piece);*/
		if (data->decision_y == NULL || data->decision_x == NULL)
		{
			ft_putnbr_fd(0, 1);
			ft_putstr_fd(" ",1);
			ft_putnbr_fd(0, 1);
			ft_putstr_fd("\n",1);
		}
		else
		{
			ft_putnbr_fd(data->decision_y[0], 1);
			ft_putstr_fd(" ",1);
			ft_putnbr_fd(data->decision_x[0], 1);
			ft_putstr_fd("\n",1);
		}
		ft_free_str_arr(data->map);
		ft_free_str_arr(data->piece);
		free(data->x);
		free(data->y);
		if (data->decision_y != NULL)
			free(data->decision_y);
		if (data->decision_x != NULL)
			free(data->decision_x);
		//data->map = NULL;
		data->piece = NULL;
		//data->decision_y = NULL;
		//data->decision_y = NULL;
		data->x = NULL;
		data->y = NULL;
		data->y_shift = 0;
		data->x_shift = 0;


	}
		return (0);
}
