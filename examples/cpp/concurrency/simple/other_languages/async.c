/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * C implementation of async.cpp (spawn a single
 * thread to perform an operation asynchronously).
 *
 * To compile:
 *
 *     gcc async.c -pthread -o async
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


/* The thread can only take a single void* parameter,
 * so we create a struct to encapsulate the parameters. */
struct multiplyArgs
{
	int a;
    int b;
};

void *multiply(void *args)
{
    /* Unpack arguments */
    int a = ((struct multiplyArgs*) args)->a;
    int b = ((struct multiplyArgs*) args)->b;

    int *retval = malloc(sizeof(int));
    *retval = a*b;

    return retval;
}


int main(int argc, char *argv[])
{
	/* The pthread_t type is a struct representing a single thread. */
	pthread_t multiply_thread;

    /* Parameters to the thread function */
    struct multiplyArgs* ma;

    /* Used to collect the return value of the thread */
    void *retval;
    

	/* The pthread_create function creates a new thread.
	   The first parameter is a pointer to a pthread_t variable, which we can use
	   in the remainder of the program to manage this thread.
	   The second parameter is used to specify the attributes of this new thread
	   (e.g., its stack size). We can leave it NULL here.
	   The third parameter is the function this thread will run. This function *must*
	   have the following prototype:

	       void *f(void *args);

	   Note how the function expects a single parameter of type void*. The fourth
	   parameter to pthread_create is used to specify this parameter. 
	   We will typically malloc a struct with the necessary args (in this case,
       we will use the multiplyArgs struct defined above. The thread function 
       is typically responsible for freeing this struct.

       If the thread function takes no arguments, the fourth parameter to
       pthread_create will be NULL.
    */

	ma = malloc(sizeof(struct multiplyArgs));
	ma->a = 2;
	ma->b = 3;

	if (pthread_create(&multiply_thread, NULL, multiply, ma) != 0) 
	{
		perror("Could not create the thread");
		free(ma);
		pthread_exit(NULL);
	}

    /* The pthread_join waits for the multiply_thread thread to finish.
       The void* returned by the thread is stored in the retval variable */
	if (pthread_join(multiply_thread, &retval) != 0) 
    {
		perror("Could not join the thread");
		pthread_exit(NULL);
    }

    printf("The thread returned %i\n", *((int *) retval));

    /* Free the return value (malloc'd by the thread) */
    free(retval);

	pthread_exit(NULL);
}

