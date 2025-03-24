#include <time.h> // Changed - added so that random numbers can be generated

PRIVATE struct proc * pick_proc(void)
{
/* Decide who to run now.  A new process is selected an returned.
 * When a billable process is selected, record it in 'bill_ptr', so that the 
 * clock task can tell who to bill for system time.
 */
  register struct proc *rp;			/* process to run */
  int q;				/* iterate over queues */

  /* Check each of the scheduling queues for ready processes. The number of
   * queues is defined in proc.h, and priorities are set in the task table.
   * The lowest queue contains IDLE, which is always ready.
   */
  srand(time(NULL)); // Changed - added to set seed to ranomly generate number

  // Iterates through each of the process queues from highest to lowest prority
  for (q=0; q < NR_SCHED_QUEUES; q++) {
	int skipProb = (rand() % 100) + 1; // Changed - this generates a random nubmer between 1 and 100 to represent the probability that the current process queue is skipped
	
    // added the || skipProb <= 30 part, the other condition was already there
    if(!(rp = rdy_head[q]) || skipProb <= 30) { // Changed - will skip the current process queue and move on to a lower queue 30% of the time in addition to skipping if it's empty
		TRACE(VF_PICKPROC, printf("queue %d empty\n", q););
		continue;
	}

#if DEBUG_RACE
	rp = random_process(rdy_head[q]);
#endif

    // finds the first process in the current process queue and returns it
	TRACE(VF_PICKPROC, printf("found %s / %d on queue %d\n", 
		rp->p_name, rp->p_endpoint, q););
	assert(proc_is_runnable(rp));
	if (priv(rp)->s_flags & BILLABLE)	 	
		bill_ptr = rp;		/* bill for system time */
	return rp;
  }
  return NULL;
}