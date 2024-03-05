CC=gcc
CFLAGS=-Wall -Wextra -Werror

grep:
	$(CC) $(CFLAGS) -g --std=c11 grep.c flags_logic.c -o grep

clean:
	@rm -rf grep *.txt

clang:
	@cp ../../materials/linters/.clang-format ./
	@clang-format -i *.c *.h
	@clang-format -n *.c *.h
	@rm -rf .clang-format

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h || true

valgrind: rebuild
	@bash vlg_test.sh
	@cat valgrind_out.txt
	@rm -rf grep *.txt

rebuild: clean grep

test: rebuild
	@bash tests.sh
	@cat log.txt
	@rm -rf grep *.txt