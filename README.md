# soal-shift-sisop-modul-3-A11-2021
## Soal 1

- SERVER : https://github.com/erzajanitra/soal-shift-sisop-modul-3-A11-2021/blob/main/soal1/SERVER/server.c
- CLIENT : https://github.com/erzajanitra/soal-shift-sisop-modul-3-A11-2021/blob/main/soal1/CLIENT/client.c

### Server
* Register
```
            char str[100];
            send(new_socket,"Username : ",11,0);
            read(new_socket,buffer,1024);
            strcpy(str,buffer);
            bzero(buffer,sizeof(buffer));
            
            strcat(str,":");
            send(new_socket,"Password : ",11,0);
            read(new_socket,buffer,1024);
            strcat(str,buffer);
            bzero(buffer,sizeof(buffer));

            fprintf(fp,"%s\n",str);
            fclose(fp);
```
   Server menerima message *register* dari client, kemudiaan mengirimkan message permintaan *username* dan *password*. Setelah itu, server akan menyimpan username dan password dalam file *akun.txt*
* Login
```
            char str[100];
            send(new_socket,"Username : ",11,0);
            read(new_socket,buffer,1024);
            strcpy(str,buffer);
            bzero(buffer,sizeof(buffer));
            
            strcat(str,":");
            send(new_socket,"Password : ",11,0);
            read(new_socket,buffer,1024);
            strcat(str,buffer);
            bzero(buffer,sizeof(buffer));

            char data2[100];
            while(fgets(data2, sizeof(data2),fr) != NULL){
                if(strstr(data2,str) != 0){
                    flag = 1;
                    send(new_socket,"Login Success!\n",15,0);
```
   Server menerima *login* message dari client, kemudian mengirimkan permintaan *username* dan *password*. Server akan mengecek *username* dan *password*. Jika berhasil ditemukan maka akan menyimpan user yang sedang login dan mengirim pesan sukses. Apabila tidak ditemukan, maka akan mengirim pesan login gagal.
* Add
```
                if(strstr(data,"add") != 0){
                printf("Add Session\n");
               
                send(new_socket, "Publisher: ", 11, 0);
                read(new_socket, buffer, 1024);

                char record[100];
                strcpy(f[n].publisher, buffer);
                strcpy(record, f[n].publisher);
                strcat(record, "\t");
                bzero(buffer, sizeof(buffer));

                send(new_socket, "Tahun Publikasi: ", 18, 0);
                read(new_socket, buffer, 1024);
                
                strcpy(f[n].year_pub, buffer);
                strcat(record, f[n].year_pub);
                strcat(record, "\t");
                bzero(buffer, sizeof(buffer));

                send(new_socket, "Filepath: ", 11, 0);
                read(new_socket, buffer, 1024);
                strcpy(f[n].filepath, buffer);
                
                char fileee[100];
                getcwd(fileee,sizeof(fileee));

                sprintf(f[n].name,"file%d.pdf",n);
                strcat(f[n].filepath,"/");
                strcat(f[n].filepath, f[n].name);
                strcat(record, f[n].filepath);
                bzero(buffer, sizeof(buffer));
                sprintf(fileee,"%s/FILES/%s",fileee,f[n].name);
                
                fp = fopen(fileee,"w");
                fprintf(fp,"File #%d Created Successfully.",file_no);
                file_no++;
                fclose(fp);

                tsv = fopen("/home/tsania/Documents/sisopshift3/no1/SERVER/files.tsv", "a");
                fprintf(tsv, "%s\n", record);

                fclose(tsv);

                mlog = fopen("/home/tsania/Documents/sisopshift3/no1/SERVER/running.log","a");

                fprintf(mlog,"Tambah : %s %s\n",f[n].name,user);
                fclose(mlog);

                n++;

            }
```
   Server menerima input *publisher*, *year_pub*, dan *filepath* dari client dan menambahkan identitas data file baru tersebut pada file tsv. File tsv akan dicetak akan disimpan padaa folder FILES dalam server.
