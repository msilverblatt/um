#ifndef UM_STRUCT_INCLUDED
#define UM_STRUCT_INCLUDED

struct Node{
    struct Node *next;
    uint32_t val;
};

typedef struct Node Node;

typedef struct {
    uint32_t *arr;
    uint32_t len;
} Seg;

typedef struct {
    Seg *arr;
    uint32_t len;
    Node *unmapped;
    uint32_t ID_counter;
} Mem;


#endif
