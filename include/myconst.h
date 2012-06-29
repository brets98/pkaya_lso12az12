#include "const.h"
#include "uMPStypes.h"

/* Constants */
/* TODO: trovare  modo di leggere num CPU da emulatore ma potendolo
 * usare come costante (ad esempio per dimensionare gli array) */
#define NCPU_ADDR 0x10000500
#define NUM_CPU 4 
/* #define NUM_CPU (int)*(int*)NCPU_ADDR	 */

#define TIME_SCALE BUS_TIMESCALE

/* Interrupt Delivery Controller Processor Interface Register Map
 * Sono separate per ogni CPU ma condividono lo stesso address-space */
#define INBOX_ADDR 0x10000400
#define OUTBOX_ADDR 0x10000404
#define TPR_ADDR 0x10000408
#define BIOS_RES1_ADDR 0x1000040c
#define BIOS_RES2_ADDR 0x10000410

/* Interrupt Routing Tables (formula pag.61 princOfOperations.pdf) */
#define DEV_IRT_BASE 0x10000300 /* Linea 2 */
#define IRT_ENTRY(line,dev) \
	(line == 2? DEV_IRT_BASE:DEV_IRT_BASE+(WORD_SIZE*((line-2)*8+dev)))
#define DYN_IRT_MASK 0x10000000 

/* Interrupt Lines (custom) */
#define INT_PLT 1


/* Dati riguardanti i pcb_t e lo scheduler */
#define MAX_PCB_PRIORITY		10
#define MIN_PCB_PRIORITY		0
#define DEFAULT_PCB_PRIORITY		5
#define TIME_SLICE 5*(*(memaddr *)TIME_SCALE)*1000 /* espresso in ms, 1ms = TIME_SCALE*1000 clock_ticks */

/* Costanti di utilità */
#define STATUS_TE 0x08000000
#define RESET 0
#define PASS 0 /* per CAS */
#define FORBID 1 /* per CAS */

/* Organizzazione della memoria */
#define ROM_RES_FRAME_START 0x20000000
#define AREAS_SIZE (sizeof(state_t)*NUM_AREAS*NUM_CPU)
#define AREAS_DISTANCE (sizeof(state_t))/* distanza in byte tra due aree dello stesso tipo */

#define HSTACK_SIZE 1024 /* per dividere il frame in 4 unità da 1KB */
#define HSTACKS_SIZE 4*HSTACK_SIZE*NUM_CPU /* Dimensione totale degli stack degli handler */
#define HSTACKS_START	RAMTOP	/* Inizio degli stack per gli handler */
#define HSTACKS_END		RAMTOP-(HSTACKS_SIZE) /* Fine degli stack per gli handler */
						 
#define PSTACKS_START 	(RAMTOP-HSTACKS_SIZE)
#define PSTACKS_END 	(ROM_RES_FRAME_START+AREAS_SIZE)
#define PSTACK_RES_FRAMES 	((PSTACKS_START-PSTACKS_END)/FRAME_SIZE)
#define PSTACK_RES_FRAMES_CPU 	(PSTACK_RES_FRAMES/NUM_CPU)

/* NUMERI DELLE SYSTEM CALL */

#define CREATEPROCESS		1
#define CREATEBROTHER		2
#define TERMINATEPROCESS	3
#define VERHOGEN			4
#define PASSEREN			5
#define GETCPUTIME			6
#define WAITCLOCK			7
#define WAITIO				8
#define SPECPRGVEC			9
#define SPECTLBVEC			10
#define SPECSYSVEC			11

/* identificativi New e Old Area generici */
#define NUM_AREAS 8

#define OLD_INTS 0
#define NEW_INTS 1
#define OLD_TLB 2
#define NEW_TLB 3 
#define OLD_TRAP 4
#define NEW_TRAP 5 
#define OLD_SYSBP 6
#define NEW_SYSBP 7
