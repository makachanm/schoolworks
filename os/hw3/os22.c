#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <limits.h>

// Linux List Code in Soruce

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({                      \
        const __typeof__(((type *)0)->member) *__mptr = (ptr);  \
        (type *)((char *)__mptr - offsetof(type, member)); })

#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)

struct list_head {
	struct list_head* next, * prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

static inline void __list_add(struct list_head* new,
	struct list_head* prev,
	struct list_head* next) {
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add(struct list_head* new, struct list_head* head) {
	__list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head* new, struct list_head* head) {
	__list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head* prev, struct list_head* next) {
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(struct list_head* entry) {
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}

static inline void list_del_init(struct list_head* entry) {
	__list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry);
}

static inline void list_move(struct list_head* list, struct list_head* head) {
	__list_del(list->prev, list->next);
	list_add(list, head);
}

static inline void list_move_tail(struct list_head* list,
	struct list_head* head) {
	__list_del(list->prev, list->next);
	list_add_tail(list, head);
}

static inline int list_empty(const struct list_head* head) {
	return head->next == head;
}

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_for_each(pos, head) \
  for (pos = (head)->next; pos != (head);	\
       pos = pos->next)

#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; prefetch(pos->prev), pos != (head); \
        	pos = pos->prev)

#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, __typeof__(*pos), member);	\
	     &pos->member != (head);					\
	     pos = list_entry(pos->member.next, __typeof__(*pos), member))

#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = list_entry((head)->prev, __typeof__(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.prev, __typeof__(*pos), member))

#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, __typeof__(*pos), member),	\
		n = list_entry(pos->member.next, __typeof__(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, __typeof__(*n), member))

