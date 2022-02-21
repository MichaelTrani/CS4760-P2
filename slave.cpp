#include"p2.h"

int main()
{

    sleep(5);
    int shmid = shmget(SHMKEY, BUFF_SZ, 0777);

    if (shmid == -1)
    {
        std::cerr << "Child: ... Error in shmget ..." << std::endl;
        exit(1);
    }

    int* cint = (int*)(shmat(shmid, 0, 0));  // read

    std::cout << "Slave: Read Val. = " << *cint << std::endl;

    printf("hello from %s!\n", "Slave");


    return 0;
}