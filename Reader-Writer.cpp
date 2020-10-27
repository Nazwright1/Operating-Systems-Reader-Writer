/*
 * Nazere Wright
 * COMP350/section 1
 * October 31st 2020
 * This program implements a solution to the classic
 * Reader-Writer process synchronization problem. 
 * A variable number of readers or writers can be specified
 * from the command line.
 * The writers threads create integers and but them in a buffer.
 * The readers consume these widgets.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <semaphore.h>

// initialize buffer to 0 values
int buffer[100] = {0};
int countArray = 0;
sem_t roomEmpty;
sem_t mutex;
sem_t exclusion;
int Readers = 0;
int widget = 1;
int readCount = 0;

void* writer(void* arg){
  long thread_id = (long)arg;
  // thread id for current thread
  int t_id = (int)thread_id;
  sem_wait(&roomEmpty);
  std::cout << "\n\n-----------------------\n\n";
  std::cout << "Writer thread: " << t_id << " Writing widget " << widget << " to index: " << countArray << std::endl;
  buffer[countArray] = widget; 
  widget++;
  countArray++;
  sem_post(&roomEmpty); 
  pthread_exit(NULL);
}

void* reader(void* arg){
  long thread_id = (long)arg;
  // thread id for current thread
  int t_id = (int)thread_id;
  sem_wait(&mutex);
  Readers = Readers + 1;
  if(Readers == 1){
    sem_wait(&roomEmpty);
  }
  sem_post(&mutex);
  sem_wait(&exclusion);
  std::cout << "\n\n-----------------------\n\n";
  std::cout<< "Reader Thread " << t_id <<  " reading widget " << buffer[readCount] << std::endl ;
  readCount = readCount + 1;
  sem_post(&exclusion);
  pthread_exit(NULL);
}

int main(){ 
  int rc = sem_init(&roomEmpty,0, 1);
  // semaphore that indicates a thread is executing the critcal section.
  if(rc != 0){
    std::cout << "Error with initializing roomEmpty" << std::endl;
	exit(0);
  }
  // semaphore that provides mutual exclusion for updating
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

  std::cout << "Enter the number of readers and writers" << std::endl;
  int numReaderThreads = 0;
  int numWriters = 0; 
  std::cin >> numReaderThreads >> numWriters; 
  pthread_t t_readers[numReaderThreads];
  pthread_t t_writers[numWriters];
  if(numReaderThreads != 0 && numWriters != 0){
    for(int i = 1; i <= numReaderThreads; i++){
      pthread_create(&t_readers[i], NULL, reader, (void *)(intptr_t)i);
    }
    for(int i = 1; i <= numWriters; i++){
      pthread_create(&t_writers[i], NULL, writer, (void *)(intptr_t)i);
    }
    for(int i = 1; i <= numReaderThreads; i++){
      pthread_join(t_readers[i], NULL);
    }
    for(int i = 1; i <= numWriters; i++){
	  pthread_join(t_writers[i], NULL);
    }
  }
  return 0;

}