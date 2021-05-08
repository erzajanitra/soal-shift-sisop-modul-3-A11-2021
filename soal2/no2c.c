
/*

2. Buatlah sebuah program untuk menampilkan file 
pada urutan ketiga dari sebuah direktori, 
dengan menggunakan pipe dan command ls, head, tail.

*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t child_id;
	int status;
	int fd1[2];
	int fd2[2];
    pipe(fd1);
    pipe(fd2);

	
	if(pipe(fd1) == -1 || pipe(fd2) == -1) {
		exit(EXIT_FAILURE); 
	}
	
	child_id = fork();
	if(child_id < 0) {
		exit(EXIT_FAILURE);
	}

	if(child_id == 0) {
        	pid_t child_id2;
        	int status2;

	        child_id2 = fork();
		
            if(child_id2 < 0) {
		        exit(EXIT_FAILURE);
	        }

	        if(child_id2 == 0) {

                close(1);
		        dup(fd1[1]);
		        close(fd1[0]);
		        char *proc[] = {"ps","aux",NULL};
		        execv("/bin/ps", proc);
	        } else {
		        while((wait(&status)) > 0);
	        	close(0);
		        dup(fd1[0]);
		        close(fd1[1]);

			close(1);
			dup(fd2[1]);
			close(fd2[0]);
				char *head[] = {"head", "-5", NULL};
				execv("/usr/bin/head", head);
			}
    }else{
                	close(0);
		        dup(fd2[0]);
		        close(fd2[1]);
		        char *sort[] = {"sort","-nrk","3,3",NULL};
		        execv("/usr/bin/sort", sort);
    }    
}
