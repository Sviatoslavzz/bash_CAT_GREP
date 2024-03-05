#include "cat.h"

int main(int argc, char* argv[]) {
  struct Keys keys = {0, 0, 0, 0, 0,
                      0, 1, 0, 0, (int*)malloc(argc * sizeof(int))};

  if (keys.file_ind == 0) {
    printf("Memory allocation error");
  } else {
    int error = 0;
    error = get_args(argc, argv, &keys);

    if (keys.file_counter && !error) {
      loop_files(argv, &keys);
    } else if (!error) {
      char ch;
      char prev_ch = '\n';
      while (fread(&ch, 1, 1, stdin) > 0) {
        put_cat_char(&prev_ch, &ch, &keys);
      }
    }
  }

  free(keys.file_ind);

  return 0;
}

int get_args(int argc, char** argv, struct Keys* keys) {
  int error = 0;
  int has_empty_flag = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '-' && strlen(argv[i]) != 1 &&
        !has_empty_flag) {
      char* p = argv[i];
      p++;
      while (*p != '\0') {
        if (*p == 'b') {
          keys->flag_b = 1;
        } else if (*p == 'e') {
          keys->flag_E = 1;
          keys->flag_v = 1;
        } else if (*p == 'n') {
          keys->flag_n = 1;
        } else if (*p == 't') {
          keys->flag_T = 1;
          keys->flag_v = 1;
        } else if (*p == 's') {
          keys->flag_s = 1;
        } else if (*p == 'E') {
          keys->flag_E = 1;
        } else if (*p == 'T') {
          keys->flag_T = 1;
        } else if (*p == 'v') {
          keys->flag_v = 1;
        } else {
          printf("%s:  invalid option -- '%c'\n", argv[0] + 2, *p);
          error = 1;
        }
        p++;
      }
    } else if (argv[i][0] == '-' && argv[i][1] == '-' && strlen(argv[i]) > 2 &&
               !has_empty_flag) {
      if (strcmp(argv[i], "--number-nonblank") == 0) {
        keys->flag_b = 1;
      } else if (strcmp(argv[i], "--number") == 0) {
        keys->flag_n = 1;
      } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
        keys->flag_s = 1;
      } else {
        printf("%s:  unrecognized option '%s'\n", argv[0] + 2, argv[i]);
        error = 1;
      }
    } else {
      if (strcmp(argv[i], "--") == 0 && !has_empty_flag) {
        has_empty_flag = 1;
      } else {
        keys->file_counter++;
        keys->file_ind[keys->file_counter - 1] = i;
      }
    }
    if (error) break;
  }
  return error;
}

void loop_files(char** argv, struct Keys* keys) {
  keys->empty_line = 0;
  char prev_ch = '\n';

  for (int i = 0; i < keys->file_counter; i++) {
    if (strcmp(argv[keys->file_ind[i]], "-") == 0) {
      char ch;
      while ((ch = fgetc(stdin)) != EOF) {
        put_cat_char(&prev_ch, &ch, keys);
      }
    } else {
      FILE* file = fopen(argv[keys->file_ind[i]], "rt");
      if (file) {
        char ch;
        while ((ch = fgetc(file)) != EOF) {
          put_cat_char(&prev_ch, &ch, keys);
        }
        fclose(file);
      } else {
        printf("%s: %s: No such file or directory\n", argv[0] + 2,
               argv[keys->file_ind[i]]);
      }
    }
  }
}

void put_cat_char(char* prev_ch, char* ch, struct Keys* keys) {
  if (*prev_ch == '\n' && keys->flag_b && *ch != '\n') {
    printf("%6d	", keys->line_number);
    keys->line_number++;
  }
  if (keys->flag_s && keys->empty_line && *ch == '\n') {
    ;
  } else {
    int er_code = 0;
    if (*prev_ch == '\n' && keys->flag_n && !keys->flag_b) {
      printf("%6d	", keys->line_number);
      keys->line_number++;
    }
    if (keys->flag_T && *ch == 9) {
      fputc('^', stdout);
      *ch = *ch + 64;
    }
    if (keys->flag_v && *ch != 9 && *ch != 10) {
      er_code = get_m_notation(ch);
    }
    if (keys->flag_E && *ch == '\n') {
      fputc('$', stdout);
    }
    if (!er_code) {
      fputc(*ch, stdout);
    }
  }
  if (*prev_ch == '\n' && *ch == '\n') {
    keys->empty_line = 1;
  } else {
    keys->empty_line = 0;
  }
  *prev_ch = *ch;
}

int get_m_notation(char* ch) {
  int er_code = 0;
  if (*ch < -96) {
    printf("M-^");
    *ch = *ch + 192;
  } else if (*ch < 0) {
    printf("M-");
    *ch = *ch + 128;
  } else if (*ch < 32) {
    printf("^");
    *ch = *ch + 64;
  } else if (*ch == 127) {
    printf("^?");
    er_code = 1;
  }
  return er_code;
}