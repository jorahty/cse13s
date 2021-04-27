#ifndef __MORE_H__
#define __MORE_H__

#include <stdint.h>
#include <stdbool.h>

void printGuideAndExit();

extern uint32_t moves;
extern uint32_t comparisons;

// Taken from Lecture 8
void swap(uint32_t *one, uint32_t *two);

// Taken from Eugene
bool less_than(int64_t first, int64_t second);

#endif
