#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>

#define SHARED_MEM_NAME "/shm"
#define SHM_SIZE 30

pthread_mutex_t mutex_var = PTHREAD_MUTEX_INITIALIZER;

int shm_id, my_pos = 0, state=0;
char *shm_ptr, *point;