#define list_for_each_entry_safe_reverse(pos, n, head, member)		\
	for (pos = list_entry((head)->prev, __typeof__(*pos), member),	\
		n = list_entry(pos->member.prev, __typeof__(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.prev, __typeof__(*n), member))

#if 0    //DEBUG
#define debug(fmt, args...) fprintf(stderr, fmt, ##args)
#else
#define debug(fmt, args...)
#endif

#define CPU(i) (i + 1)

typedef enum {
	CPU_IDLE,
	CPU_RUNNING,
	CPU_CTXSWITCH,
	CPU_HALTED,
} CPU_STATE;

// Code Tuple: opcode & opcode excution due time data
typedef struct {
    unsigned char op;
    unsigned char len;
} code_tuple;

/* 
Process: pid, arrival time, code length(in raw),
         pointers for this process's code tuple.
		 linked list head: job, ready, wait (for process queue)
*/
typedef struct {
    int pid;
    int arrival_time;
    int code_bytes;

    code_tuple* code;
    struct list_head job;
	int pc;
	int used_clock;
} process;

/*
CPU: holds excution state, clock information, 
     currunt queue capacity(used), and saving information
     for context switching action.
*/
typedef struct {
	CPU_STATE state;

	int processor_id;
	int total_clock;
	int idle_clock;

	int currunt_process_amount;

	int before_clk;
	int csbefore_pid;
	int csafter_pid;
	CPU_STATE csbefore_state;
} cpu; 

// F I X E D
int processor_count = 2;
cpu *processors;

LIST_HEAD(job_queue);

LIST_HEAD(cpu0_ready_queue);
LIST_HEAD(cpu1_ready_queue);

// hardcoded... it can be get improved plexiblity with macros, but not enough time to do that.
struct list_head* get_cpu_ready_queue(int cpuid) {
	switch(cpuid) {
		case 0:
			return &cpu0_ready_queue;

		case 1:
			return &cpu1_ready_queue;
	}
}

// from os2-1. same code!!
void read_and_register_tasks() {
	process *p;

	while(1) {
		p = (process *)malloc(sizeof(process));
        
		if(!fread(p, 12, 1, stdin)) {
			free(p);
			break;
		}

    	int code_length = (p->code_bytes / 2);
        
    	code_tuple* codes;
    	codes = (code_tuple *)malloc(sizeof(process) * code_length);

    	for(int i = 0; i < code_length; i++) {
        	fread(&codes[i], sizeof(code_tuple), 1, stdin);
    	}

    	p->code = codes;
		p->pc = 0;
		p->used_clock = 0;

    	INIT_LIST_HEAD(&p->job);

    	list_add_tail(&p->job, &job_queue);
	}
}

// makes process PID 100, contains NOP opertation.
// and push process into selected cpu's queue. 
void insert_idle_process(int cpu_id) {
	process *p;
	code_tuple *c;

	p = (process *)malloc(sizeof(process));
	p->pid = 100;
	p->code_bytes = 2;
	p->arrival_time = 0;
	p->used_clock = 0;
	p->pc = 0;

	c = (code_tuple *)malloc(sizeof(code_tuple));
	c->op = 0xFF;
	c->len = 0x01;

	p->code = c;

	INIT_LIST_HEAD(&p->job);
	list_add_tail(&p->job, get_cpu_ready_queue(cpu_id));

	processors[cpu_id].currunt_process_amount++;

	printf("%04d CPU%d: Loaded PID: %03d\tArrival: %03d\tCodesize: %03d\n",
		processors[cpu_id].total_clock, CPU(cpu_id), p->pid, p->arrival_time, p->code_bytes);
}

// make processor to CONTEXT SWITCH STATE
// mark last information of processor to restore state after CTXSWCH is over 
void task_ctxswtich(int cpu_id, process* before, process* after) {
	processors[cpu_id].before_clk = processors[cpu_id].total_clock;
	processors[cpu_id].csbefore_pid = before->pid;
	processors[cpu_id].csafter_pid = after->pid;
	processors[cpu_id].csbefore_state = processors[cpu_id].state;

	processors[cpu_id].state = CPU_CTXSWITCH;

	return;
}

// do acutal CPU jobs
// check the currunt state, and do incresement of clock.
// check the instrcution opcode, and do I/O job.
// check clock and progress of opcode, and manage process's pc.
void task_do_excute_perop(int processor_id, process* p) {
	if(processors[processor_id].state == CPU_HALTED) return;
	// is processor on a switching? just stop all excution
	if(processors[processor_id].state == CPU_CTXSWITCH) { 
		processors[processor_id].total_clock++;
		processors[processor_id].idle_clock++;
		return;
	}

	int code_length = (p->code_bytes / 2);
	int excution_time = p->code[p->pc].len;

	if(p->code[p->pc].op == 1) {
		if(p->used_clock == 0) {
			printf("%04d CPU%d: OP_IO START len: %03d ends at: %04d\n",
					processors[processor_id].total_clock, CPU(processor_id), excution_time, processors[processor_id].total_clock + excution_time);
		}
		processors[processor_id].idle_clock++;
	}

	// if operation is NOP? 
	// then count idle clock and stop increase program counter
	if(p->code[p->pc].op == 0xFF) {
		processors[processor_id].state = CPU_IDLE;
		processors[processor_id].idle_clock++;
	} else {
		p->used_clock++;
	}

	processors[processor_id].total_clock++;

	if(excution_time <= p->used_clock) {
		p->used_clock = 0;
		p->pc = (p->pc + 1);
	}

	return;
}

void task_check_job_and_excute() {
	process *cur, *next;
	
	for(int i = 0; i < processor_count; i++) {
		// clear the switching state -
		// it used 10 clock to switch? 
		// then print information and restore state of excution.
		if(processors[i].state == CPU_CTXSWITCH) {
			if((processors[i].total_clock - processors[i].before_clk) >= 10) {
				printf("%04d CPU%d: Switched\tfrom: %03d\tto: %03d\n", 
					processors[i].total_clock, CPU(i), processors[i].csbefore_pid, processors[i].csafter_pid);
				processors[i].state = processors[i].csbefore_state;
			}
		}

		process* excuted;
		list_for_each_entry_safe(cur, next, get_cpu_ready_queue(i), job) {
			excuted = cur;
			task_do_excute_perop(i, cur);
			break;
		}

		list_for_each_entry_safe(cur, next, get_cpu_ready_queue(i), job) {
			//delete process
			if(cur->pc >= (cur->code_bytes / 2)) {
				// task deleted
				// remove from queue and ready to jump next process
				// (do swtich to jump)

				// if this task is last task of cpu0?
				// then just terminate excution and do not switch
				if(cur->pid == 100 && i == 0) {
					processors[i].state == CPU_IDLE;
					break;
				} else {
					task_ctxswtich(i, excuted, next);
				}
				list_del(&cur->job);
				processors[i].currunt_process_amount--;

				free(cur->code);
				free(cur);
			}
			break;
		}
	}
}

// lowest remaining target gets process.
// when processor is idling state, get more priority.
// if amount is same, give to cpu0.
bool task_can_be_allocated(int cpu_id) {
	int priority[processor_count];
	for(int i = 0; i < processor_count; i++) {
		priority[i] = ((processors[i].state == CPU_IDLE) ? 0 : processors[i].currunt_process_amount);
	}

	// if all priority value is  same, select 0. 
	bool all_equal = true;
	for(int i = 0; i < processor_count; i++) {
		if(priority[i] != priority[0]) all_equal = false;
	}
	if(all_equal) return (cpu_id == 0);

	int smallest_val = priority[0];
	int smallest_sel = 0;
	for(int i = 0; i < processor_count; i++) {
		if(priority[i] < smallest_val) {
			smallest_val = priority[i];
			smallest_sel = i;
		}
	}

	return (smallest_sel == cpu_id);
		
}

//arrival time순으로 allocate함 (FIFO)
void task_allocate_to_cpu() {
	//job is fully allocated, no more aloocateble job remains.

	for(int i = 0; i < processor_count; i++) {
		process *cur, *next;
		// no allocation in context switching state
		//if(processors[i].state == CPU_CTXSWITCH)
		//	continue;


		// fifo allocation
		list_for_each_entry_safe(cur, next, &job_queue, job) {
			// check queue is on a first allocation - they need to allocate a idle process in their tail.
			bool was_empty = list_empty(get_cpu_ready_queue(i));

			// check arrival time match and load balance priority
			// it have little bit of core check loop ignore issue (maybe bug) so task loses timing to get on a cpu. (해결할 자신 없음)
			if(*(&cur->arrival_time) <= processors[i].total_clock && task_can_be_allocated(i)) {
				printf("%04d CPU%d: Loaded PID: %03d\tArrival: %03d\tCodesize: %03d\n",
						processors[i].total_clock, CPU(i), cur->pid, cur->arrival_time, cur->code_bytes);
				list_move_tail(&cur->job, get_cpu_ready_queue(i));

				processors[i].currunt_process_amount++;
				processors[i].state = CPU_RUNNING;

				// they need to allocate a idle process in their tail. - check former step.
				if(was_empty)
					insert_idle_process(i);

				// check core is on the idle state - move idle process to tail and make it to ready state
				// and do switch!
				process *rc, *rn;
				list_for_each_entry_safe(rc, rn, get_cpu_ready_queue(i), job) {
					if(rc->pid == 100) {
						list_move_tail(&rc->job, get_cpu_ready_queue(i));
						task_ctxswtich(i, rc, cur);
					}
					break;
				}
				
				continue;
			} else {
				if(list_empty(get_cpu_ready_queue(i))) {
					insert_idle_process(i);
				} 
				continue;
			}

		}

		// idle process must be always sitting on end of queue.
		// if head(idle process) is not a only element of queue?
		// then move to tail (it has lowest priority)
		list_for_each_entry_safe(cur, next, get_cpu_ready_queue(i), job) {
			if(cur->pid == 100 && cur->job.next != get_cpu_ready_queue(i)) {
				list_move_tail(&cur->job, get_cpu_ready_queue(i));
				break;
			}
		}
	}
}

// check all cpu is falled into idle state
bool processor_all_jobless() {
	process *cur, *next;

	for(int i = 0; i < processor_count; i++) {
		list_for_each_entry_safe(cur, next, get_cpu_ready_queue(i), job) {
			if(cur->pid != 100 || !list_empty(&job_queue))
				return false;
		}
	}

	return true;
}

// calcuate all statics of excution result
void print_total_statics() {
	int cpu0_tclock = processors[0].total_clock;
	int cpu1_tclock = processors[1].total_clock;

	int cpu0_iclock = processors[0].idle_clock;
	int cpu1_iclock = processors[1].idle_clock;

	double cpu0util = ((double)(cpu0_tclock - cpu0_iclock) / cpu0_tclock) * 100;
	double cpu1util = ((double)(cpu1_tclock - cpu1_iclock) / cpu1_tclock) * 100;

	double totalutil = ((double)((cpu0_tclock + cpu1_tclock) - (cpu0_iclock + cpu1_iclock)) / (cpu0_tclock + cpu1_tclock)) * 100;
	
	printf("*** TOTAL CLOCKS: %04d CPU1 IDLE: %04d CPU2 IDLE: %04d CPU1 UTIL: %2.2f%% CPU2 UTIL: %2.2f%% TOTAL UTIL: %2.2f%%\n",
		  (cpu0_tclock), cpu0_iclock, cpu1_iclock, cpu0util, cpu1util, totalutil);
	
}

void processor_init() {
	processors = (cpu*)malloc(sizeof(cpu) * processor_count);

	process *p;
	code_tuple *c;

	for(int i = 0; i < processor_count; i++) {
		processors[i].processor_id = i;
		processors[i].total_clock = 0;
		processors[i].idle_clock = 0;
		processors[i].state = CPU_RUNNING;
		processors[i].currunt_process_amount = 0;
		processors[i].before_clk = 0;
	}
}

void processor_loop() {
	task_allocate_to_cpu();
	task_check_job_and_excute();

	while(1) {
		if(processor_all_jobless()) {
			print_total_statics();
			exit(0);
		}

		task_allocate_to_cpu();
		task_check_job_and_excute();
	}
}

int main() {
	read_and_register_tasks(); 
	processor_init();
	processor_loop();

    return 0;
}