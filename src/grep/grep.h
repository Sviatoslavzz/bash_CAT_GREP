#ifndef GREP_H
#define GREP_H

#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Keys {
  short int flag_i;
  short int flag_v;
  short int flag_c;
  short int flag_l;
  short int flag_n;
  short int flag_h;
  short int flag_s;
  short int flag_o;
  short int matched_counter;
  short int line_number;
  short int matched;
  int closest_position;
  short int pattern_len;
  short int pattern_exist;
  short int f_start_index;
  int* p_argc;
  char** p_argv;
  short int write_to_file;
  short int error;
  short int has_match;
  short int e_f_exist;
};

void show_usage_man(const char*);
void get_options(struct Keys*);
void read_stdin_line(struct Keys*);
void read_files(struct Keys*);
void read_file_lines(FILE**, struct Keys*, const char*);
void file_flags_logic(const struct Keys*, const char*);
void compare_line(char*, struct Keys*, const char*);
void main_flags_logic(struct Keys*, const char*, char*, const int*);
void flag_o_logic(const struct Keys*, char*, const char*);
void get_patterns_from_file(const char*, char*, struct Keys*);
void regex_line(char*, char*, struct Keys*);
void show_line_by_chars(char*, const int*, const struct Keys*);
int check_emptiness(struct Keys*, const char*);

#endif