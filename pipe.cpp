// Vidhur Vashisht

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int  main()
{
  int pipefd[2];
  int check = pipe(pipefd);
  int number;
  int count, count_two;

  if (check < 0) {
    cout<< "The pipe returned an error" << endl;
    return 0;
  }

  pid_t pid = fork();
  pid_t pid2;

  if (pid < 0) {
    cout<< "There is an error with the Process ID" << endl;
    return 0;
  }

  else if (pid == 0) {
    pid2 = getpid();
    for(count = 0; count < 10; count++)
    {
      read(pipefd[0],&number,sizeof(number));
      cout << "Child:  " << pid2 << " Writing " << number + 10 << endl;
      sleep(2);
    }
    return 0;
  }

  else {
    pid2 = getpid();
    number = 1;
    for(count_two = 0; count_two < 10; count_two++)
    {
      cout << "Parent: " << pid2 << " Writing " << number << endl;
      write(pipefd[1],&number,sizeof(number));
      number++;
      sleep(2);
    }
    wait(NULL);
    cout << "The child process has successfully terminated. The parent process will now terminate, and the code will end. " << endl;
  }

  return 0;
}
