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
			free(*line);
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
		if (ft_strncmp("$$$ exec p1 : ", *line, 10) == 0)
		{
			if (ft_strcmp("$$$ exec p1 : [./earteshc.filler]", *line) == 0)
			{
				*player = 'O';
			}
			else
			{
				*player = 'X';
			}
		}
		if (ft_strncmp(*line,"Plateau", 7) == 0)
		{
			data->row = (int)ft_atoi(*(line) + 7);
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
		free(*line);
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

	tmp = ptr;
	if (!(ptr = ft_memalloc(size)))
		return (NULL);
	if (old_size != 0 && tmp != NULL)
		ft_memcpy(ptr, tmp, old_size);
	//if (tmp != NULL)
	//	free(tmp);
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

/*int search_position(t_fdata *data)
{
	int i;

	i = 0;
	while (i <)
}*/

int main()
{
	char *line;
	t_fdata *data;
	size_t i;

	while (1)
	{
		data = (t_fdata *)malloc(sizeof(t_fdata));
		if (!(data->map = get_map(&line, &data->player, data)))
			return (0);
		if (!(data->piece = get_piece(&line)))
			return (0);
		i = 0;
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
		}
		get_piece_cords(data);
		cords_init_position(data);
		i = 0;
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
		ft_putstr_fd("default point [",2);
		ft_putnbr_fd(data->zero_point[0], 2);
		ft_putstr_fd(",",2);
		ft_putnbr_fd(data->zero_point[1], 2);
		ft_putstr_fd("]  ",2);
		ft_putstr_fd("\n",2);
		ft_free_str_arr(data->map);
		ft_free_str_arr(data->piece);
	}
		return (0);
}
