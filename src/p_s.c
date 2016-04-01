#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int  flag;
pthread_cond_t cond;
pthread_mutex_t mutex;
 
void init()
{
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
  flag = 0;
}

void *consume_wait(void *pid)
{
  int id = *(int *)pid; 
  while (1)
  {
    pthread_mutex_lock(&mutex);
    while (!flag)
    {
      pthread_cond_wait(&cond, &mutex);
    }
    --flag;
    printf("<<<pick one:flag=%d\n", flag);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *produce_notify()
{
  pthread_mutex_lock(&mutex);
  if (flag == 0)
      pthread_cond_signal(&cond);
  ++flag;
  printf(">>>produce one:flag=%d\n", flag);
  pthread_mutex_unlock(&mutex);
  return NULL;
}
 
#define C_THREADS 3 
#define P_THREADS 10 

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  pthread_t wait[C_THREADS], notify[P_THREADS];
  int id;

  init();
  for(id=0; id<P_THREADS; id++)
      pthread_create(&notify[id], NULL, produce_notify, NULL);
  
  for(id=0; id<C_THREADS; id++) 
      pthread_create(&wait[id], NULL, consume_wait, &id);

  printf("wait all thread to stop\n");
  for(id=0; id<P_THREADS; id++)
      pthread_join(notify[id], NULL);
  
  for(id=0; id<C_THREADS; id++) 
      pthread_join(wait[id], NULL);
  printf("end main thread is running\n");

  return 0;
}
