#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
    int xresult[24];
    int inputs[24];
    int i,j,iter,add=0;

    pthread_t tid[24];

struct pair{
    int angka;
    int batas;
};

void* faktorial(void *pairs){

    struct pair *pair = (struct pair *)pairs;

    if(pair->angka == 0 || pair->batas == 0){
        printf("0\n");
    }else if(pair->batas > pair->angka){
        while(pair->angka>0){
            if(iter == pair->angka) printf("%d",iter);
            else printf("%d*",iter);
            pair->angka--;
        }
        printf("\n");
    }else if(pair->angka >= pair->batas){
        for(iter=pair->angka; iter>pair->angka-pair->batas; iter--){
            if(iter == (pair->angka-pair->batas)-1) printf("%d",iter);
            else printf("%d*",iter);
        }
        printf("\n");
    }
}

void main(){

    printf("Masukkan 24 Input :\n");
    for(iter=0;iter<24;iter++){
        scanf("%d",&inputs[iter]);
    }

    puts("");
    
        int a=0;
        key_t key = 1234;
        int *value;
        //membuat shared-memory segmen
        int shmid = shmget(key, sizeof(int)*6*4, IPC_CREAT | 0666);
        //menautkan pointer ke segmen memory pertama
        value = shmat(shmid, NULL, 0);
     for(iter=0;iter<24;iter++){
            xresult[iter] = value[iter];
            struct pair pair;
            pair.angka = xresult[iter];
            pair.batas = inputs[iter];

            int error = pthread_create(&tid[iter],NULL,faktorial,(void*)&pair);

            if(error != 0){
                printf("\nCan't create thread : [%s]",strerror(error));
            }   
            pthread_join(tid[iter],NULL);
    }
    sleep(50);

    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
}