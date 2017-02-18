#include <setjmp.h>
#include <avr/io.h>

#include "tinythreads.h"
#include <avr/interrupt.h>

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
                        *((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4

//static int blinkTimer = 0;
struct thread_block {
    void (*function)(int);   // code to run
    int arg;                 // argument to the above
    thread next;             // for use in linked lists
    jmp_buf context;         // machine state
    char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];

struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;
	
static void initialize(void) {
	int i;
	for (i=0; i<NTHREADS-1; i++)
	threads[i].next = &threads[i+1];
	threads[NTHREADS-1].next = NULL;
	//External input
	EIMSK = (1 << PCIE1);
	PCMSK1 = (1 << PCINT15);
	//activate the button
	PORTB = (1 << PINB7);
	//timer with prescaler 1024
	TCCR1B = (1<<CS12) | (1 << CS10) | (1 << WGM12);
	//500 ms period
	OCR1A = 0xF42;

	TIMSK1 = (1 << OCIE1A);
	//reset timer
	TCNT1 = 0;
	initialized = 1;
}

static void enqueue(thread p, thread *queue) {

	p->next = NULL;
	if (*queue == NULL){
		*queue = p;
		}else{
		thread q = *queue;
		p->next = q;
		*queue = p;
	}
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
    }
    return p;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

void spawn(void (* function)(int), int arg) {
    thread newp;

    DISABLE();
    if (!initialized) initialize();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        ENABLE();
        current->function(current->arg);
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    SETSTACK(&newp->context, &newp->stack);

    enqueue(newp, &readyQ);
    ENABLE();
}

void yield(void) 
{
	DISABLE();	
	if(readyQ != NULL){
		thread next = dequeue(&readyQ);
		enqueue(current, &readyQ);
		dispatch(next);
	} ENABLE();
}


void lock(mutex *m) {
	DISABLE();
	if(m->locked == 0){
		m->locked = 1;
	}
	else{
		thread next = dequeue(&readyQ);
		enqueue(current, &(m->waitQ));
		dispatch(next);
	}
	ENABLE();
}

void unlock(mutex *m) {
	DISABLE();
	if(m->waitQ != 0){
		thread next = dequeue(&(m->waitQ));
		enqueue(current, &readyQ);
		dispatch(next);
	}
	else{
		m->locked = 0;
	}
	ENABLE();
}
