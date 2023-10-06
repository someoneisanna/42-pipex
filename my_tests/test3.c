#include "../pipex.h"

int main(void)
{
	char *line;

	line = get_next_line(0);
	printf("%s", line);
}
