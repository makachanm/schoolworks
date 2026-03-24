#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int PAGESIZE, PAS_FRAMES, VAS_PAGES;

#define PAS_SIZE (PAGESIZE*PAS_FRAMES) //test3.bin : 32*256 = 8192 B
#define VAS_SIZE (PAGESIZE*VAS_PAGES) // test3.bin : 32*64 = 2048 B
#define PTE_SIZE (4) //sizeof(pte)
// test3.bin : 64*4/32 = 8 consecutive frames
#define PAGETABLE_FRAMES (VAS_PAGES*PTE_SIZE/PAGESIZE)
#define PAGE_INVALID (0)
#define PAGE_VALID (1)
#define MAX_REFERENCES (256)

#define PTE_PER_PAGE (PAGESIZE / PTE_SIZE)

typedef struct{
    unsigned char frame; //allocated frame
    unsigned char vflag; //valid-invalid bit
    unsigned char ref; //reference bit
    unsigned char pad; //padding
} pte; // Page Table Entry (total 4 Bytes, always)

typedef struct{
    int pid;
    int ref_len; //Less than 255
    unsigned char *references;
} process_raw;
    
typedef struct {
    int faults;
    int refs;
    int frames;
    int pc;

    process_raw p;
    pte* virtual_page_area;
} process_pinfo;

typedef struct {
    //b[PAGESIZE]
    unsigned char* b;
    unsigned char allocated;
} frame;

int process_count = 0;
process_pinfo* processes;
frame* physical_frame;

pte* lv1_virtual_space;

bool is_oom = false;

void read_sysinfo() { 
    fread(&PAGESIZE, 4, 1, stdin);
    fread(&PAS_FRAMES, 4, 1, stdin);
    fread(&VAS_PAGES, 4, 1, stdin);
    //printf("System Info Readed!\n");    
}

void read_process() { 
    while(1) {
        if(!fread(&processes[process_count].p, 8, 1, stdin)) {
            break;
        }

        int p_pagesize = processes[process_count].p.ref_len;
        processes[process_count].p.references = (unsigned char *)calloc(p_pagesize, sizeof(unsigned char));

        for(int i = 0; i < p_pagesize; i++) {
        	fread(&processes[process_count].p.references[i], 1, 1, stdin);
    	}

        processes[process_count].faults = 0;
        processes[process_count].refs = 0;
        processes[process_count].frames = PAGETABLE_FRAMES;

        init_vpage_area(&processes[process_count]);

        process_count++;
    }

    //printf("Process Read Complete!\n");
}

void init_vpage_area(process_pinfo* p) { 
    //allocate lv2 area
    //printf("Virtual Page Table Initing... PID %d / REFLEN %d\n", p->p.pid, p->p.ref_len);
    p->virtual_page_area = (pte*)calloc(1, sizeof(pte));
    p->virtual_page_area[i].frame = 0;
    p->virtual_page_area[i].vflag = PAGE_INVALID;
    p->virtual_page_area[i].ref = 0;
    p->virtual_page_area[i].pad = 0;
}

void init_lv1vpage_area() {
    //allocate actual LV1 area

    lv1_virtual_space = (pte*)calloc(PTE_PER_PAGE, sizeof(pte));
    for(int i = 0; i < PTE_PER_PAGE; i++) {
        lv1_virtual_space.frame = 0;
        lv1_virtual_space.vflag = PAGE_INVALID;
        lv1_virtual_space.ref = 0;
        lv1_virtual_space.pad = 0;
    }
}

void init_pframe_area() {
    physical_frame = (frame *)calloc(PAS_FRAMES, sizeof(frame));
    
    for(int i = 0; i < PAS_FRAMES; i++) {
        physical_frame[i].b = (unsigned char*)calloc(1, PAGESIZE);
        physical_frame[i].allocated = PAGE_INVALID;
    }

    //allocate LV1 Page Tables;
    physical_frame[0].allocated = PAGE_VALID;
    //int vpt_needed_frame = (process_count);
    //for(int i = 0; i < vpt_needed_frame; i++)
    //   physical_frame[i].allocated = PAGE_VALID;

    //printf("Physical Frame Inited!\n");
}

bool okay_to_break() {
    if(is_oom) return true;

    for(int i = 0; i < process_count; i++)
        if(processes[i].pc < processes[i].p.ref_len) return false;

    return true;
}

