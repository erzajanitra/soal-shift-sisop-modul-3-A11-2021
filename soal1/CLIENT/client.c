#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080

char opt;
char buffer[1024] = {0};
char data[100], name[100];
int flag = 0;
int sock = 0, valread;



int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    struct sockaddr_in serv_addr;
 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

        printf("Client Ready!\n");
        send(sock,"Client Enter!\n",14,0);    
  
    while(1){

        if(flag == 0){
        //printf("Ini Flag : %d\n",flag);
       
        read(sock,buffer,1024);
        printf("%s",buffer);
        bzero(buffer,sizeof(buffer));

        char inp[100];
        scanf("%s",inp);
        send(sock,inp,strlen(inp),0);

        if(strcmp(inp,"register")== 0 && flag == 0){
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
        
        }else if(strcmp(inp,"login") == 0 && flag == 0){
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
        
        }
        
        }else if(flag == 1){

            printf("User Authority\n");

                scanf("%s",data);
                send(sock,data,strlen(data),0);

            if(strstr(data,"add") != 0){

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

            }else if(strstr(data,"logout") != 0){

                printf("----------Logout Session!---------\n");
                printf("-----SUCCESSFULLY SIGNED OUT-----\n");
                flag = 0;

            }else if(strstr(data,"delete") != 0){

                printf("-----Delete Session!------\n");
                scanf("%s",name);
                send(sock,name,strlen(name),0);

            }else if(strstr(data,"see") != 0){
                
            }else if(strstr(data,"find") != 0){
                
            }else if(strstr(data,"download") != 0){
                
            }
        } 

    }
    

    return 0;
}
