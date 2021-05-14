# soal-shift-sisop-modul-3-A11-2021
## Soal 1

## Soal 2

## Soal 3
### Fungsi ``moveFile`` untuk membuat kategori file
``
    char *ndir,*dir;
    char x='/'; 
    char y='.';
    dir = strrchr(file,x); 
    ndir = strchr(file, y); 
    char ext[1000];
 ``
  *strrchr* digunakan untuk mendapatkan string yang dipisahkan dengan tanda */* dengan mengecek dari string bagian belakang. Sedangkan, *strchr* digunakan untuk mendapatkan string yang dipisahkan dengan tanda *.* dengan mengecek dari string bagian depan.
 ``
    if (dir){
        if(checkIfFileExists(file)){
            cekExt(dir+1,ext);
        }
        else{
            return 0;
        }
    }
``
  Jika path yang dicek merupakan directory atau file, maka akan mengecek apakah path file tersebut benar ada dengan fungsi ``checkIfFileExists``. Jika ada maka akan memisahkan extension dari nama file tersebut dengan fungsi ``cekExt`` yang akan dijelaskan pada bagian *3d*.
``
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
``
  Membuat directory berupa kategori dari path yang diinputkan dengan *mkdir*. Kemudian, directory tersebut disimpan pada current working directory dengan melakukan *rename* pada path awal dari directory tersebut.

### 3a
**Soal :** Program menerima opsi -f seperti contoh di atas, jadi pengguna bisa
menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan
oleh pengguna.
* Menerima argumen -f 
``
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
``
  Menggunakan *strcmp* untuk membandingkan argumen input apakah sesuai dengan argumen input yang diminta yaitu **-f**. Kemudian, *pthread_create* dan *pthread_join* dibuat untuk setiap path yang diinputkan. Apabila argumen file berhasil dikategorikan maka akan mengeluarkan pesan *Berhasil Dikategorikan*, sedangkan kalau tidak berhasil akan mengeluarkan pesan *Sad, gagal :(*
  
### 3b
**Soal :** Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada
suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1
directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin.
* Menerima argumen -d
``
else if(strcmp(argv[1],"-d")==0){
        if(argc==3){ //bisa menerima 1 path
            strcpy(dir, argv[2]);
            
        }
    }
``
   Menggunakan *strcmp* untuk membandingkan argumen input apakah sesuai dengan argumen input yang diminta yaitu **-d**. Command *-d* akan dilaksanakan jika hanya memasukkan 1 path saja, maka menggunakan *argc==3*. Path tersebut akan disimpan di sebuah char *dir*.
* Pesan yang ditampilkan ketika berhasil melakukan command pada argumen -d
``
if(strcmp(argv[1],"-d")==0) printf("Berhasil disimpan\n");
``
  Pesan ini akan ditampilkan apabila proses rekursif untuk memindahkan semua isi pada directory path yang telah dikategorikan ke current working directory sudah berhasil.
  
### 3c
**Soal :** program ini menerima opsi * yang akan mengkategorikan seluruh file yang ada di working directory ketika menjalankan program C tersebut.
* Menerima argumen *
``
else if(strcmp(argv[1],"*")==0){
        strcpy(dir,src);
    }
``
  Menggunakan *strcmp* untuk membandingkan argumen input apakah sesuai dengan argumen input yang diminta yaitu **\***. Path tersebut akan disimpan di sebuah char *dir*.

### 3d
**Soal :** Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. Jika file hidden, masuk folder “Hidden”
`` 
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
``
  File hidden adalah file yang memiliki awalan *.* pada nama file, sehingga jika file diawali dengan *.* maka akan membuat kategori file *Hidden*. Kemudian, jika file tidak punya extension dibelakanganya maka akan dikategorikan sebagai *Unknown*. Untuk nama extension yang ditulis dengan uppercase dapat diubah menjadi lowercase dengan menggunakan *tolower*.
  
### 3e
**Soal :** Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.
``
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
``
  Membuat thread untuk command *-d* dan *\**. *pthread_create* dan *pthread_join* akan dibuat sebanyak kategori yang ingin dibuat dari file yang ada pada directory tersebut.

### Kendala yang dialami


### Screenshot Eror
