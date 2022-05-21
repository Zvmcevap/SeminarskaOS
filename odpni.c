#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *odpni(void *arg);

int main(int argc, char *argv[]) {
  pthread_t threads[argc];
  int i, rc;

  // Ustvarjanje niti glede na kolicino podanih datotek
  for (i = 0; i < argc-1; i++) {
    if ((rc = pthread_create(&threads[i], NULL, odpni, argv[i+1])) != 0) {
      perror("Napaka pri kreiranju niti.\n");
      exit(1);
    }
  }

  // Pocakamo da niti koncajo in jih zdruzimo nazaj
  for (i = 0; i < argc-1; i++) {
    if ((rc = pthread_join(threads[i], NULL)) != 0) {
      perror("Napaka pri zdruzitvi niti.\n");
      exit(1);
    }
  }

  return 0;
}

void *odpni(void *arg) {
  FILE *fp;
  int j, k;
  int *kolicina = malloc(sizeof(int)); // kompajlerju rečemo da rezervira v heap-u na tem kazalcu, prostora za velikost 1 int-a (4 bajte)

  fp = fopen(arg, "r");

  // failed to open file
  if (fp == NULL) {
    printf("Datoteke ni mozno najti/odpreti\n");
    exit(1);
  }

  // Dobimo kolicino (4 - bajtni int) karakterja
  fread(kolicina, 4, 1, fp);

  while ((k = getc(fp)) != EOF) {
    // in jih naprintamo toliko kolikor jih moramo
    for (j = 0; j < *kolicina; j++) {
      putchar(k);
    }
    // kolicina naslednjega karakterja
    fread(kolicina, 4, 1, fp);
  }

  fclose(fp);

  return NULL;
}
