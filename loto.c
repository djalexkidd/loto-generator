#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *generateRoll() {
    int *randNums = malloc(5 * sizeof(int)); // tableau pour stocker les nombres choisis
    int randNum, i;

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    // using nano-seconds instead of seconds
    srand((time_t)ts.tv_nsec);

    for (i = 0; i < 5;) { // boucle jusqu'à ce que l'utilisateur ait entré 5 nombres différents
        randNum = rand() % 51;

        if (randNum <= 0 || randNum > 50) { // vérifie si le nombre est inférieur à 1 ou supérieur à 50
            printf("");
        } else {
            int j, duplicate = 0;
            for (j = 0; j < i; j++) { // vérifie si le nombre a déjà été choisi
                if (randNums[j] == randNum) {
                    printf("");
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate) { // si le nombre est valide et non dupliqué, l'ajouter au tableau
                randNums[i] = randNum;
                i++;
            }
        }
    }

    return randNums;
}

int compareArrays(int a[], int b[], int size) {
    int i, j, match;
    
    for (i = 0; i < size; i++) {
        match = 0;
        for (j = 0; j < size; j++) {
            if (a[i] == b[j]) {
                match = 1;
                break;
            }
        }
        if (!match) {
            return 0;
        }
    }
    
    return 1;
}

int main() {
    int nums[5] = {0}; // tableau pour stocker les nombres choisis
    int num, i;

    printf("Entrez 5 nombres différents entre 1 et 50 :\n");

    for (i = 0; i < 5;) { // boucle jusqu'à ce que l'utilisateur ait entré 5 nombres différents
        printf("Nombre %d : ", i+1);
        scanf("%d", &num);

        if (num <= 0 || num > 50) { // vérifie si le nombre est inférieur à 1 ou supérieur à 50
            printf("Nombre invalide, veuillez entrer un nombre entre 1 et 50.\n");
        } else {
            int j, duplicate = 0;
            for (j = 0; j < i; j++) { // vérifie si le nombre a déjà été choisi
                if (nums[j] == num) {
                    printf("Nombre déjà choisi, veuillez en choisir un autre.\n");
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate) { // si le nombre est valide et non dupliqué, l'ajouter au tableau
                nums[i] = num;
                i++;
            }
        }
    }

    int isOk = 0;
    int tries = 0;

    clock_t start_time, end_time;
    double time_elapsed;

    start_time = clock(); // enregistre le temps de départ

    while(isOk == 0) {
    int *randNums = generateRoll();

    for (i = 0; i < 5; i++) {
        printf("%i ", randNums[i]);
    }
    printf("\n");

    tries++;
    if (compareArrays(nums, randNums, 5)) {
        isOk = 1;
        free(randNums); // libère la mémoire allouée dynamiquement
    } else {
        free(randNums); // libère la mémoire allouée dynamiquement
    }
    }

    end_time = clock(); // enregistre le temps de fin

    time_elapsed = ((double) (end_time - start_time)) / CLOCKS_PER_SEC; // calcule le temps écoulé en secondes

    printf("Vous avez choisi les nombres suivants : ");
    for (i = 0; i < 5; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    printf("Nombre de tentatives : %i\n", tries);
    printf("Temps écoulé : %f secondes\n", time_elapsed);

    return 0;
}