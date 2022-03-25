#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include "actors.h"

void init_semaphores()
{
    sem_unlink("/student_outside");
    sem_unlink("/david_available");
    sem_unlink("/question_asked");
    sem_unlink("/student_got_resp");
    sem_unlink("/student_leaving");
    student_outside = sem_open("/student_outside", O_CREAT, 0600, 0);
    david_available = sem_open("/david_available", O_CREAT, 0600, 0);
    question_asked = sem_open("/question_asked", O_CREAT, 0600, 0);
    student_got_resp = sem_open("/student_got_resp", O_CREAT, 0600, 0);
    student_leaving = sem_open("/student_leaving", O_CREAT, 0600, 0);
}

void *david_func(void *args)
{
    int i = 0;
    while (i < NUM_STUDENTS)
    {
        // look busy
        printf("David: pretends to looks busy as students arrive.\n");

        // Wait for students to signal that they've arrived. Then panic
        sem_wait(student_outside);
        printf("David: panic!!\n");

        // Signal to let in a waiting student
        sem_post(david_available);

        // Wait for student to ask a question
        sem_wait(question_asked);

        // Yell
        printf("David: yells at student!!\n");

        // Let student know I'm done answering their question
        sem_post(student_got_resp);

        // Wait for the student to leave office
        sem_wait(student_leaving);

        // good bye
        printf("David: waves goodbye!!\n");
        i++;
    }
    return NULL;
}

void *student_func(void *args)
{
    // signal to Prof that student is outside the door!
    printf("A student arrived at David's door!\n");
    sem_post(student_outside);

    // wait until Prof is ready to answer next student's question
    sem_wait(david_available);
    printf("Student: \"Hey David, do you like bananas or oranges?\"\n");

    // signal to the Prof that question has been asked
    sem_post(question_asked);

    // student waits until they get response from prof; acknowledge response
    sem_wait(student_got_resp);
    printf("Student: \"Got it! Thanks for your help!\"\n");

    // student signals to Prof that they're leaving
    sem_post(student_leaving);
    printf("Student: \"Goodbye!\"\n");
    return NULL;
}
