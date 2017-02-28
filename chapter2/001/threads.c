#include <pthread.h>
#include <stdio.h>

int n = 0;

volatile int counter = 0;
int loops;

void *adder(void *arg) {
  while (1) {
      n++;
  }
  return NULL;
}

void *printer(void *arg) {
    while (1) {
        printf("%d\n", n);
    }
}


int main(void) {
  pthread_t p1, p2;
  printf("Initial value : %d\n", n);

  pthread_create(&p1, NULL, adder, NULL);
  pthread_create(&p2, NULL, printer, NULL);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  return 0;
}
