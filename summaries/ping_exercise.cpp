
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv){

	pid_t pid;
	int fd[2];


	for(int i=1;i<argc;i++){

		
		if(pipe(fd)!=0){
			perror(argv[0]);
			exit(1);
		}

		if( (pid=fork() )==0){
			//child
			close(fd[0]);
			close(1);
			close(2);
			dup2(fd[1],1);
			if(execl("/bin/ping", "/bin/ping","-c","1","argv[i]",(char*)0)==-1){ 
				perror(argv[0]);
				exit(1);
			}

		}
		pid_t pid2;
		if( (pid2=fork() )==0){
			close(fd[1]);
			dup2(fd[0],0);
			int teller=0;
			std::string lijn;
			std::getline(std::cin, lijn);
			while(!std::cin.fail()){
				teller++;
				if(teller==2 && lijn.substr(0,2)=="64") {
					std::cout << argv[i] << " bereikbaar" << std::endl;
				} else {
					std::cout << argv[i] << " niet bereikbaar" << std::endl;
				}

				std::getline(std::cin, lijn);
			}
			exit(0);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
		waitpid(pid2, NULL, 0);

		} // for

	return 0;

}
