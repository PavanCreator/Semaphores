#include <stdio.h>
#include <string.h>

#include <opencv2/opencv.hpp>

#include <unistd.h>
#include <pthread.h>
#include <sched.h>


void CreateSHM(void);
void do_process(void);

void SemaUnlink(void);
void CreateSemaphore(void);
void SHM_Monitor(void);
void Read_SHM(void);
void MutexInit(void);
void Destroy(void);