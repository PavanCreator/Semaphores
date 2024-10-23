#include "declaration.h"
#include "../include/my_semaphores.h"
#include "logger.h"
#include "log_config.h"
#include "log_levels.h"

using namespace cv;

void CreateSemaphore(void)
{
    sema_1 = sem_open(SMPR_1, O_CREAT, S_IRUSR | S_IWUSR, 0);
    if(sema_1 != SEM_FAILED)
        LOG(LOGGER_LEVEL_INFO, "semaphore 1 creation success\n");
    
    sema_2 = sem_open(SMPR_2, O_CREAT, S_IRUSR | S_IWUSR, 0);
    if(sema_2 != SEM_FAILED)
        LOG(LOGGER_LEVEL_INFO, "semaphore 2 creation success\n");
    
}
void SemaUnlink(void)
{
    sem_unlink(SMPR_1);
    sem_unlink(SMPR_2);
    shm_unlink(SHARED_MEM_NAME);
    LOG(LOGGER_LEVEL_INFO, "SHM & semaphore unlink success\n");
}

void CreateSHM(void)
{
    shm_id = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    
    if(shm_id != -1)
        LOG(LOGGER_LEVEL_INFO,"Shared memory created successfully\n");

    if( ftruncate(shm_id, SHM_SIZE) == -1)
        LOG(LOGGER_LEVEL_INFO,"Failed to set size of SHM\n");
    
    shm_ptr = (char*)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
    LOG(LOGGER_LEVEL_INFO,"shm addr = %p\n", shm_ptr);

    int count = 0, val=65;
    char *ptr = shm_ptr;
    while(count < SHM_SIZE)
    {
        for(int i=0; i<5; i++, val++, count++)
            *ptr++ = val;

        for(int i=0; i<5; i++, count++)
            *ptr++ = '0';
    }
    LOG(LOGGER_LEVEL_INFO,"SHM Created & Data stored in SHM\n");
    ptr = shm_ptr;
    for(int i=0; i<SHM_SIZE; i++)
        printf("%c ", *ptr++);
    printf("\n\n");
}

void do_process(void)
{
    if(fork() == 0)
    {
        LOG(LOGGER_LEVEL_INFO,"child process\n");
        for(; my_pos < SHM_SIZE; )
        {
            sem_wait (sema_2);
            while( my_pos < SHM_SIZE && shm_ptr[my_pos] != '0' )
            {
                printf("%c ", shm_ptr[my_pos]);
                my_pos++;
            }
            if(shm_ptr[my_pos] == '0')
            {
                state = 0; my_pos++;
                sem_post(sema_1);
            }
        }

    }
    else
    {
        LOG(LOGGER_LEVEL_INFO,"parent process\n");

        /*int shm1 = shm_open(SHARED_MEM_NAME, O_RDONLY, 0444);
        if(shm1 != -1)
            LOG(LOGGER_LEVEL_INFO,"opened SHM in Read only mode\n");
        */
        for(; my_pos < SHM_SIZE; )
        {
            if( shm_ptr[my_pos] != 0 )
            {
                state = 1;
                sem_post(sema_2);
                sem_wait(sema_1);
            }
            else
                my_pos++;
        }

    }
}






