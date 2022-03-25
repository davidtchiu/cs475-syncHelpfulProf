#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include "actors.h"

int main(int argc, char *argv[])
{
	int i = 0;
	init_semaphores();

	// create professor and student threads
	pthread_t *david = (pthread_t *)malloc(sizeof(pthread_t));
	pthread_t *students = (pthread_t *)malloc(NUM_STUDENTS * sizeof(pthread_t));

	pthread_create(david, NULL, david_func, NULL);
	for (i = 0; i < NUM_STUDENTS; i++)
	{
		pthread_create(&students[i], NULL, student_func, NULL);
	}

	for (i = 0; i < NUM_STUDENTS; i++)
	{
		pthread_join(students[i], NULL);
	}
	pthread_join(*david, NULL);

	// close semaphores
	sem_close(student_outside);
	sem_close(david_available);
	sem_close(question_asked);
	sem_close(student_got_resp);
	sem_close(student_leaving);

	// delete semaphores
	sem_unlink("/student_outside");
	sem_unlink("/david_available");
	sem_unlink("/question_asked");
	sem_unlink("/student_got_resp");
	sem_unlink("/student_leaving");

	free(david);
	free(students);

	return 0;
}
