/*
 * machine.c
 * Names: Michael Silverblatt and Elliot Storey
 * Date: 4/2/13
 * HW 6: Universal Machine
 * Implementation of UM opcode interface
 */

#include "machine.h"
#include "bitpack.h"

inline uint32_t cond_move(uint32_t condition, uint32_t src, uint32_t dest)
{
        if (condition != 0){
                return src;
        }
	else return dest;
}	

inline uint32_t seg_load(Mem *memory, uint32_t identifier, uint32_t offset)
{
         return get(memory, identifier, offset);
}

inline void seg_store(Mem *memory, uint32_t identifier, uint32_t offset, 
                      uint32_t src)
{
        put(memory, identifier, offset, src);
}

inline uint32_t add(uint32_t first, uint32_t second)
{
 	return first + second; 
}

inline uint32_t mult(uint32_t first, uint32_t second)
{
    return first * second;
}

inline uint32_t divide(uint32_t dividend, uint32_t divisor)
{
	return dividend / divisor;
}

inline uint32_t bit_nand(uint32_t first, uint32_t second)
{
	return ~(first & second);
}

inline void halt(Mem *memory)
{/*
        uint32_t * temp;
        while (Seq_length(memory) > 0){
                temp = Seq_remhi(memory);
                if (temp != NULL){
                        free(temp);
                }
        }
        while (Seq_length(seg_lengths) > 0){
                temp = Seq_remhi(seg_lengths);
                if (temp != NULL){
                        free(temp);
                }
        }
        while (Seq_length(unmapped_IDs) > 0){
            temp = Seq_remhi(unmapped_IDs);
            if (temp != NULL){
                    free(temp);
            }
        }
 */
    // free(ID_counter);
        Node *temp;
        while (memory->unmapped != NULL){
	        temp = memory->unmapped;
	        memory->unmapped = memory->unmapped->next;
                free(temp);        
	}
        for (unsigned int i = 0; i < memory->ID_counter; i++){
	         if (memory->arr[i].len != 0){
	    		        free(memory->arr[i].arr);
	    	}
	    // free(&(memory->arr[i]));
	}
//	free(memory->arr);
	free(memory);	
//   Seq_free(&memory);
	//      Seq_free(&unmapped_IDs);
        exit(0);
}

inline uint32_t map_seg(Mem *memory, uint32_t num_words)
{
        return map_segment(memory, num_words);
}

inline void unmap_seg(Mem *memory, uint32_t segmentID)
{
        unmap_segment(memory, segmentID);
}

inline uint32_t input()
{
        int input = getc(stdin);
     	return input;
}

inline void output(uint32_t value)
{
        printf("%c", (char)value);
}

inline uint32_t load_prog(Mem *memory, uint32_t src, uint32_t counter)
{
//        registers[8] = registers[counter];
        if (src == 0){
                return counter;
        }
        else {
                unmap_zero(memory);
                map_zero(memory, src);
        }
	return counter;
}

uint32_t load_val(uint32_t value)
{
//        registers[dest] = value;
    return value;
}
