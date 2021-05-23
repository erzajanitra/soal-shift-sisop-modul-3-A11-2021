#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>
#define PORT 8080

int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int sock = 0;
char buffer[1024] = {0};
int addrlen = sizeof(address);
FILE *fp,*fr,*tsv;
char data[100], name[100];
int flag = 0;//set belum ada client yg login. 
int file_no = 1;
int n = 0;
int iter;

//membuat detail identitas tiap file.

struct fileDetails{
    char name[100];
    char publisher[100];
    char year_pub[100];
    char filepath[100];
};


struct fileDetails f[100];
   
int main(int argc, char const *argv[]){

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    fp = fopen("/home/tsania/Documents/sisopshift3/no1/SERVER/akun.txt","a");
    fr = fopen("/home/tsania/Documents/sisopshift3/no1/SERVER/akun.txt","r");
  
    mkdir("FILES",0777);//automated directory-creation while server runs.
    printf("Server Ready!\n");
    read(new_socket,buffer,1024);
    printf("%s",buffer);
    bzero(buffer,sizeof(buffer));

    while(new_socket){

        //printf("Ini Flag : %d\n",flag);
        send(new_socket,"Type command to continue..\n",27,0);

        char inp[100];
        read(new_socket,buffer,1024);
        strcpy(inp,buffer);
        bzero(buffer,sizeof(buffer));

        if((strcmp(inp,"register") == 0) && flag == 0){
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
            
        }else if((strcmp(inp,"login") == 0) && flag == 0){
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
                }
            }
        }
        
        while(flag == 1){

            printf("User Authority\n");

            read(new_socket,buffer,1024);
            strcpy(data,buffer);
            bzero(buffer,sizeof(buffer)); 

            if(strstr(data,"add") != 0){
                printf("Add Session\n");

                send(new_socket, "Filename:", 9, 0);
                read(new_socket, buffer, 1024);
                strcpy(f[n].name, buffer);
                bzero(buffer, sizeof(buffer));
                fp = fopen(f[n].name, "w");
                fprintf(fp, "%d-st/nd/rd/th File Created Successfully.", file_no);
                file_no++;
                fclose(fp);

                send(new_socket, "Publisher:", 10, 0);
                read(new_socket, buffer, 1024);

                char record[100];
                strcpy(f[n].publisher, buffer);
                strcat(record, f[n].publisher);
                strcat(record, "\t");
                bzero(buffer, sizeof(buffer));

                send(new_socket, "Tahun Publikasi:", 17, 0);
                read(new_socket, buffer, 1024);
                bzero(buffer, sizeof(buffer));

                strcat(f[n].year_pub, buffer);
                strcat(record, f[n].year_pub);
                strcat(record, "\t");

                char fileee[100];

                getcwd(fileee, sizeof(fileee));

                strcpy(f[n].filepath, fileee);
                strcat(f[n].filepath, f[n].name);
                strcat(record, f[n].filepath);

                tsv = fopen("/home/tsania/Documents/sisopshift3/no1/SERVER/FILES/files.tsv", "a");
                fprintf(tsv, "%s\n", record);

                fclose(tsv);
                n++;
            }else if(strstr(data,"logout") != 0){
                flag = 0;
            }
        }
    }


    return 0;
}
