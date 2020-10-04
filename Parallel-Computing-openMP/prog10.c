#include<omp.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
struct mynode
{
  char string[50];
  struct mynode *link;
};
struct mynode *start;
int first =0;
int last =0;
 
void *producer(void *argv);
void *consumer(void *argv);
void pthread_func(){
  pthread_t thread[2];
  pthread_attr_t attributes;
  int tid1,tid2;
  pthread_attr_init(&attributes);
  if((tid1 = pthread_create(&thread[0],&attributes,producer,NULL)))
  {
      printf("\nError in the producer thread\n");
      printf("\n");
  }
  if((tid2 = pthread_create(&thread[1],&attributes,consumer,NULL)))
  {
      printf("\nError in the consumer thread\n");
  }
  pthread_join(thread[0],NULL);
  pthread_join(thread[1],NULL);
}
 
void retrieve()
{
  struct mynode *three,*four;
  three = start;
  if(three!=NULL)
  {
      printf("\nThe string entered is = %s and its length = %zu\n",three->string,strlen(three->string));
      three=three->link;
      free(start);
      start = three;
      first++;
  }
  else
      printf("\nqueue is already empty");
}
void tailfunc()
{
  char *dummy = NULL;
  struct mynode *one,*two;
  one = start;
  int structsize;
structsize = sizeof(struct mynode);
  if(one  == NULL)
  {
      one = malloc(structsize);
      one->link = NULL;
      printf("Enter the producer string : ");
      gets(one->string);
      last++;
      start  = one;
  }
  else
  {
      while(one->link!=NULL)
          one = one->link;
      two = malloc(structsize);
      one->link = two;
      two->link = NULL;
      printf("Enter the Next string : ");
      gets(two->string);
      last++;
  }
    
}
void display()
{
  int i=0;
  struct mynode *print;
  for(print=start;print!=NULL;print=print->link)
  {
      printf("values = %s\n",print->string);
  }
}
void *consumer(void *argv)
{
  int num_cons=3;
  while(num_cons--){
  printf("Consumer : Hello I am consumer #%ld. Ready to consume Data\n",                pthread_self());
  while(1)
  {
      pthread_mutex_lock(&mutex);
      printf("Consumer...\n");
      while(last == first)
      {
          last=0;first=0;
          pthread_cond_wait(&cond,&mutex);
      }
      retrieve();
      sleep(1);
      pthread_mutex_unlock(&mutex);
      int resp;
      printf("Switch to another consumer? ( 1 - YES, 2 - NO)\n");
      scanf("%d",&resp);
      if(resp==1) break;
     }
   }
}
void *producer(void *argv)
{
  int num_prod=3;
  while(num_prod--){
  printf("Producer : Hello I am producer #%ld. Ready to produce data\n", pthread_self());
  while(1)
  {
      if(last < 5)
      {
          pthread_mutex_lock(&mutex);
          printf("Producer...\n");
          tailfunc();
          pthread_cond_signal(&cond);
          sleep(1);
          pthread_mutex_unlock(&mutex);
      }
      int resp;
      printf("Switch to another produces? ( 1 - YES, 2 - NO)\n");
      scanf("%d",&resp);
      if(resp==1) break;
    }  
  }
}
int main()
{
   num_p=3,num_c=5;
   printf("\nMain thread started\n");
   pthread_func();
 
  printf("\n\t* DONE *\n");
  return 0 ;
}
