// Mason Shreffler
// consumer.c

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>

int main()
{
	const char * name = "shared_memory";
	const char * sema1 = "fill";
	const char * sema2 = "available";
	const char * sema3 = "mutex";
	int shm_fd;
	int * items;
	int loop = 10;
	sem_t * fill;
	sem_t * available;
	sem_t * mutex;
	pthread_t consumer;
  
	// Creates the thread
	pthread_create(&main, NULL, &consumer, (void*)&amp;context);

	// Joins the threads together
	pthread_join(consumer, NULL);

	// Creates the shared memory between the producer and consumer
	shm_fd = shm_open(name, O_RDWR, 0666);

	// Maps the shared memory to an memory address
	items = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

	// Opens the semaphores
	fill = sem_open(sema1, O_CREAT, 0666, 0);
	available = sem_open(sema2, O_CREAT, 0666, 2);
	mutex = sem_open(sema3, O_CREAT, 0666, 1);

	// Consumer will keep looping until it consumes the set amount of items predetermined in the loop variable of both programs
	while(loop--){
		sem_wait(fill);

    // Sleeps to let the producer produce an item
    sleep(rand() % 2 + 1);
	
    // Waits until there is an item to consume
    sem_wait(mutex);
    (* items)--;
    sem_post(mutex);
    printf("Consumer: I have consumed an item\n");
    sem_post(available);
	}
	
	// Removes the semaphores
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
	
	// Prints that it's done consuming
	printf("Consumer: Finished consuming\n");
	return 0;
}