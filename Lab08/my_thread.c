#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
  int an_index;
  char some_message[100];
} my_thread_data;

void *my_worker(void *thread_data_ptr) {
  my_thread_data *my_data = (my_thread_data*) thread_data_ptr;
  printf("\nThread %d says %s", my_data->an_index, my_data->some_message);
}


int main(int argc, char *argv[]) {
  int n_threads=10;
  pthread_t my_threads[n_threads];
  my_thread_data my_thread_infos[n_threads];

  int i,ret;
  for (i=0; i<n_threads;i++) {
    my_thread_infos[i].an_index=i;
    strcpy(my_thread_infos[i].some_message, "some random message");
    pthread_create (&my_threads[i], NULL, my_worker, &my_thread_infos[i]);
    if (ret!=0) {
      fprintf(stderr, "create error!");
      exit(1);
    }
  }
  for(i=0; i<n_threads; i++) {
    ret = pthread_join(my_threads[i], NULL);
    if (ret!=0) {
      fprintf(stderr, "sadjfkaldj");
      exit(1);
    }
  }

  printf("\nGood, we are done!");
  return 0;
}
