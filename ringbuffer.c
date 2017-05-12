#include "stdio.h"
#include "ringbuffer.h"
int main(void)
{
    printf("Hello\n");
    int buff[6]={0};
    circular_buffer rb;
    printf("Start Address of mem: %p\n",(void *)buff);
    int j=0;
    for (j=0;j<6;j++) {
        printf("Address of buff[%d] is %p; trying to add %p\n",j,(void *) &buff[j],(void *)buff+j*sizeof(int));
    }
    cb_init(&rb, buff, 6, sizeof(int));
    while (1) {
        printf("[p]ush [r]emove\n");
        char c;
        scanf("%c",&c);
        if (c=='p') {
            printf("number: \n");
            int i;
            scanf("%d",&i);
            cb_push_back(&rb,&i);
        }
        if (c=='r') {
            int i;
            cb_pop_front(&rb,&i);
            printf("Pop: %d\n",i);
        }
    }
    return 0;
}



void cb_init(circular_buffer *cb, int *mem, int capacity, size_t sz)
{
    cb->buffer = mem;
    cb->capacity = (capacity-1);
    cb->buffer_end = mem + (capacity-1); 
    cb->count = 0;
    cb->sz = sz;
    cb->head = cb->buffer;
    cb->tail = cb->buffer;
    cb->isEmpty=1;
    cb->isFull=0;
    printf("Ring Buffer Start: %p End: %p\n", (void *)cb->buffer, (void *)cb->buffer_end);
    printf("Ring Buffer Capacity: %zu size: %zu and result: %p difference: %p \n", cb->capacity, cb->sz, (void *) cb->buffer_end, (void *)(cb->buffer_end - cb->buffer)); 
}

void cb_push_back(circular_buffer *cb, int *item)
{
    printf("Ring Buffer Head: %p Tail: %p, Difference: %ld\n", (void *)cb->head, (void *)cb->tail, cb->head-cb->tail); 
    if (cb->isFull==1) {
        printf("Memory Full\n");
        int i;
        cb_pop_front(cb,&i);
    }
    if ((cb->head - cb->tail == cb->capacity) || (cb->head - cb->tail == -1 )) {
        cb->isFull=1;
        cb->isEmpty=0;
        // handle error
    }
    memcpy(cb->head, item, cb->sz);
    if(cb->head == cb->buffer_end)
        cb->head = cb->buffer;
    else
        cb->head = cb->head + 1;
    printf("Pushed: %d at count: %d\n", *item, (int) cb->count);
    cb->count++;
    cb->isEmpty=0;
    
    
}

void cb_pop_front(circular_buffer *cb, int *item)
{
    printf("Ring Buffer Head: %p Tail: %p\n", (void *)cb->head, (void *)cb->tail);
    if (cb->head == cb->tail && cb->isFull!=1) {
        cb->isEmpty=1;
        *item=0;
        printf("Empty Buffer\n");
        return;
        // handle error
    }
    memcpy(item, cb->tail, cb->sz);
    if(cb->tail == cb->buffer_end)
        cb->tail = cb->buffer;
    else
        cb->tail = cb->tail + 1;
    printf("Poped: %d from count: %d\n",*item,(int) cb->count);
    cb->count--;
    cb->isFull=0;
    
}
