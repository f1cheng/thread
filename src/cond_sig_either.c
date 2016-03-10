#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int  flag;
pthread_cond_t cond;
pthread_mutex_t mutex;
 
void initialize_flag()
{
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
  flag = 0;
}

void set_thread_flag (int v)
{ 
  pthread_mutex_lock(&mutex);
  flag = v;
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
}
 
void *thread_wait(void *pid)
{
  int id = *(int *)pid; 
  while (1)
  {
    pthread_mutex_lock(&mutex);
    if (!flag)
    {
			printf("thread%d wait begin\n", id);
			pthread_cond_wait(&cond, &mutex);
			printf("thread%d wait end\n", id);
	  }
    printf("thread %d is running\n", id);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}


void *thread_notify()
{
  sleep(3);
  printf("thread notify is running\n");
  set_thread_flag(1);
  return NULL;
}
 

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  pthread_t wait1, wait2, notify;
  int id = 1;
  initialize_flag();

  pthread_create(&wait1, NULL, thread_wait, &id);
  id = 2;
  pthread_create(&wait2, NULL, thread_wait, &id);
  pthread_create(&notify, NULL, thread_notify, NULL);

  printf("main thread is running\n");
  sleep(5);
  printf("end main\n");

  return 0;
}
