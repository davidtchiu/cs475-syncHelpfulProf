#define NUM_STUDENTS 2

// globals
sem_t *student_outside;
sem_t *david_available;
sem_t *question_asked;
sem_t *student_got_resp;
sem_t *student_leaving;

// function declarations
void init_semaphores();
void *david_func(void *args);
void *student_func(void *args);