* Delete
```
else if(strstr(data,"delete") != 0){
                 
                char doc[100];
                read(new_socket,buffer,1024);
                strcpy(doc,buffer);
                bzero(buffer,sizeof(buffer));

                struct dirent *de;
                DIR *dr = opendir("FILES");

                while((de = readdir(dr)) != NULL){
                    if(strstr(de->d_name,doc) != 0){
                        remove(de->d_name);
                    }    
                }
                closedir(dr);

                tsv = fopen("/home/tsania/Documents/sisopshift3/no1/SERVER/files.tsv","w");    
                
                char doc2[100];
                while(fgets(doc2, sizeof(doc2),tsv) != NULL){
                    if(strstr(doc,doc2)!= 0){
                        char *temp = doc2;
                        memset(doc2,0,sizeof(doc2));
                        fprintf(tsv,"%s\n",doc2);
                        break;
                    }
                }
                fclose(tsv);

                mlog = fopen("/home/tsania/Documents/sisopshift3/no1/SERVER/running.log","a");

                fprintf(mlog,"Hapus : %s %s\n",doc,user);
                fclose(mlog);

            }
```
   Server akan menjalankan fungsi `delete` apabila *client* mengirimkan pesan *delete* kepada server. Delete berfungsi untuk menghapus identitas data file pada folder FILES serta menghapus filenya.
* Log Pada Delete
```
mlog = fopen("/home/tsania/Documents/sisopshift3/no1/SERVER/running.log","a");

                fprintf(mlog,"Hapus : %s %s\n",doc,user);
                fclose(mlog);
```
* Log Pada Add
```
 mlog = fopen("/home/tsania/Documents/sisopshift3/no1/SERVER/running.log","a");

                fprintf(mlog,"Tambah : %s %s\n",f[n].name,user);
                fclose(mlog);

```
 Server dapat menyimpan log untuk merekam tiap aktivitas pada penambahan dan penghapusan data.
   
### Client
* Register
```
            char reg_id[100], reg_pass[100];
            read(sock,buffer,1024);
            printf("%s",buffer);
            bzero(buffer,sizeof(buffer));

            scanf("%s",reg_id);
            send(sock,reg_id,strlen(reg_id),0);

            read(sock,buffer,1024);
            printf("%s",buffer);
            bzero(buffer,sizeof(buffer));

            scanf("%s",reg_pass);
            send(sock,reg_pass,strlen(reg_pass),0);
 ```
   Client mengirim message *register* ke server, kemudiaan memasukkan *username* dan *password*.
* Login
```
            char log_id[100], log_pass[100], status[50];
            read(sock,buffer,1024);
            printf("%s",buffer);
            bzero(buffer,sizeof(buffer));

            scanf("%s",log_id);
            send(sock,log_id,strlen(log_id),0);

            read(sock,buffer,1024);
            printf("%s",buffer);
            bzero(buffer,sizeof(buffer));

            scanf("%s",log_id);
            send(sock,log_id,strlen(log_id),0);

            read(sock,buffer,1024);
            printf("%s",buffer);
            strcpy(status,buffer);
            bzero(buffer,sizeof(buffer));

            if(strstr(status,"Login Success!\n") != 0){
                flag = 1;
            }
```
   Client mengirim message *login* ke server, kemudiaan memasukkan *username* dan *password*. Setiap client yang login akan disimpan pada file log.
 * Logout
 ```
                printf("----------Logout Session!---------\n");
                printf("-----SUCCESSFULLY SIGNED OUT-----\n");
                flag = 0;
 ```
   Menampilkan pesan logout apabila user melakukan logout.
 * Menambahkan buku (add)
 ```
                printf("-----Add Session!------\n");
                read(sock, buffer, 1024);
                printf("%s\n", buffer);
                char publisher[100];
                scanf("%s", publisher);
                bzero(buffer, sizeof(buffer));
                send(sock, publisher, strlen(publisher), 0);

                read(sock, buffer, 1024);
                printf("%s\n", buffer);
                char year_pub[100];
                scanf("%s", year_pub);
                bzero(buffer, sizeof(buffer));
                send(sock, year_pub, strlen(year_pub), 0);

                read(sock, buffer, 1024);
                printf("%s\n", buffer);
                char filepath[100];
                scanf("%s", filepath);
                send(sock, filepath, strlen(filepath), 0);
                bzero(buffer, sizeof(buffer));
```
   Client mengirimkan pesan berupa string *publisher*, *year_pub*, dan *filepath* kepada server yang akan disimpan pada file tsv. Kumpulan file tsv ini akan disimpan pada folder FILES

