CC=gcc
CFLAGS=-Wall -Wextra -Werror

cat:
	$(CC) $(CFLAGS) -g --std=c11 cat.c -o cat

clean:
	rm -rf cat *.txt

clang:
	@cp ../../materials/linters/.clang-format ./
	@clang-format -i *.c *.h || echo "OK"
	@clang-format -n *.c *.h || echo "OK"
	@rm -rf .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

memcheck:
	valgrind --tool=memcheck --leak-check=yes ./cat

rebuild: clean cat

test: rebuild
	@bash tests.sh
	@cat log.txt
	@rm -rf cat *.txt