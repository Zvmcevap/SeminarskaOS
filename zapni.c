#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *zapni(void *arg); // plac drzac funkcije, ki je definirana pod main-om (baje je to dobra praksa v C-ju.)

int main(int argc, char *argv[]) {
    pthread_t threads[argc];
    int i, rc;

    // Ni podanega argumenta
    if (argc < 2) {
        printf("Vnesite ime datoteke, ki jo zelite zapeti.\n");
        return 1;
    }

    // Ustvari nit za vsak argument, zmanjsan za 1 ker prvi argument je vedno ime datoteke al neki
    for (i = 0; i < argc - 1; i++) {
        if ((rc = pthread_create(&threads[i], NULL, zapni, argv[i + 1])) != 0) { // ce create ni enak 0 je napaka, drugace vzame zapni argument ime datoteke argv[i+1]
            perror("Napaka v ustvarjanju niti.\n");
            return 1;
        }
    }

    // Pocakaj da nit konca svoje veselje
    for (i = 0; i < argc - 1; i++) {
        if ((rc = pthread_join(threads[i], NULL)) != 0) {
            perror("Napaka pri zdruzitvi niti.\n");
            return 1;
        }
    }
    return 0;
}

void *zapni(void *arg) {
    FILE *fp;
    int c, p, kolicina;
    p = 0; // p je primerjalni karakter, ki ga primerjamo z naslednjim karakterjem c
    kolicina = 1;    // kolicina je kolikokrat srecamo karakter p


    fp = fopen(arg, "r");

    // Ce ime datoteke ali format ne stimata
    if (fp == NULL) {
        printf("Datoteke ni mozno najti/odpreti! \n");
        exit(1); // Vrni se z napako
    }

    while ((c = getc(fp)) != EOF) { // preberi vsak karakter v datoteki posebej dokler ni End Of File
        // Ce bi bil p == 0 bi bili na zacetku vrstice in rabimo samo izenacit p = c
        if (p != 0) {
            if (p == c) { // pristej 1 vsakic ko je p == cju
                kolicina += 1;
            } else { // Ce p ni enak karakterju moramo izpisati karakter in zaceti steti znova
                fwrite(&kolicina, 4, 1, stdout); // izpisi kolicino kot 4-bajtni integer v binarnem formatu
                printf("%c", p); // in karakter katerega smo steli
                kolicina = 1;
            }
        }
        p = c; // p spremenimo v c zato da ga primerjamo z naslednjim karakterjem ki pride v zanki
    }

    fclose(fp); // zapri datoteko

    return NULL;
}
