/*
 * segment.c
 * Names: Michael Silverblatt and Elliot Storey
 * Date: 4/2/13
 * HW 6: Universal Machine
 * Implementation of segmented memory interface
 */
#include <string.h>
#include "segment.h"
#include "assert.h"


Seq_T segment_new(int hint)
{
        Seq_T result = Seq_new(hint);
        return result;
}

uint32_t next_segmentID(Mem *memory)
{
        if (!memory->unmapped){
	    memory->ID_counter++;
	    return memory->ID_counter - 1;
	}
        else {
            uint32_t result = memory->unmapped->val;
            Node *temp = memory->unmapped;
            memory->unmapped=memory->unmapped->next;
            free(temp);
            return result;
	}
}

uint32_t map_segment(Mem *memory,  uint32_t num_words)
{
        int seg_id = next_segmentID(memory);
	if ((uint32_t) seg_id >= (memory->len)){
	    memory->len = memory->len << 2;
	    memory->arr = realloc(memory->arr,memory->len*sizeof(Seg));
	}
	memory->arr[seg_id].len = num_words;
        uint32_t *arr;
        arr = calloc(num_words,sizeof(uint32_t));
	memory->arr[seg_id].arr = arr;
        return seg_id;
}

void unmap_segment(Mem *memory, uint32_t segmentID)
{
        Node *new = malloc(sizeof(*new));
        new->next = memory->unmapped;
        new->val = segmentID;
        memory->unmapped = new;
	free(memory->arr[segmentID].arr);
	memory->arr[segmentID].len = 0;        
}

inline void put(Mem *memory, uint32_t segmentID, uint32_t offset, 
                uint32_t value)
{
    memory->arr[segmentID].arr[offset] = value;
}

inline uint32_t get(Mem *memory, uint32_t segmentID, uint32_t offset)
{
    return memory->arr[segmentID].arr[offset];
}

void map_zero(Mem *memory, uint32_t segmentID)
{
        memory->arr[0].arr = realloc(memory->arr[0].arr, 
                             memory->arr[segmentID].len*sizeof(uint32_t));
	memcpy(memory->arr[0].arr, memory->arr[segmentID].arr, 
               sizeof(uint32_t)*memory->arr[segmentID].len);
	memory->arr[0].len = memory->arr[segmentID].len;
}

void unmap_zero(Mem *memory)
{
        Seg temp = memory->arr[0];
        if (temp.arr != NULL){
                temp.len = 0;
		//               free(&(memory->arr[0]));
        }
}
