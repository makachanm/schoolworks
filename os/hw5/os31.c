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
    //printf("Virtual Page Table Initing... PID %d / REFLEN %d\n", p->p.pid, p->p.ref_len);

    p->virtual_page_area = (pte *)calloc(VAS_PAGES, sizeof(pte));
    for(int i = 0; i < VAS_PAGES; i++) {
        p->virtual_page_area[i].frame = 0;
        p->virtual_page_area[i].vflag = PAGE_INVALID;
        p->virtual_page_area[i].ref = 0;
        p->virtual_page_area[i].pad = 0;

    }
}

void init_pframe_area() {
    physical_frame = (frame *)calloc(PAS_FRAMES, sizeof(frame));
    
    for(int i = 0; i < PAS_FRAMES; i++) {
        physical_frame[i].b = (unsigned char*)calloc(1, PAGESIZE);
        physical_frame[i].allocated = PAGE_INVALID;
    }

    int vpt_needed_frame = ((PAGETABLE_FRAMES) * process_count);
    for(int i = 0; i < vpt_needed_frame; i++)
        physical_frame[i].allocated = PAGE_VALID;

    printf("NEEDED: %d\n", vpt_needed_frame);

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
    //do allocation job
    //printf("Page Fault in PID %d Page %d\n", p->p.pid, num);

    for(int i = 0; i < PAS_FRAMES; i++) {
        if(physical_frame[i].allocated == PAGE_INVALID) {
            physical_frame[i].allocated = PAGE_VALID;

            p->faults++;
            p->refs++;
            p->frames++;

            p->virtual_page_area[num].vflag = PAGE_VALID;
            p->virtual_page_area[num].ref++;
            p->virtual_page_area[num].frame = i;
            p->virtual_page_area[num].pad = 0;

            //printf("PID %d: Frame %d is allocated to Page %d\n", p->p.pid, i, num);
            return;
        }
    }

    is_oom = true;
}

void allocate_ref_page(int num, process_pinfo* p) {
    //printf("Valid page %d access in PID %d\n", num, p->p.pid);
    p->virtual_page_area[num].ref++;
    p->refs++;
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

        printf("PAS_FRAMES = %d\n", PAS_FRAMES);
        printf("VAS_FRAMES = %d\n", VAS_PAGES);

    for(int  i = 0; i < PAS_FRAMES; i++) {
        printf("%d ", physical_frame[i].allocated);
    }
    printf("\n");

    int total_frame = 0;
    int total_faults = 0;
    int total_refs = 0;

    printf("%d %d\n", PAGE_INVALID, PAGE_VALID);

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
            } else {
                printf("VFLAG: %d\n", processes[i].virtual_page_area[j].vflag);
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