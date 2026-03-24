#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

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

typedef struct {
    unsigned char op;
    unsigned char len;
} code_tuple;

typedef struct {
    int pid;
    int arrival_time;
    int code_bytes;

    code_tuple* code;
    struct list_head job, ready, wait;
} process;

int main() {
    process* p;
    process *cur, *next;
    
    LIST_HEAD(job_queue);

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

        INIT_LIST_HEAD(&p->job);
        list_add_tail(&p->job, &job_queue);
    }

    list_for_each_entry_reverse(cur, &job_queue, job) {
		int codelen = (cur->code_bytes / 2);
        printf("PID: %03d\tARRIVAL: %03d\tCODESIZE: %03d\n", cur->pid, cur->arrival_time, codelen * 2);

		code_tuple* tuple_cur = cur->code; 
		for(int i = 0; i < codelen; i++) 
			printf("%d %d\n", tuple_cur[i].op, tuple_cur[i].len);
    }

	list_for_each_entry_safe(cur, next, &job_queue, job) {
		free(cur->code);
		list_del(&cur->job);
		free(cur);
	}
	
    return 0;
}