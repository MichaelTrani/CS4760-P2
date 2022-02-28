/*  Author: Michael Trani
    February 2022       */

#include"p2.h"
#include"config.h"

// Shared mem vars
int shmid_ticketNumber;
int* ticketNumber_ptr;

int shmid_choosing;
int* choosing_ptr;

std::string error_message;

pid_t parental;
pid_t children;
int cprocess;

// for args
std::string timeIn, processnum;
int maxslaves; 

int main(int argc, char* argv[]){   

    error_message = argv[0];
    error_message.erase(0, 2);        // remove annoying ./ at start
    error_message += "::ERROR: ";
    std::string logname = "logs/logfile.";

    srand(time(0));
    int timerLock = 1 + rand() % 5;  // used for waiting period

    int option;

    // input fed from master
    while ((option = getopt(argc, argv, "i:t:n:")) != -1) {
        switch (option)
        {
            case 'i':   // pid
                processnum = optarg;
                logname += processnum;
                std::cout << "processnum:" << processnum << "\n";
                break;

            case 't':   // time in
                timeIn = optarg; 
                std::cout << "timeIn:" << timeIn << "\n";
                break;
            case 'n':
                maxslaves = atoi(optarg);
                std::cout << "maxslaves:" << maxslaves << "\n";
                break;
            default:
                break;
        }
    }

    // Log small details
    std::ofstream logfile(logname);
    std::ofstream primary("cstest");
    logfile << "Execution Time: " << timeIn << std::endl;
    logfile << "This program waits: " << timerLock << " seconds.\n";

    // Shared Memory block
    shmkey = ftok("./master", 246810);  // ##### KEY 1 
    shmid_shared_num = shmget(shmkey, sizeof(shared_num_ptr), 0777 | IPC_CREAT);
    shared_num_ptr = (int*)shmat(shmid_shared_num, NULL, 0);

    shmkey = ftok("./slave", 246811);   // ##### Key 2
    shmid_choosing = shmget(shmkey, sizeof(choosing_ptr), 0777 | IPC_CREAT);
    choosing_ptr = (int*)shmat(shmid_choosing, NULL, 0);

    shmkey = ftok("./slave", 246812);   // #### Key #3
    shmid_ticketNumber = shmget(shmkey, sizeof(ticketNumber_ptr), 0777 | IPC_CREAT);
    ticketNumber_ptr = (int*)shmat(shmid_ticketNumber, NULL, 0);


    sleep(2); // remove me when time is right


    int shmid = shmget(SHMKEY, STR_SZ, 0777);   // get process id from parent
    if (shmid == -1){
        std::cerr << "Slave: " << logname << " Error in shmget cint. " << std::endl;
        logfile << "Slave: " << logname << " Error in shmget cint. " << std::endl;
        exit(1);
    }

    int* cint = (int*)(shmat(shmid, 0, 0));  // read
    logfile << "Program number: " << *cint << std::endl;

    struct timespec current;
    long current_time;
    int progs = 0;

    parental = getppid();
    children = getpid();
    cprocess = (int)(children - parental);

    
    for (int i = 0; i < PROCESS_RUNNING_MAX; i++ )
    {
        
        //execute code to enter critical section; log file this
        choosing_ptr[(cprocess - 1)] = 1;
        for (progs = 0; progs < maxslaves; progs++) {}
        //sleep(timerLock);
        //primary << timeFunction() <<  " Queue " << ticketnumber << "File modified by " << processnum << std::endl;
        //sleep(timerLock);
        //execute code to exit from critical section;
    }
    
 



    logfile << "Completion Time: " << timeFunction() << "\n\n";
    logfile.close();
    return 0;
}



/*
The slave just writes the message into the file inside the critical section. 

We want to have some log messages to see that the process is behaving appropriately and it does follow the guidance required for critical section.
If a process starts to execute code to enter the critical section, it must print a message to that effect in its log file.
It will be a good idea to include the time when that happens. 
Also, indicate the time in log file when the process actually enters and exits the critical section. 
Within the critical section, wait for a random number of seconds (in the range [1,5]) before you write into the file, and then, wait for another [1,5] seconds before leaving the critical section.
For each child process, tweak the code so that the process requests and enters the critical section at most five times.


The bakery algorithm requires you to specify the number of processes in the system. 

*/