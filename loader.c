/*
 * loader.c
 * Names: Michael Silverblatt and Elliot Storey
 * Date: 4/2/13
 * HW 6: Universal Machine
 * Implementation of program loader interface
 */

#include "machine.h"
#include "bitpack.h"
//#include "struct.h"

int read_file (FILE *fp, Mem *memory);
void read_word (uint32_t registers[], Mem *memory);


int main (int argc, char *argv[])
{
        (void) argc;
        uint32_t registers[9];
	Mem *memory = malloc(sizeof(*memory));
	memory->len = 2 << 20;
	memory->arr = calloc(memory->len,sizeof(*memory));
        memory->unmapped = NULL;
        memory->ID_counter = 1;
        FILE *fp = fopen (argv[1], "rb");
        read_file (fp, memory);
        fclose(fp);
        for (int i = 0; i < 9; i++){
                registers[i] = 0;
        }
        while(1){
                read_word (registers, memory);
        }
}

int read_file (FILE *fp, Mem *memory)
{
        fseek (fp, 0, SEEK_END);
        int num_words = ftell(fp) / 4;
        rewind (fp);
        uint32_t word = 0;
        int c;
        uint32_t *temp;
        temp = malloc(sizeof(uint32_t)*num_words);
        for (int i = 0; i < num_words; i++){
                c = getc(fp);
                word = (uint32_t) c;
                for (int j = 0; j < 3; j++){
                        c = getc(fp);
                        word = word << 8;
                        word += (uint32_t) c;
                }
                temp[i] = word;
        }
	memory->arr[0].arr = temp;
	memory->arr[0].len = num_words;
	return num_words;
}
    

void read_word (uint32_t registers[], Mem *memory)
{ 
        uint32_t instruction = memory->arr[0].arr[registers[8]];
        int opcode = instruction >> 28;
        int a,b,c;
        uint32_t value;
        a = 0;
        b = 0;
        c = 0;
        value = 0;
        if (opcode < 13){
	    c = (instruction & 7);
		if (opcode < 7){
		    a = ((instruction & 448) >> 6);
		    b = ((instruction & 56) >> 3);                      
		}
                else if ((opcode == 8) || (opcode == 12)){
		    b = ((instruction & 56) >> 3); 
		}
                        switch (opcode) {
                                case 0: 
		                        registers[a] = cond_move(registers[c], 
                                                                 registers[b], 
                                                                 registers[a]);
                                        break;
                                case 1: 
                                        registers[a] = seg_load (memory,
                                                                 registers[b], 
                                                                 registers[c]);
                                        break;
                                case 2: 
                                        seg_store (memory, 
                                                   registers[a], 
                                                   registers[b], 
                                                   registers[c]);
                                        break;
                                case 3:
                                        registers[a] = add(registers[b],
                                                           registers[c]);
                                        break;
            			case 4:
        		                registers[a] = mult(registers[b],
                                                            registers[c]);
   		                        break;
   		                case 5:
    		                        registers[a] = divide(registers[b], 
                                                       registers[c]);
	                                break;
 		                case 6:
        	                        registers[a] = bit_nand(registers[b], 
                                                                registers[c]);
                       		        break;
 		                case 7:
                                        halt(memory);
                                        break;
                                case 8:
 	                                registers[b] = map_seg(memory, 
                                                               registers[c]);
                                        break;
                                case 9:
		                        unmap_seg (memory, registers[c]);
                                        break;
                                case 10:
                                        output(registers[c]);
                                        break;
                                case 11:
                                        registers[c] = input();
                                        break;
                                case 12:
                                        registers[8] = load_prog(memory,
                                                                 registers[b], 
                                                                 registers[c]);
                                        break;
                       }
        }
        else {
       	        a = (instruction & 234881024) >> 25;
                value = (uint32_t)((instruction << 7) >> 7);
                registers[a] = load_val (value);
        }

        if (opcode != 12) registers[8]++;
}
