/*
 * Nazere Wright
 * COMP350/section 1
 * October 31st 2020
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <iostream>
#include <sys/semaphore.h>

int buffer[100] = {0};
int countArray = 0;
sem_t roomEmpty;
sem_t mutex;
sem_t exclusion;
int numReaders = 0;
int widget = 1;

void* writer(void* arg){
	long thread_id = (long)arg;
	int t_id = (int)thread_id;
	sem_wait(&roomEmpty);
	std::cout << "\n\n-----------------------";
	std::cout << "Writer thread: " << t_id << "Writing widget 1 to index: " << countArray;
	buffer[countArray] = widget; 
	widget++;
	countArray++;
	sem_post(&roomEmpty); 

	return NULL;
}
void* reader(void* arg){
	int readCount = 0;
	long thread_id = (long)arg;
	int t_id = (int)thread_id;
	sem_wait(&mutex);
	numReaders = numReaders + 1;
	if(numReaders == 1){
		sem_wait(&roomEmpty);
	}
	sem_post(&mutex);
	sem_wait(&exclusion);
	if(buffer[readCount]!= 0){
	std::cout<< "Reader reading widget" << buffer[readCount];
	readCount++;
	}
	sem_post(&exclusion);
	

}

int main(){ 
	int rc = sem_init(&roomEmpty,0, 1);
	if(rc != 0){
		std::cout << "Error with initializing roomEmpty" << std::endl;
		exit(0);
	}
	int mtex = sem_init(&mutex,0, 1);
	if(mtex != 0){
		std::cout << "Error with initializing mutex" << std::endl;
		exit(0);
	}
	int ex = sem_init(&exclusion,0, 1);
	if(ex != 0){
		std::cout << "Error with initializing ex" << std::endl;
		exit(0);
	}
	// represents the state of a thread in the buffer
	std::cout << "Enter the number of readers and writers" << std::endl;
	


}