#### Kendala yang dialami<br/>
1. Belum bisa melakukan multiuser 
2. `files.tsv` tidak dapat menampung dan menampilkan data yang diinputkan

#### Screenshot Eror<br/>
1.![image](https://user-images.githubusercontent.com/69724694/119264798-bceaca80-bc0e-11eb-90cf-a18d07f8076d.png)<br/>

#### Output No 1<br/>
1. Register & Login, Add Session, Delete Session<br/>
![image](https://user-images.githubusercontent.com/69724694/119265084-a729d500-bc0f-11eb-87b5-710ebd1e7698.png)<br/>
2. Files And Directory Creation<br/>
![image](https://user-images.githubusercontent.com/69724694/119265104-ba3ca500-bc0f-11eb-8e79-0d4b5ceb0055.png)<br/>
![image](https://user-images.githubusercontent.com/69724694/119265116-c7f22a80-bc0f-11eb-9f6c-fb2c921ad3f1.png)<br/>



## Soal 2

Soal No 2 : <br/>
2A : [no2a](https://github.com/erzajanitra/soal-shift-sisop-modul-3-A11-2021/blob/main/soal2/no2a.c)<br/>
2B : [no2b](https://github.com/erzajanitra/soal-shift-sisop-modul-3-A11-2021/blob/main/soal2/no2b.c)<br/>
2C : [no2c](https://github.com/erzajanitra/soal-shift-sisop-modul-3-A11-2021/blob/main/soal2/no2c.c)<br/>

### 2a
**Soal :** Membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).

* mendefinisikan matriks
```
    int matrix1[4][3];
    int matrix2[3][6];
    int hasil[4][6];
```
* mengassign angka random pada matriks dan mengkalikan keduanya dan diassign menuju matriks hasil
```
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
```
modulo 4 pada setiap value-assignmentnya bertujuan untuk menghasilkan angka 1 digit dan bernilai tidak terlalu besar. sehingga ketika dikalikan antara kedua matriksnya akan menghasilkan angka yg tidak lebih dari 20.

* membuat shared memory untuk dipasangkan dengan program kedua
```
 key_t key = 1234;
        int *value;
        int shmid = shmget(key, sizeof(int)*6*4, IPC_CREAT | 0666);
        value = (int *)shmat(shmid, NULL, 0);
```
* mengassign array hasil kepada pointer tertaut pada shared memory yang nantinya nilai-nilai ini akan digunakan secara bersamaan oleh kedua program. value dibuat berbentuk array 1 dimensi menampung secara urut nilai-nilai pada matriks hasil dimulai dari setiap barisnya.
```
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
```

### 2b
**Soal :** Membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c) (Catatan!: gunakan shared memory). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang ada. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya matri(dari paling besar ke paling kecil) (Catatan!: gunakan thread untuk perhitungan di setiap cel). 

* membuat input user yang akan dipasangkan dengan variabel yang menampung matriks hasil (variabel value)
```
printf("Masukkan 24 Input :\n");
    for(iter=0;iter<24;iter++){
        scanf("%d",&inputs[iter]);
    }
```
* membuat struct untuk memasangkan tiap-tiap value dan input user
```
struct pair{
    int angka;
    int batas;
};
```
* mengassign tiap array ke dalam struct berdasarkan index serta membuat thread agar proses dapat bersambung
```
for(iter=0;iter<24;iter++){
            xresult[iter] = value[iter];
            struct pair pair;
            pair.angka = xresult[iter];
            pair.batas = inputs[iter];

            int error = pthread_create(&tid[iter],NULL,faktorial,(void*)&pair);

            if(error != 0){
                printf("\nCan't create thread : [%s]",strerror(error));
            }   

            pthread_join(tid[i],NULL);
    }
```
* memunculkan faktorial sesuai dengan ketentuan yg berada pada soal dimana ketika input lebih besar daripada hasil perkalian matriks pada array value maka akan dioutputkan seluruh faktorialnya. dan apabila input lebih kecil daripada hasil perkalian matriks pada array value maka akan dioutputkan faktorialnya hingga batas inputnya. dan apabila input nol maka akan dioutputkan nol.
```
void* faktorial(void *pairs){

    struct pair *pair = (struct pair *)pairs;
    int angka = pair->angka;
    int batas = pair->batas;
    if(angka == 0 || batas == 0){
        printf("0\n");
    }else{
        if(batas > angka){
            while(angka>0){
                if(angka == 1){
                    printf("%d",angka);
                }else{
                    printf("%d*",angka);
                }
                angka--;
            }
            printf("\n");
        }else if(angka >= batas){
            while(batas>0){
                if(batas == 1){
                    printf("%d",angka);
                }else{
                    printf("%d*",angka);
                }
                angka--;
                batas--;
            }
            printf("\n");
        }
    }
}
```
* output 2A dan 2B
![image](https://user-images.githubusercontent.com/69724694/119107391-63856e80-ba49-11eb-85cc-422f7024df8b.png)


### 2c
**Soal :** Membuat program untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command “ps aux | sort -nrk 3,3 |
head -5” (Catatan!: Harus menggunakan IPC Pipes)
* Menjalankan proses `ps aux`
```
                close(1);
                dup(fd1[1]);
                close(fd1[0]);
                close(fd2[0]);
                close(fd2[0]);
                char *proc[] = {"ps","aux",NULL};
                execv("/bin/ps", proc);
 ```
fd1[0] adalah file descriptor untuk membaca input pertama. fd1[1] adalah file descriptor untuk menuliskan output pertama.fd2[0] adalah file descriptor untuk membaca input kedua. fd2[1] adalah file descriptor untuk menuliskan output kedua. pada source code di atas diketahui bahwa terjadi penulisan proses pertama yaitu ps -aux pada file descriptr pertama sedangkan file descriptor lain ditutup.
   
 * Menjalankan proses `sort -nrk 3,3`
 ```
                while((wait(&status2)) > 0);
                close(0);
                dup(fd1[0]);
                close(fd1[1]);

                close(1);
                dup(fd2[1]);
                close(fd2[0]);
                char *sort[] = {"sort","-nrk","3,3",NULL};
                execv("/usr/bin/sort", sort);
            
  ```
  pada source code di atas diketahui bahwa terjadi pembacaan output dari input atau penulisan proses pertama yaitu `ps -aux` pada file descriptor pertama. pada saat yg bersamaan output dari file descriptor yg pertama berposisi sebagai output filedescriptor pertama diproses bersamaan dengan `sort -nrk 3,3` yang kemudian hasil dari proses kedua command tersebut juga diinputkan pada file descriptor kedua.
  * Menjalankan proses `head -5`
```
                close(fd1[0]);
                close(fd1[1]);
                while((wait(&status)) > 0);
                close(0);
                dup(fd2[0]);
                close(fd2[1]);
                // char *sort[] = {"sort","-nrk","3,3",NULL};
                // execv("/usr/bin/sort", sort);
                char *head[] = {"head", "-5", NULL};
                execv("/usr/bin/head", head);
```
pada bagian ini terjadi pemrosesan terakhir dimana output dari filedescriptor kedua berakhir dari input dari proses sebelumnya yang diolah bersamaan dengan command terakhir yaitu `head -5`

* Output nomor 2c <br\>
![image](https://user-images.githubusercontent.com/75319371/119258138-a171c680-bbf2-11eb-9e2e-cdadf0e2107d.png)

### Kendala yang dialami
1. Pada saat mengerjakan nomor 2c, output yang dihasilkan tidak sesuai karena kesalahan urutan dalam proses mengeksekusi. Maka kami memperbaiki urutan eksekusi dengan mengeksekusi *ps aux* dan  *sort -nrk 3,3* pada child process, sedangkan *head -5* dieksekusi pada parent process. Hal ini dilakukan agar proses mengeksekusi *ps aux*, *sort*, dan terakhir *head* secara berurutan.

### Screenshot Eror
1. output tidak bisa ditampilkan pada program sebelum revisi. <br\>
![image](https://user-images.githubusercontent.com/69724694/119259752-e6e5c200-bbf9-11eb-9623-c10c7791ffb9.png)


## Soal 3
### Fungsi ``moveFile`` untuk membuat kategori file
```
    char *ndir,*dir;
    char x='/'; 
    char y='.';
    dir = strrchr(file,x); 
    ndir = strchr(file, y); 
    char ext[1000];
 ```
  *strrchr* digunakan untuk mendapatkan string yang dipisahkan dengan tanda */* dengan mengecek dari string bagian belakang. Sedangkan, *strchr* digunakan untuk mendapatkan string yang dipisahkan dengan tanda *.* dengan mengecek dari string bagian depan.
 ```
    if (dir){
        if(checkIfFileExists(file)){
            cekExt(dir+1,ext);
        }
        else{
            return 0;
        }
    }
```
  Jika path yang dicek merupakan directory atau file, maka akan mengecek apakah path file tersebut benar ada dengan fungsi ``checkIfFileExists``. Jika ada maka akan memisahkan extension dari nama file tersebut dengan fungsi ``cekExt`` yang akan dijelaskan pada bagian *3d*.
```
    mkdir(ext,0777);//extension dir
    
    char path[1000];
    strcpy(path,(char*) argc);
    
    char fileCat[1000];
    getcwd(fileCat,sizeof(path));
    strcat(fileCat,"/");
    strcat(fileCat,ext);
    strcat(fileCat,"/");
    strcat(fileCat,dir+1);
    printf("%s\n%s\n",path,fileCat);
    rename(path,fileCat);
    
    return(void *) 1;
    //moves(src);
    pthread_exit(0);
}
```
  Membuat directory berupa kategori dari path yang diinputkan dengan *mkdir*. Kemudian, directory tersebut disimpan pada current working directory dengan melakukan *rename* pada path awal dari directory tersebut.

### 3a
**Soal :** Program menerima opsi -f seperti contoh di atas, jadi pengguna bisa
menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan
oleh pengguna.
* Menerima argumen -f 
```
if(strcmp(argv[1],"-f")==0){
        int i=0;
        for(int x=2;x<argc;x++){
            //printf("%s", argv[x]);
            pthread_create(&tid[i],NULL,moveFile,(void *)argv[x]);
            i++;
        }
        for(int x=0;x<i;x++){
            void *ptr;
            pthread_join(tid[x],&ptr);
            
            if(((int) ptr)==1){
                printf("File %d : Berhasil Dikategorikan \n", x+1);
            }
            else{
                printf("File %d : Sad, gagal :( \n",x+1);
            }
        }
        return 0;
    }
```
  Menggunakan *strcmp* untuk membandingkan argumen input apakah sesuai dengan argumen input yang diminta yaitu **-f**. Kemudian, *pthread_create* dan *pthread_join* dibuat untuk setiap path yang diinputkan. Apabila argumen file berhasil dikategorikan maka akan mengeluarkan pesan *Berhasil Dikategorikan*, sedangkan kalau tidak berhasil akan mengeluarkan pesan *Sad, gagal :(*
* Output no 3a <br/>
![image](https://user-images.githubusercontent.com/75319371/118289224-51fb0e80-b4ff-11eb-8ddf-64a2d71c07c5.png) <br/>
Berhasil membuat kategori c <br/>
![image](https://user-images.githubusercontent.com/75319371/118289334-71923700-b4ff-11eb-84b2-223886273619.png) <br/>
Berhasil membuat kategori txt <br/>
![image](https://user-images.githubusercontent.com/75319371/118289493-9ab2c780-b4ff-11eb-8091-387245132b5d.png)

### 3b
**Soal :** Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada
suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1
directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin.
* Menerima argumen -d
```
else if(strcmp(argv[1],"-d")==0){
        if(argc==3){ //bisa menerima 1 path
            strcpy(dir, argv[2]);
            
        }
    }
```
   Menggunakan *strcmp* untuk membandingkan argumen input apakah sesuai dengan argumen input yang diminta yaitu **-d**. Command *-d* akan dilaksanakan jika hanya memasukkan 1 path saja, maka menggunakan *argc==3*. Path tersebut akan disimpan di sebuah char *dir*.
* Pesan yang ditampilkan ketika berhasil melakukan command pada argumen -d
```
if(strcmp(argv[1],"-d")==0) printf("Berhasil disimpan\n");
```
  Pesan ini akan ditampilkan apabila proses rekursif untuk memindahkan semua isi pada directory path yang telah dikategorikan ke current working directory sudah berhasil.
* Output no 3b <br/>
![image](https://user-images.githubusercontent.com/75319371/119086040-14cadb00-ba2f-11eb-9aac-3e75d9bff7c5.png)

### 3c
**Soal :** program ini menerima opsi * yang akan mengkategorikan seluruh file yang ada di working directory ketika menjalankan program C tersebut.
* Menerima argumen *
```
else if(strcmp(argv[1],"*")==0){
        strcpy(dir,src);
    }
```
  Menggunakan *strcmp* untuk membandingkan argumen input apakah sesuai dengan argumen input yang diminta yaitu **\***. Path tersebut akan disimpan di sebuah char *dir*.
* Output no 3c <br/>
![image](https://user-images.githubusercontent.com/75319371/119086331-89057e80-ba2f-11eb-93cf-070f67f666ad.png)

### 3d
**Soal :** Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. Jika file hidden, masuk folder “Hidden”
```
void cekExt(char* fileName,char *ext){ 
    char *extt=strchr(fileName,'.'); //kalau ada 2 ext->ambil paling depan
    if(extt==fileName){
        strcpy(ext,"Hidden");
    }
    else if (extt==NULL){
        strcpy(ext,"Unknown");
    }
    else{
        strcpy(ext,extt+1);
        for(int x=0;x<strlen(ext);x++){
            //ubah jadi lowercase
            ext[x]=tolower(ext[x]);
        }
    }
}
```
  File hidden adalah file yang memiliki awalan *.* pada nama file, sehingga jika file diawali dengan *.* maka akan membuat kategori file *Hidden*. Kemudian, jika file tidak punya extension dibelakanganya maka akan dikategorikan sebagai *Unknown*. Untuk nama extension yang ditulis dengan uppercase dapat diubah menjadi lowercase dengan menggunakan *tolower*.
* Isi folder Unknown <br/>
 ![image](https://user-images.githubusercontent.com/75319371/119086578-dc77cc80-ba2f-11eb-99c0-ddf933d2130d.png) <br/>

### 3e
**Soal :** Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.
```
while(i<indeks){
        printf("%s\n",save[i]);
        pthread_create(&tid2[i],NULL,moveFile,(void *)save[i]);
        i++;
    }
    while (j<indeks)
    {
        void *ptr;
        pthread_join(tid2[j],&ptr);
        j++;
    }
```
  Membuat thread untuk command *-d* dan *\**. *pthread_create* dan *pthread_join* akan dibuat sebanyak kategori yang ingin dibuat dari file yang ada pada directory tersebut.

### Kendala yang dialami
1. Membedakan string path yang merupakan directory dan file biasa. Solusinya kami menggunakan strrchr untuk mengecek directory dan strchr untuk mengecek file. 
2. Directory untuk kategori dapat terbuat di current working directory, tetapi file tidak berhasil dipindah. Solusi : menggunakan getcwd agar path tujuan benar dan menambahkan "/" sebelum dir+1 (nama file).
3. Memindahkan file secara rekursif. Hal ini disebabkan oleh size array untuk menyimpan path masing2 file terlalu kecil, sehingga kami membuat size array hingga 1000.

### Screenshot Eror
* Aborted ketika menjalankan argumen -d dan * <br/>
![image](https://user-images.githubusercontent.com/75319371/118289843-f41af680-b4ff-11eb-8789-da593be13e39.png)



