// Mason Shreffler
// producer.c

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>

int main()
{
	const char * name = "shared_memory";
	const char * sema1= "fill";
	const char * sema2= "available";
	const char * sema3= "mutex";
	int shm_fd;
	int * items;
	int loop = 10;  
	sem_t * fill;
	sem_t * available;
	sem_t * mutex;
	pthread_t producer;
	
	// Creates the thread
	pthread_create(&main, NULL, &producer, (void*)&amp;context);
	
	// Joins the threads together
	pthread_join(producer, NULL);
	
	// Creates the shared memory between the producer and consumer
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	
	// Sets the size of the shared memory
	ftruncate(shm_fd,sizeof(int));
	
	// Maps the shared memory to an memory address
	items = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	// Opens the semaphores
	fill = sem_open(sema1, O_CREAT, 0666, 0);
	
	// Consumer will consumer an item at the beginning starting at 3
	available = sem_open(sema2, O_CREAT, 0666, 2);
	
	// Creation of mutex for mutual exclusion of items variable
	mutex = sem_open(sema3, O_CREAT, 0666, 1);
	
	// Loops based on the number of items that producer is set to produce
	while(loop--){
		sem_wait(available);
		
		// Sleep is added to allow for consumer to consume
		sleep(rand() % 2 + 1);
		sem_wait(mutex);
		
		// If there are currently 2 items, then it will not produce another one
		(* items)++;
		sem_post(mutex);
		printf("Producer: produced an item, there are %d items now\n", * items);
		sem_post(fill);
	}
	
	// After the producer has produced the set amount of items it will stop producing and close and unlink semaphores
	// Closing semaphores
	sem_close(fill);
	sem_close(available);
	sem_close(mutex);
	
	// Unlinking semaphores
	sem_unlink(sema1);
	sem_unlink(sema2);
	sem_unlink(sema3);
	
	// Closing shared memory
	munmap(items, sizeof(int));
	close(shm_fd);
	
	// Unlinking shared memory
	shm_unlink(name);
	
	// Prints that it's done producing
	printf("Producer: Finished producing\n");
	return 0;
}