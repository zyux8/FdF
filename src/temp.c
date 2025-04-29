void read_map(int fd, t_map *map)
{
    char **split;
    char *line;
    int x;
    int y;
    int current_width;

	x = 0;
    // map->height = ft_count_lines(fd);
    map->height = 4;
    // lseek(fd, 0, SEEK_SET);
	close(fd);
	printf("first\n");
	fd = open("test.fdf", O_RDONLY);
	printf("second\n");
    map->z_matrix = malloc(sizeof(int *) * map->height);
	printf("third\n");
    if (!map->z_matrix)
    {
		printf("Error allocating memory for z_matrix\n");
		free_z_matrix(map->z_matrix, x);
		map->z_matrix = NULL;
        return;
    }
	printf("fourth\n");
    while ((line = get_next_line(fd)))
    {
		printf("fifth\n");
		split = ft_split(line, ' ');
		if (!split)
        {
			printf("Error: ft_split failed\n");
            free(line);
            free_z_matrix(map->z_matrix, x);
            map->z_matrix = NULL;
            return;
        }
        current_width = 0;
        while (split[current_width])
		{
			printf("split[%d] = %s\n", current_width, split[current_width]);
            current_width++;
		}
		if (x == 0)
		map->width = current_width;
        else if (current_width != map->width)
		{
			printf("Error: Inconsistent line width at line %d (expected %d, got %d)\n", x, map->width, current_width);
			free(line);
			ft_free_split(split);
			free_z_matrix(map->z_matrix, x);
			return;
		}        
		map->z_matrix[x] = malloc(sizeof(int) * current_width);
        if (!map->z_matrix[x])
        {
            printf("Error allocating memory for row %d\n", x);
            return;
        }
        y = 0;
        while (y < current_width)
        {
            map->z_matrix[x][y] = ft_atoi(split[y]);
            y++;
        }
        ft_free_split(split);
        free(line);
        x++;
    }
	close(fd);
}