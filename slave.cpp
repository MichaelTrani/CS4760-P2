/*
Author: Michael Trani
February 2022
*/

#include"p2.h"
//using namespace std;


int main(int argc, char* argv[])
{   
    std::string programName = argv[0];

    int option;
    std::string fname = "logfile.";
    std::string timeIn;

    while ((option = getopt(argc, argv, "i:t:")) != -1) {
        switch (option)
        {
        case 'i':
            fname += whitespaceRemover(optarg);
            break;

        case 't':
            timeIn = whitespaceRemover(optarg); 

        default:
            break;
        }
    }

    std::ofstream logfile(fname);
    logfile << "Execution Time: " << timeIn << std::endl;

    sleep(5);
    int shmid = shmget(SHMKEY, BUFF_SZ, 0777);
    if (shmid == -1){
        std::cerr << "Slave: " << fname << " Error in shmget cint. " << std::endl;
        logfile << "Slave: " << fname << " Error in shmget cint. " << std::endl;
        exit(1);
    }

    int* cint = (int*)(shmat(shmid, 0, 0));  // read
    logfile << "ticket number: " << *cint << std::endl;

    /*
    for ( i = 0; i < 5; i++ )
    {
        execute code to enter critical section;
        sleep for random amount of time (between 0 and 5 seconds);
        critical_section();
        sleep for random amount of time (between 0 and 5 seconds);
        execute code to exit from critical section;
    }
    
    */



    logfile << "Completion Time: " << timeFunction() << std::endl;;
    logfile.close();
    return 0;
}



/*
The slave just writes the message into the file inside the critical section. 

We want to have some log messages to see that the process is behaving appropriately and it does follow the guidance required for critical section.
If a process starts to execute code to enter the critical section, it must print a message to that effect in its log file.
I’ll suggest naming the log file as logfile.xx where xx is the process number for the child, passed via the command line. 
It will be a good idea to include the time when that happens. 
Also, indicate the time in log file when the process actually enters and exits the critical section. 
Within the critical section, wait for a random number of seconds (in the range [1,5]) before you write into the file, and then, wait for another [1,5] seconds before leaving the critical section.
For each child process, tweak the code so that the process requests and enters the critical section at most five times.

The code for each child process should use the following template:


The bakery algorithm requires you to specify the number of processes in the system. 
I’ll suggest specifying it as a constant macro (use #define) in a header file called config.h. 
Please keep this number under 20. 
This is the maximum number of processes that can be forked. 
The number of processes actually forked will come from the number specified on command line when you start the program.

*/