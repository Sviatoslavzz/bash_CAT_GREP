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
	@cp tests/vlg_test.sh .
	@bash vlg_test.sh
	@cat valgrind_out.txt
	@rm -rf grep *.txt vlg_test.sh

rebuild: clean grep

test: rebuild
	@cp tests/tests.sh .
	@bash tests.sh
	@cat log.txt
	@rm -rf grep *.txt tests.sh