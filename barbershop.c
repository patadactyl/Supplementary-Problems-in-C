//
//  barbershop.c
//  
//
//  Created by Patrick Charlton on 4/30/19.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

// The maximum number of barber and customer processes
#define MAX_CUSTOMERS 30
#define MAX_BARBERS 3

// Function prototypes…
void *customer(void *num);
void *barber(void *);
void P(int semid, int index);
void V(int semid, int index);

void randwait(int secs);

// Define the semaphores.

// waitingRoom Limits the # of customers allowed
// to enter the waiting room at one time.
sem_t waitingRoom;

// barberChair ensures mutually exclusive access to
// the barber chair.
sem_t barberChair;

// barberPillow is used to allow the barber to sleep
// until a customer arrives.
sem_t barberPillow;

// seatBelt is used to make the customer to wait until
// the barber is done cutting his/her hair.
sem_t seatBelt;

// Flag to stop the barber thread when all customers
// have been serviced.
int allDone = 0;

int main(int argc, char *argv[]) {
    pid_t barbid[MAX_BARBERS], custid[MAX_CUSTOMERS];
    long RandSeed;
    int i, numCustomers, numChairs, numBarbers;
    int customers[MAX_CUSTOMERS];
    int fd[2];
    

    
    // Initialize the numbers array.
    for (i=0; i < MAX_CUSTOMERS; i++) {
        numCustomers[i] = i;
    }
    
    // Initialize the semaphores with initial values…
    sem_init(&waitingRoom, 0, numChairs);
    sem_init(&barberChair, 0, 1);
    sem_init(&barberPillow, 0, 0);
    sem_init(&seatBelt, 0, 0);
    
    // Create the barber.
    if (pipe (pipe_fd) < 0) {       /* Create pipe and check for error */
        perror("pipe error");
        exit (1);
    }
    
    if ((pid1 = fork()) < 0) {      /* Create fork and check for error */
        perror ("error in fork");
        exit (1);
    }
    
    for (i=0; i<numBarbers; i++) {
        /* create barber processes */
        if (0 == barb1id)
        { // processing for Barber1
            while (1) {
                P(customers);          /*go to sleep if no customers*/
                P(mutex);
                waiting=waiting-1;
                V(barbers);
                V(mutex);
                cut_hair();
            }
        }
    }
        

    
    // Create the customers.
    for (i=0; i<numCustomers; i++) {
        /* implementation with threads
        pthread_create(&tid[i], NULL, customer, (void *)&Number[i]);
        sleep(1); */
        
        if (0 == custid[1])
        { /* processing for child == reader */
            printf ("The reader process begins.\n");
            
            P(semid, buf_used);  /* wait semaphore for something used */
            value = buffer[*out];
            *out = (*out + 1) % BUF_SIZE;
            printf ("First Customer's report: item %2d == %2d\n", i_child, value);
            V(semid, buf_space); /* signal semaphore for space available */
            if ((i_child % 3) == 1)
                sleep(1);  /* take time to process every third element */
        }
            printf ("Reader done.\n");
        }
        else
        { /* processing for parent == writer */
            printf ("The writer process begins.\n");
            
            P(semid, buf_space);/* wait semaphore for space available */
            buffer[*in] = j_child*j_child;    /* put data in buffer */
            *in = (*in + 1) % BUF_SIZE;
            printf ("Subsequent Customer's report: item %2d put in buffer\n", j_child);
            V(semid, buf_used); /* signal semaphore for something used */
            if ((j_child % 4) == 0) {
                    sleep(1); /* take time to generate every fourth element */
            }
            
            waitpid(pid, NULL, 0);
            printf ("Writer done.\n");
            
            /* deallocate shared memory */
            munmap (shared_memory, SHARED_MEM_SIZE);
            
            /* Remove the semaphore from the system and destroy the set of
             semaphores and data structure associated with it. */
            if (semctl (semid, 0, IPC_RMID) < 0)
            {  perror ("error in removing semaphore from the system");
                exit (1);
            }
            printf ("Semaphore cleanup complete.\n");
        }
    }
    
    // Join each of the threads to wait for them to finish.
    for (i=0; i<numCustomers; i++) {
        pthread_join(tid[i],NULL);
        sleep(1);
    }
    
    // When all of the customers are finished, kill the
    // barber thread.
    allDone = 1;
    sem_post(&barberPillow); // Wake the barber so he will exit.
    pthread_join(btid,NULL);
}


