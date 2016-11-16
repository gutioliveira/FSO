#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

// Global variables

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
semt_t job_queue_count;
char alphabet[28]= {'0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char alphabet2[28] = {'0', 'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q', 'p', 'o', 'n', 'm', 'l', 'k', 'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};

void initialize_job_queue ()
{
  /* The queue is initially empty. */
  job_queue = NULL;
  /* Initialize the semaphore which counts jobs in the queue.
   Its
  initial value should be zero. */
  sem_init (&job_queue_count, 0, 0);
}


void* print_alphabet (void* param) {
  int n =  *((int*)param);
  int i;

  sem_wait(&job_queue_count);
  pthread_mutex_lock(&mutex);

  for (i = 1; i < n; ++i)
  {
    printf("%c ", alphabet[i]);
    usleep(500000);
  }

  puts("");
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void creating_threads(int n) {
  int i;
  pthread_t thread_id[n];

  for (i = n; i > 0; i--) {
    int n = i + 1;
    pthread_create (&(thread_id[i]), NULL, &print_alphabet, &n);
    pthread_join (thread_id[i], NULL);
  }
}

int main(int argc, char const *argv[]) {

  int n = atoi(argv[1]);

  creating_threads(n);

  return 0;
}
