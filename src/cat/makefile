CC=gcc
CFLAGS=-Wall -Wextra -Werror

cat:
	$(CC) $(CFLAGS) -g --std=c11 cat.c -o cat

clean:
	@rm -rf cat *.txt

clang:
	@cp ../../materials/linters/.clang-format ./
	@clang-format -i *.c *.h
	@clang-format -n *.c *.h
	@rm -rf .clang-format

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

rebuild: clean cat

test: rebuild
	@cp tests/tests.sh .
	@bash tests.sh
	@cat log.txt
	@rm -rf cat *.txt tests.sh

valgrind_test: rebuild
	@cp tests/valgrind_test.sh .
	@bash valgrind_test.sh
	@cat valgrind_out.txt
	@rm -rf cat *.txt valgrind_test.sh