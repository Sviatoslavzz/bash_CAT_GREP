#include "grep.h"

int main(int argc, char* argv[]) {
  if (argc == 1) {
    show_usage_man(argv[0]);
  } else {
    struct Keys keys = {0, 0, 0, 0, 0,     0,    0, 0, 0, 1, 0,
                        0, 0, 0, 0, &argc, argv, 0, 0, 0, 0};

    get_options(&keys);

    if (!keys.error) {
      if (!isatty(fileno(stdout))) {
        keys.write_to_file = 1;
      }
      read_files(&keys);
    }
  }

  return 0;
}

void show_usage_man(const char* name) {
  printf("Usage: %s [OPTION]... PATTERNS [FILE]...", name + 2);
  printf("\n-i: --ignore-case");
  printf("\n-v: --invert-match");
  printf("\n-c: --count");
  printf("\n-l: --files-with-matches");
  printf("\n-n: --line-number");
  printf("\n-h: --no-filename");
  printf("\n-s: --no-messages");
  printf("\n-o: --only-matching");
  printf("\n-: read stdin file stream\n");
}

void get_options(struct Keys* keys) {
  int opt;
  while ((opt = getopt_long(*keys->p_argc, keys->p_argv, "ivclnhsoe:f:", NULL,
                            NULL)) != -1) {
    if (opt == 'i') {
      keys->flag_i = 1;
    } else if (opt == 'v') {
      keys->flag_v = 1;
    } else if (opt == 'c') {
      keys->flag_c = 1;
    } else if (opt == 'l') {
      keys->flag_l = 1;
    } else if (opt == 'n') {
      keys->flag_n = 1;
    } else if (opt == 'h') {
      keys->flag_h = 1;
    } else if (opt == 's') {
      keys->flag_s = 1;
    } else if (opt == 'o') {
      keys->flag_o = 1;
    } else if (opt == 'e') {
      keys->pattern_exist = 1;
      keys->e_f_exist = 1;
    } else if (opt == 'f') {
      keys->e_f_exist = 1;
      if (!check_emptiness(keys, optarg)) {
        keys->error++;
        printf("%s: %s: No such file or directory\n", keys->p_argv[0] + 2,
               optarg);
      }
    } else {
      keys->error++;
    }
    if (keys->error) break;
  }
  if (!keys->e_f_exist) {
    keys->f_start_index = optind + 1;
    keys->pattern_exist = 1;
  } else {
    keys->f_start_index = optind;
  }
  if (keys->f_start_index == *keys->p_argc - 1) {
    keys->flag_h = 1;
  }
}

int check_emptiness(struct Keys* keys, const char* file_name) {
  int checker = 0;
  FILE* file = fopen(file_name, "r");
  if (file) {
    checker++;
    fseek(file, 0, SEEK_END);
    int pos = ftell(file);
    if (pos > 0) {
      keys->pattern_exist = 1;
    }
    rewind(file);
    fclose(file);
  }
  return checker;
}

void read_files(struct Keys* keys) {
  for (int i = keys->f_start_index; i < *keys->p_argc; i++) {
    if (strcmp(keys->p_argv[i], "-") == 0) {
      read_stdin_line(keys);
    } else {
      FILE* file = fopen(keys->p_argv[i], "r");
      if (file) {
        read_file_lines(&file, keys, keys->p_argv[i]);
        fclose(file);
      } else if (!keys->flag_s) {
        printf("%s: %s: No such file or directory\n", keys->p_argv[0] + 2,
               keys->p_argv[i]);
      }
      if (keys->error) break;
    }
  }
}

void read_stdin_line(struct Keys* keys) {
  keys->line_number = 1;
  keys->matched_counter = 0;
  char* str = NULL;
  str = malloc(sizeof(char));
  if (!str) {
    keys->error = 1;
  } else {
    char ch;
    str[0] = '\0';
    int counter = 0;
    while ((ch = fgetc(stdin)) != EOF) {
      counter++;
      char* tmp = realloc(str, (counter + 1) * sizeof(char));
      if (!tmp) {
        keys->error = 1;
        break;
      } else {
        str = tmp;
        str[counter - 1] = ch;
        str[counter] = '\0';
        if (ch == '\n') {
          compare_line(str, keys, "stdin");
          keys->line_number++;
          counter = 0;
        }
      }
    }
    free(str);
    fseek(stdin, 0, SEEK_END);
  }
  if (keys->error == 1) {
    printf("Memory allocation error: function <read_stdin_line>\n");
  } else if (!keys->error) {
    file_flags_logic(keys, "stdin");
  }
}

