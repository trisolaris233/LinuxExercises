#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

#define MAX_ALLOC_SIZE 1000000
#define BLOCK_SIZE 10240

struct mem_node {
    struct mem_node *prev;
    struct mem_node *next;
    size_t   size;
    void     *mem;
    short    is_freed;
};
struct mem_node heap_list = {
    NULL,
    NULL,
    0,
    NULL,
    -1
};
void *mymalloc(size_t mem_size);
void myfree(void* ptr);
void prt_heap_list(void);

int main(int argc, char **argv) {
    if (argc < 3 || 0 == strcmp("--help", argv[1]))
        usageErr("%s num-alloc blocksz [step [min [max]]]", argv[0]);

    int num_alloc, blocksz, stp, free_min, free_max, i;

    char *ptr[MAX_ALLOC_SIZE];
    num_alloc = getInt(argv[1], GN_ANY_BASE, argv[1]);
    blocksz = getInt(argv[2], GN_ANY_BASE, argv[2]);
    stp = (argc > 3) ? getInt(argv[3], GN_ANY_BASE, argv[3]) : 1;
    free_min = (argc > 4) ? getInt(argv[4], GN_ANY_BASE, argv[4]) : 0;
    free_max = (argc > 5) ? getInt(argv[5], GN_ANY_BASE, argv[5]) : num_alloc;

    char buffer[blocksz], buffer2[blocksz];
    for (i = 0; i < blocksz; ++i)
        buffer[i] = 'x';
    
    if (num_alloc > MAX_ALLOC_SIZE)
        cmdLineErr("num-alloc > %d", MAX_ALLOC_SIZE);

    printf("sizeof(heap_list) = %d\n", sizeof(heap_list));
    printf("allocating %d * %d bytes\n", num_alloc, blocksz);
    printf("initial break: %10p\n", sbrk(0));
    char *original_brk = sbrk(0);
    for (i = 0; i < num_alloc; ++i) {        
        ptr[i] = mymalloc(blocksz);
        if (NULL == ptr[i])
            errExit("mymalloc");
        // test writing the given memory
        // if no segmentation fault is thrown
        // at least, indicating no great error
        strncpy(ptr[i], buffer, blocksz);
        strncpy(buffer2, ptr[i], blocksz);

        // performing i/o
        int j;
        for (j = 0; j < blocksz; ++j)
            if (buffer2[j] != buffer[j])
                errExit("bad memory");
    }

    prt_heap_list();

    printf("after mymalloc() break: %10p\n", sbrk(0));
    printf("size allocated: %ld\n", (char*)sbrk(0) - original_brk);

    printf("\n\nfreeing [%d,%d) in stp of %d\n", free_min, free_max, stp);

    for (i = free_min; i < free_max; i += stp) {
        myfree(ptr[i]);
    }
    prt_heap_list();
    printf("after myfree() break: %10p\n", sbrk(0));
    

    
    exit(EXIT_SUCCESS);
}

void prt_heap_list(void) {
    struct mem_node *p;
    for (p = heap_list.next; p; p = p->next) {
        printf("(%d,%ld,%p)->",p->is_freed, p->size, p->mem);
    }
    printf("NULL\n");
}

void *mymalloc(size_t memsz) {
    struct mem_node *p;
    for (p = heap_list.next; NULL != p; p = p->next) {
        if (p->is_freed && p->size >= memsz) {
            p->is_freed = 0;
            return p->mem;
        }
    }

    struct mem_node *ptr = sbrk(sizeof(heap_list));
    if (NULL == ptr)
        return NULL;

    ptr->mem = sbrk(memsz);
    if (NULL == ptr->mem)
        return NULL;
    ptr->size = memsz;
    ptr->is_freed = 0;

    if (NULL == heap_list.next) {
        heap_list.next = ptr;
        ptr->prev = &heap_list;
        ptr->next = NULL;
    } else {
        for (p = heap_list.next; p->next; p = p->next);
        p->next = ptr;
        ptr->prev = p;
    }
    return ptr->mem;
}

void myfree(void *ptr) {
    // find the tail
    struct mem_node *p;
    for(p = heap_list.next; p->next; p = p->next)
        if (p->mem == ptr) 
            p->is_freed = 1;
    if (p->mem == ptr)
        p->is_freed = 1;

    struct mem_node *tail = p;
    size_t free_space = 0;
    for(p = tail; p->prev != NULL; p = p->prev) {
        if (!(p->is_freed))
            break;
        else
            free_space += (sizeof(heap_list) + p->size);
    }
    
    if (free_space >= BLOCK_SIZE) {
        p->next = NULL;
        sbrk(-free_space);
        return;
    }
}