#ifndef CAT_H
#define CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Keys {
  int flag_E;
  int flag_v;
  int flag_b;
  int flag_n;
  int flag_T;
  int flag_s;
  int line_number;
  int file_counter;
  int empty_line;
  int* file_ind;
};

int get_args(int, char**, struct Keys*);
void loop_files(char**, struct Keys*);
void put_cat_char(char*, char*, struct Keys*);
int get_m_notation(char*);

#endif