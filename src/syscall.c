#include "uMPStypes.h"
#include "types11.h"
#include "pcb.e"
#include "asl.e"
#include "myconst.h"
#include "scheduler.h"

extern state_t* pnew_old_areas[NUM_CPU][NUM_AREAS];

/* Handlers delle 11 System Call */



/* System Call #1  : Create Process
 * genera un processo figlio del processo chiamante
 * statep   = indirizzo fisico del nuovo processo
 * priority = priorità del nuovo processo
 * return  -> 0 ok / -1 errore (coda piena PLB)
 */
int create_process(state_t *statep, int priority)
{

}

/* System Call #2  : Create Brother
 * genera un processo fratello del processo chiamante
 * statep   = indirizzo del nuovo processo
 * priority = priorità del nuovo processo
 * return  -> 0 ok / -1 errore
 */
int create_brother(state_t *statep, int priority)
{
}


/* System Call #3  : Terminate Process
 * termina il processo corrente e tutti i discendenti
 * LIBERARE TUTTE LE RISORSE
 */
void terminate_process()
{
	/* dealloco ricorsivamente il processo e i figli */
}


/* System Call #4  : Verhogen
 * esegue la V sul semaforo con chiave semKey
 * il primo processo in coda sul semaforo va in esecuzione
 */
void verhogen(int semKey)
{
	/* puntatore al processo rilasciato dal semaforo */
	pcb_t *processoLiberato;
	/* libero il processo dal semaforo
	*processoLiberato = removeBlocked(semKey);
	if(*processoLiberato != NULL)
	{
		 decrementare Soft Block Count 
		 inserire processo nella Ready Queue del processore più libero
	 
	riprendere l'esecuzione del processo che ha chiamato la SYSCALL*/
}


/* System Call #5  : Passeren
 * esegue la P sul semaforo con chiave semKey
 * il processo che ha chiamato la syscall si mette in attesa
 */
void passeren(int semKey)
{
	/* processo corrente: processoCorrente */
	/* inserisco il processo nella coda del semaforo */
	pcb_t* processoCorrente;
	if(insertBlocked(semKey, processoCorrente) == FALSE)
	{
		/* incremento Soft Block Count */

	}
	else
	{
		/* continuo l'esecuzione */
	}
}


/* System Call #6  : Get CPU Time
 * restituisce il tempo CPU usato dal processo in millisecondi
 * -> IL KERNEL DEVE TENERE LA CONTABILITA DEL TEMPO CPU DEI PROCESSI
 */
int get_cpu_time() /* FIXME deve restituire cpu_t, dove è dichiarato? */
{
}


/* System Call #7  : Wait Clock
 * esegue una P sul semaforo dello PSEUDO CLOCK TIMER (PCT)
 * il PCT esegue una V ogni 100 millisecondi e sblocca tutti i processi
 */
void wait_clock()
{
}


/* System Call #8  : Wait I/O
 * esegue una P sul semaforo del device specificato dai parametri
 * intNo = linea di interrupt
 * dnum  = numero del device
 * waitForTermRead = operazione di terminal read/write
 * return -> status del device
 */
int wait_io(int intNo, int dnum, int waitForTermRead)
{
}

/* System Call #9  : Specify PRG State Vector
 * definire handler personalizzato per Program Trap per il processo corrente
 * oldp = indirizzo della custom OLDAREA
 * newp = indirizzo della custom NEWAREA
 */
void specify_prg_state_vector(state_t *oldp, state_t *newp)
{
	/* ottengo il processore corrente */
	U32 prid = getPRID();
	/* ottengo il processo chiamante */
	state_t *OLDAREA = pnew_old_areas[prid][OLD_SYSBP];
	/* carico il processo corrente */
	pcb_t *processoCorrente = getCurrentProc(prid);
	/* copio i custom handlers */
	copyState(oldp, processoCorrente->custom_handlers[OLD_TRAP]); 	
	copyState(newp, processoCorrente->custom_handlers[NEW_TRAP]);
}

/* System Call #10 : Specify TLB State Vector
 * definire handler personalizzato per TLB Exception per il processo corrente
 * oldp = indirizzo della custom OLDAREA
 * newp = indirizzo della custom NEWAREA
 */
void specify_tlb_state_vector(state_t *oldp, state_t *newp)
{
	/* ottengo il processore corrente */
	U32 prid = getPRID();
	/* ottengo il processo chiamante */
	state_t *OLDAREA = pnew_old_areas[prid][OLD_SYSBP];
	/* carico il processo corrente */
	pcb_t *processoCorrente = getCurrentProc(prid);
	/* copio i custom handlers */
	copyState(oldp, processoCorrente->custom_handlers[OLD_TLB]); 	
	copyState(newp, processoCorrente->custom_handlers[NEW_TLB]);
}

/* System Call #11 : Specify SYS State Vector
 * definire handler personalizzato per SYSCALL/BreakPoint per il processo corrente
 * oldp = indirizzo della custom OLDAREA
 * newp = indirizzo della custom NEWAREA
 */
void specify_sys_state_vector(state_t *oldp, state_t *newp)
{
	/* ottengo il processore corrente */
	U32 prid = getPRID();
	/* ottengo il processo chiamante */
	state_t *OLDAREA = pnew_old_areas[prid][OLD_SYSBP];
	/* carico il processo corrente */
	pcb_t *processoCorrente = getCurrentProc(prid);
	/* copio i custom handlers */
	copyState(oldp, processoCorrente->custom_handlers[OLD_SYSBP]); 	
	copyState(newp, processoCorrente->custom_handlers[NEW_SYSBP]);
}
