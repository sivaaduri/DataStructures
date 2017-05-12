typedef struct circular_buffer
{
    int *buffer;     // data buffer
    int *buffer_end; // end of data buffer
    size_t capacity;  // maximum number of items in the buffer
    size_t count;     // number of items in the buffer
    size_t sz;        // size of each item in the buffer
    int *head;       // pointer to head
    int *tail;       // pointer to tail
    int isFull;      //bool
    int isEmpty;     //bool 
} circular_buffer;

void cb_init(circular_buffer *cb, int *mem, int capacity, size_t sz);

void cb_push_back(circular_buffer *cb, int *item);

void cb_pop_front(circular_buffer *cb, int *item);
