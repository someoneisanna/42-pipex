#include "../pipex.h"

int main(void)
{
	char *line;

	line = get_next_line(0);
	ft_printf("%s", line);
}
