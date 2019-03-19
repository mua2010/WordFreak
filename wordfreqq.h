#ifndef _WORD_FREQ_H
#define _WORD_FREQ_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define max_size 100
#define flag_fd 5

//A struct word is a node of the linked list of words
struct Word
{
   char *word; //a word
   int frequency;
   struct Word *next; //link to the next word in the linked list
};
typedef struct Word Word;

Word *search(Word *wl, char *wordStr);

Word *makeNode(char *word);

void addWord(Word *head, char *word);

void free_node(Word *w);

void free_list(Word *w);

void wordFreq(Word *wl, char *filename, int fd1);

#endif