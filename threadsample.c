#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// sample de https://www.youtube.com/watch?v=NAKrOZCcJ4A

void *thread_routine(void *arg)
{
	int		nr_lines = *((int*)arg);
	int		fd;
	char	buf[] = "Nueva linea \n";

	for (int i = 0; i < nr_lines; i++)
	{
		fd = open("test.txt", O_WRONLY|O_APPEND);
		write (fd, buf, sizeof(buf) - 1);
		close(fd);
	}
return (NULL);
}

int main (int argc, char **argv)
{
	pthread_t thread1; // estructura de threads - compilar con gcc threads.c -pthread
	int value = atoi(argv[1]);

	if (0 != pthread_create(&thread1, NULL, thread_routine, &value))
		return (-1);
	pthread_join(thread1, NULL); //para funcion padre esperar el thread ejecutar antes de seguir.

	return (0);
}