void *customer(void *number) {
    int num = *(int *)number;
    
    // Leave for the shop and take some random amount of
    // time to arrive.
    printf("Customer %d leaving for barber shop.\n", num);
    randwait(2);
    printf("Customer %d arrived at barber shop.\n", num);
    
    // Wait for space to open up in the waiting room…
    sem_wait(&waitingRoom);
    printf("Customer %d entering waiting room.\n", num);
    
    // Wait for the barber chair to become free.
    sem_wait(&barberChair);
    
    // The chair is free so give up your spot in the
    // waiting room.
    sem_post(&waitingRoom);
    
    // Wake up the barber…
    printf("Customer %d waking the barber.\n", num);
    sem_post(&barberPillow);
    
    // Wait for the barber to finish cutting your hair.
    sem_wait(&seatBelt);
    
    // Give up the chair.
    sem_post(&barberChair);
    printf("Customer %d leaving barber shop.\n", num);
    
    /* wait(mutex)
     if (customers_waiting == 0) {
     signal(mutex);
     wait(barber_sleeping);
     wait(mutex);
     }
     customers_waiting--;
     signal(mutex);
     signal(customer_queue);
     do_cut_hair();
     signal(cut_done); */
}

void *barber(void *junk) {
    // While there are still customers to be serviced…
    // Our barber is omnicient and can tell if there are
    // customers still on the way to his shop.
    while (!allDone) {
        
        // Sleep until someone arrives and wakes you..
        printf("The barber is sleeping\n");
        sem_wait(&barberPillow);
        
        // Skip this stuff at the end…
        if (!allDone) {
            
            // Take a random amount of time to cut the
            // customer’s hair.
            printf("The barber is cutting hair\n");
            randwait(2);
            printf("The barber has finished cutting hair.\n");
            
            // Release the customer when done cutting…
            sem_post(&seatBelt);
        }
        else {
            printf("The barber is going home for the day.\n");
        }
    }
    
    /* wait(mutex);
     if (customers_waiting == n) {
     signal(mutex);
     return;
     }
     customers_waiting++;
     if (customers_waiting == 1) {
     signal(barber_sleeping);
     }
     signal(mutex);
     wait(customer_queue);
     get_hair_cut();
     wait(cut_done);
     */
}

void P(int semid, int index)
{/* procedure to perform a P or wait operation on a semaphore of given index */
    struct sembuf sops[1];  /* only one semaphore operation to be executed */
    
    sops[0].sem_num = index;/* define operation on semaphore with given index */
    sops[0].sem_op  = -1;   /* subtract 1 to value for P operation */
    sops[0].sem_flg = 0;    /* type "man semop" in shell window for details */
    
    if (semop (semid, sops, 1) == -1)
    {  perror ("error in semaphore operation");
        exit (1);
    }
}

void V(int semid, int index)
{/* procedure to perform a V or signal operation on semaphore of given index */
    struct sembuf sops[1];  /* define operation on semaphore with given index */
    
    sops[0].sem_num = index;/* define operation on semaphore with given index */
    sops[0].sem_op  = 1;    /* add 1 to value for V operation */
    sops[0].sem_flg = 0;    /* type "man semop" in shell window for details */
    
    if (semop (semid, sops, 1) == -1)
    {  perror ("error in semaphore operation");
        exit (1);
    }
}

void randwait(int secs) {
    int len;
    
    // Generate a random number…
    len = (int) ((1 * secs) + 1);
    sleep(len);
}