void read_file_lines(FILE** file, struct Keys* keys, const char* f_name) {
  keys->line_number = 1;
  keys->matched_counter = 0;
  char* str = NULL;
  str = malloc(sizeof(char));
  if (!str) {
    keys->error = 1;
  } else {
    int counter = 0;
    while (!feof(*file)) {
      counter++;
      short int ch = fgetc(*file);
      char* tmp = realloc(str, (counter + 1) * sizeof(char));
      if (!tmp) {
        keys->error = 1;
        break;
      } else {
        str = tmp;
        str[counter - 1] = ch;
        str[counter] = '\0';
        if (ch == '\n') {
          counter = 0;
          compare_line(str, keys, f_name);
          keys->line_number++;
        }
      }
    }
    if (counter != 1 && !keys->error) {
      compare_line(str, keys, f_name);
      keys->line_number++;
    }
    free(str);
  }

  if (keys->error == 1) {
    printf("Memory allocation error: function <read_file_lines>\n");
  } else if (!keys->error) {
    file_flags_logic(keys, f_name);
  }
}

void compare_line(char* line, struct Keys* keys, const char* f_name) {
  int line_len = (int)strlen(line);
  int color_s[line_len];
  for (int i = 0; i < line_len; i++) {
    color_s[i] = 0;
  }

  keys->has_match = 0;
  char* tmp_line = line;
  keys->pattern_len = 0;

  while (strlen(tmp_line) > 0) {
    keys->matched = 0;
    keys->closest_position = line_len + 1;

    if (keys->e_f_exist) {
      int opt;
      optind = 1;
      opterr = 0;
      while ((opt = getopt(*keys->p_argc, keys->p_argv, "e:f:")) != -1) {
        if (opt == 'e') {
          regex_line(optarg, tmp_line, keys);
        } else if (opt == 'f') {
          get_patterns_from_file(optarg, tmp_line, keys);
        }
        if (keys->error) break;
      }
    } else {
      regex_line(keys->p_argv[keys->f_start_index - 1], tmp_line, keys);
    }
    // fill in indexes and move line pointer
    if (keys->matched && !keys->error) {
      keys->has_match = 1;
      for (int j = (tmp_line - line) + keys->closest_position;
           j < (tmp_line - line) + keys->closest_position + keys->pattern_len;
           j++) {
        color_s[j] = 1;
      }
      tmp_line = tmp_line + keys->closest_position;
      flag_o_logic(keys, tmp_line, f_name);
      tmp_line = tmp_line + keys->pattern_len;
    } else {
      break;
    }
  }
  if (!keys->error) main_flags_logic(keys, f_name, line, color_s);
}

void get_patterns_from_file(const char* file_name, char* tmp_line,
                            struct Keys* keys) {
  FILE* file = fopen(file_name, "r");
  fseek(file, 0, SEEK_END);
  if (ftell(file) > 0) {
    rewind(file);
    char* str = NULL;
    str = malloc(sizeof(char));
    if (!str) {
      keys->error = 3;
    } else {
      int counter = 0;
      while (!feof(file)) {
        counter++;
        short int ch = fgetc(file);
        char* tmp = realloc(str, (counter + 1) * sizeof(char));
        if (!tmp) {
          keys->error = 3;
          break;
        } else {
          str = tmp;
          if (ch == '\n' && counter != 1) {
            str[counter - 1] = '\0';
            counter = 0;
            regex_line(str, tmp_line, keys);
          } else {
            str[counter - 1] = ch;
            str[counter] = '\0';
          }
        }
      }
      if (counter != 1 && !keys->error) {
        regex_line(str, tmp_line, keys);
      }
      free(str);
    }
  }
  fclose(file);
  if (keys->error)
    printf("Memory allocation error: function <get_patterns_from_file>\n");
}

void regex_line(char* pattern, char* line, struct Keys* keys) {
  short int line_len = (short int)strlen(line);
  regex_t rx;
  int reg_value;
  regmatch_t match[1];
  if (keys->flag_i) {
    reg_value = regcomp(&rx, pattern, REG_ICASE);
  } else {
    reg_value = regcomp(&rx, pattern, 0);
  }
  if (reg_value != 0) {
    printf("Regex compilation error: function <regex_line>");
    keys->error = 2;
  } else {
    reg_value = regexec(&rx, line, 1, match, 0);
    if (reg_value == 0) {
      if ((match[0].rm_so < keys->closest_position ||
           (match[0].rm_so == keys->closest_position &&
            match[0].rm_eo - match[0].rm_so > keys->pattern_len)) &&
          match[0].rm_eo - match[0].rm_so <= line_len - match[0].rm_so) {
        keys->matched = 1;
        keys->closest_position = (short int)match[0].rm_so;
        keys->pattern_len = (short int)(match[0].rm_eo - match[0].rm_so);
      }
    }
  }
  regfree(&rx);
}

void show_line_by_chars(char* line, const int* color_s,
                        const struct Keys* keys) {
  char* p = line;
  int c = 0;
  while (*p != '\0') {
    if (color_s[c]) {
      if (!keys->write_to_file) printf("\033[01;31m");
      printf("%c", *p);
      if (!keys->write_to_file) printf("\033[m");
    } else {
      printf("%c", *p);
    }
    p++;
    c++;
  }
}