void do_process_work() {
    //printf("Process Excution Started!\n");
    while(1) {
        if(okay_to_break()) break;

        for(int i = 0; i < process_count; i++) {
            if(processes[i].pc >= processes[i].p.ref_len) continue;
            //printf("PID %d is Accessing Page %d, PC %d\n", processes[i].p.pid, (int)processes[i].p.references[processes[i].pc], processes[i].pc);
            allocate_page((int)processes[i].p.references[processes[i].pc], &processes[i]);
            processes[i].pc++;
        }
    }

    exit_all();
}

void allocate_page(int page_num, process_pinfo* p) {
    if(p->virtual_page_area[page_num].vflag == PAGE_VALID) {
        allocate_ref_page(page_num, p);
        
    } else {
        allocate_faulted_page(page_num, p);
    }

}

void allocate_faulted_page(int num, process_pinfo* p) {
    //do allocation job - lv2 (process & toss to LV1)
    //printf("Page Fault in PID %d Page %d\n", p->p.pid, num);
    allocate_faluted_lv1_page(num);    
    realloc(p->virtual_page_area, sizeof(pte)*(p.faults + 1));

    for(int i = 0; i < PTE_PER_PAGE; i++) {
        if(physical_frame[i].allocated == PAGE_INVALID) {
            physical_frame[i].allocated = PAGE_VALID;

            p->virtual_page_area[p.faults - 1].frame = i;
            p->virtual_page_area[p.faults - 1].vflag = PAGE_VALID;
            p->virtual_page_area[p.faults - 1].ref = 1;
            p->virtual_page_area[p.faults - 1].pad = 0;

            break;
        }
    }

    
}

void allocate_faluted_lv1_page(int num) {
    int target = num / PTE_PER_PAGE;

    if(lv1_virtual_space[target] == PAGE_VALID) return;

    for(int i = 0; i < PTE_PER_PAGE; i++) {
        if(physical_frame[i].allocated == PAGE_INVALID) {
            physical_frame[i].allocated = PAGE_VALID;

            lv1_virtual_space[target].vflag = PAGE_VALID;
            lv1_virtual_space[target].ref++;
            lv1_virtual_space[target].frame = i;
            lv1_virtual_space[target].pad = 0;

            //printf("PID %d: Frame %d is allocated to Page %d\n", p->p.pid, i, num);
            return;
        }
    }

    is_oom = true;
}

//TODO: REWRITE AS TWO_STEP
void allocate_ref_page(int num, process_pinfo* p) {
    //printf("Valid page %d access in PID %d\n", num, p->p.pid);
    allocate_ref_lv1_page(num);
    p->virtual_page_area[num].ref++;
    p->refs++;
}

void allocate_ref_lv1_page(int num) {
    int target = num / PTE_PER_PAGE;
    lv1_virtual_space[target].ref++;
}

void revoke_all_resource() {
    for(int i = 0; i < process_count; i++) {
        free(processes[i].virtual_page_area);
    }
    free(physical_frame);
}  

void print_statics() {
    if(is_oom)
        printf("Out of memory!!\n");


    int total_frame = 0;
    int total_faults = 0;
    int total_refs = 0;

    for(int i = 0; i < process_count; i++) {
        int pid = processes[i].p.pid;
        int faults = processes[i].faults;
        int reference_num = processes[i].refs;
        int allocated = processes[i].frames;

        total_frame += allocated;
        total_faults += faults;
        total_refs += reference_num;

        printf("** Process %03d: Allocated Frames=%03d PageFaults/References=%03d/%03d\n", pid, allocated, faults, reference_num);

        for(int j = 0; j < VAS_PAGES; j++) {
            if(processes[i].virtual_page_area[j].vflag == PAGE_VALID) {
                printf("%03d -> %03d REF=%03d\n", j, processes[i].virtual_page_area[j].frame, processes[i].virtual_page_area[j].ref);
            }
        }
    }

    printf("Total: Allocated Frames=%03d Page Faults/References=%03d/%03d\n", total_frame, total_faults, total_refs);
}

void exit_all() {
    print_statics();
    revoke_all_resource();
    exit(0);
    //print status
}

int main() {
    processes = (process_pinfo*)calloc(10, sizeof(process_pinfo));

    read_sysinfo();
    read_process();
    init_pframe_area();
    do_process_work();
    return 0;
}