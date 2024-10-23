#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define SMPR_1 "/my_semaphore_1"
#define SMPR_2 "/my_semaphore_2"
#define SHARED_MEM_NAME "/shm_for_sema"
#define SHM_SIZE 30

int  shm_id, my_pos = 0, state=0;
char *shm_ptr, *point;

sem_t *sema_1, *sema_2;






