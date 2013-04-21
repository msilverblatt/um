/*
 * segment.h
 * Names: Michael Silverblatt and Elliot Storey
 * Date: 4/2/13
 * HW 6: Universal Machine
 * Interface for segmented memory
 */


#include <seq.h>
#include <table.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "assert.h"
#include "struct.h"

Seq_T segment_new(int hint);
uint32_t next_segmentID(Mem *memory);
uint32_t map_segment(Mem *memory,  uint32_t num_words);
void unmap_segment(Mem *memory, uint32_t segmentID);
inline void put(Mem *memory, uint32_t segmentID, uint32_t offset, 
                uint32_t value);
inline uint32_t get(Mem *memory, uint32_t segmentID, uint32_t offset);
void map_zero(Mem *memory, uint32_t segmentID);
void unmap_zero(Mem *memory);
