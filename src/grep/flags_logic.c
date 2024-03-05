#include "grep.h"

void file_flags_logic(const struct Keys* keys, const char* f_name) {
  if (!keys->flag_h && keys->flag_c && !keys->flag_l && keys->pattern_exist) {
    if (keys->write_to_file) {
      printf("%s:", f_name);
      printf("%d\n", keys->matched_counter);
    } else {
      printf("\033[0;35m%s\033[m:", f_name);
      printf("%d\n", keys->matched_counter);
    }
  } else if (keys->flag_h && keys->flag_c && !keys->flag_l &&
             keys->pattern_exist) {
    printf("%d\n", keys->matched_counter);
  } else if (keys->flag_l && keys->matched_counter) {
    if (keys->write_to_file) {
      printf("%s\n", f_name);
    } else {
      printf("\033[0;35m%s\033[m\n", f_name);
    }
  }
}

void main_flags_logic(struct Keys* keys, const char* f_name, char* line,
                      const int* color_s) {
  if (keys->has_match && !keys->flag_v && !keys->flag_o && !keys->flag_c &&
      !keys->flag_l) {
    if (!keys->flag_h) {
      if (keys->write_to_file) printf("%s:", f_name);
      if (!keys->write_to_file) printf("\033[0;35m%s\033[m:", f_name);
    }
    if (keys->flag_n) {
      printf("%d:", keys->line_number);
    }
    show_line_by_chars(line, color_s, keys);
  } else if (!keys->has_match && keys->flag_v && !keys->flag_c &&
             !keys->flag_o && !keys->flag_l) {
    if (!keys->flag_h) {
      if (keys->write_to_file) printf("%s:", f_name);
      if (!keys->write_to_file) printf("\033[0;35m%s\033[m:", f_name);
    }
    if (keys->flag_n) {
      printf("%d:", keys->line_number);
    }
    show_line_by_chars(line, color_s, keys);
  } else if (keys->has_match && !keys->flag_v) {
    keys->matched_counter++;
  } else if (!keys->has_match && keys->flag_v) {
    keys->matched_counter++;
  }
}

void flag_o_logic(const struct Keys* keys, char* tmp_line, const char* f_name) {
  if (keys->flag_o && !keys->flag_c && !keys->flag_v && !keys->flag_l &&
      tmp_line[0] != '\n') {
    if (tmp_line[strlen(tmp_line) - 1] == '\n') {
      tmp_line[strlen(tmp_line) - 1] = '\0';
    }
    if (!keys->flag_h) {
      if (keys->write_to_file) printf("%s:", f_name);
      if (!keys->write_to_file) printf("\033[0;35m%s\033[m:", f_name);
    }
    if (keys->flag_n) {
      printf("%d:", keys->line_number);
    }
    if (!keys->write_to_file) printf("\033[1;31m");
    printf("%.*s\n", keys->pattern_len, tmp_line);
    if (!keys->write_to_file) printf("\033[m");
  }
}