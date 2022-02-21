#include"p2.h"

#define DEFAULT_TIME 100
#define PROCESS_MAX 20
pid_t waitreturn;	// for waiting on process to end


void child();
void parent();

char command[] = "";		// Command to be executed
char path[] = "./slave";		// Path for the command

int main(int argc, char* argv[])
{
    std::string programName = argv[0];

    int option;
    int user_time = DEFAULT_TIME;
    int process_count = 20;

    while ((option = getopt(argc, argv, "t:n:")) != -1) {
        switch (option)
        {

            case 't':
                 user_time = atoi(optarg);
                 break;
            
            case 'n':
                process_count = atoi(optarg);
                if (process_count > PROCESS_MAX) {
                    process_count = PROCESS_MAX;
                    std::cout << "WARNING: process count(n) override: 20 Maximum.\n";
                }
                else
                    process_count = atoi(optarg);
                break;

            default:
                break;
        }
    }

    switch (fork()) {
        case -1:
            std::cout << "Failed to fork" << std::endl;
            return (1);

        case 0:
            child();
            break;

        default:
            parent();
            break;
    }

    return 0;
}

void parent(){
    int status = 0;
    // Get shared memory segment identifier
    int shmid = shmget(SHMKEY, BUFF_SZ, 0777 | IPC_CREAT);
    if (shmid == -1)
    {
        std::cout << "Parent: ... Error in shmget ..." << std::endl;
        exit(1);
    }

    // Get the pointer to shared block
    char* paddr = (char*)(shmat(shmid, 0, 0));
    int* pint = (int*)(paddr);  
    
    *pint = 55;             /* Write into the shared area. */
    sleep(2);

    std::cout << "Parent: Written Val.: = " << *pint << std::endl;
    waitreturn = wait(&status);

}







void child()
{
    sleep(5);
    execl(path, command, (char*)0);

}