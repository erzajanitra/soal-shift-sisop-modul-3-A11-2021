#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>

    int matrix1[4][3];
    int matrix2[3][6];
    int hasil[4][6];

    int i,j,k,add=0;

void main(){

    printf("---- Matrix 1 ----\n");
    for(i=0;i<4;i++){
        for(j=0;j<3;j++){
            matrix1[i][j]=(rand()%4);
            printf("%d \t",matrix1[i][j]);
        }
        printf("\n");
    }

    puts("");

    printf("---- Matrix 2 ----\n");
    for(i=0;i<3;i++){
        for(j=0;j<6;j++){
            matrix2[i][j]=(rand()%4);
            printf("%d \t",matrix2[i][j]);
        }
        printf("\n");
    }
    
    for(i=0;i<4;i++){
            for(j=0;j<6;j++){
                for(k=0;k<3;k++){
                    add = add + matrix1[i][k] * matrix2[k][j];
                }
                hasil[i][j] = add;
                printf("%d\t",hasil[i][j]);
                add = 0;
            }
            printf("\n");
        }
    
    puts("");


        key_t key = 1234;
        int *value;
        //membuat shared-memory segmen
        int shmid = shmget(key, sizeof(int)*6*4, IPC_CREAT | 0666);
        //menautkan pointer ke segmen memory pertama
        value = (int *)shmat(shmid, NULL, 0);
    
    printf("---- Hasil ----\n");
    for(i=0;i<4;i++){
        for(j=0;j<6;j++){
            printf("%d\t",hasil[i][j]);
        }
        printf("\n");
    }

    int a=0;
    printf("---- Hasil ----\n");
    for(i=0;i<4;i++){
        for(j=0;j<6;j++){
            value[a] = hasil[i][j];
            printf("%d\t",value[a]);
            a++;
        }
        printf("\n");
    }
    printf("---- Value ----\n");
    for(i=0;i<24;i++){
        printf("%d ",value[i]);
    }

    sleep(50);

    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
}