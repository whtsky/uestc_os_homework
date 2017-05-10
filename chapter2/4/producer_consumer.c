#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

typedef struct {
  long msgType;
  char msg;
} Message;

int msgid;

void productor(void *arg) {
  Message msg;
  msg.msgType = 2;  
  FILE *fp;
  fp = fopen("t.txt", "r");
  char ch;
  while ((ch = fgetc(fp)) != EOF) {
    msg.msg = ch;
    msgsnd(msgid, &msg, 1, 0);
    sleep(4);
  }
  fclose(fp);
}

void consumer(void *arg) {
  Message msg;
  while (1) {
    msgrcv(msgid, &msg, 1, 2, 0);
    printf("out: %c\n", msg.msg);
    sleep(6);
  }
}

int main() {
  int i = 3, j = 4, k;
  pthread_t t1[i], t2[j];
  msgid = msgget((key_t)getpid(), IPC_CREAT | 0777);

  for (k = 0; k < i; k++)
    pthread_create(&t1[k], NULL, (void *)productor, NULL);
  for (k = 0; k < j; k++)
    pthread_create(&t2[k], NULL, (void *)consumer, NULL);

  for (k = 0; k < i; k++)
    pthread_join(t1[k], NULL);
  for (k = 0; k < j; k++)
    pthread_join(t2[k], NULL);
  return 0;
}
