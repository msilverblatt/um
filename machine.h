/*
 * machine.h
 * Names: Michael Silverblatt and Elliot Storey
 * Date: 4/2/13
 * HW 6: Universal Machine
 * Interface for UM opcodes
 */

#include "segment.h"
#include "struct.h"

inline uint32_t cond_move(uint32_t condition, uint32_t src, uint32_t dest);

inline uint32_t seg_load(Mem *memory, uint32_t identifier, uint32_t offset);

inline void seg_store(Mem *memory, uint32_t identifier, uint32_t offset,
               uint32_t src);
inline uint32_t add(uint32_t first, uint32_t second);

inline uint32_t mult(uint32_t first, uint32_t second);

inline uint32_t divide(uint32_t dividend, uint32_t divisor);

inline uint32_t bit_nand(uint32_t first, uint32_t second);

inline void halt();


inline uint32_t map_seg(Mem *memory,uint32_t num_words);

inline void unmap_seg(Mem *memory,  uint32_t segmentID);

inline uint32_t input();

inline void output(uint32_t value);

inline uint32_t load_prog(Mem *memory, uint32_t src,uint32_t counter);

uint32_t load_val(uint32_t value);
