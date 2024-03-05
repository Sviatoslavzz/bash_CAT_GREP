CC=gcc
CFLAGS=-Wall -Wextra -Werror

cat:
	$(CC) $(CFLAGS) -g --std=c11 cat.c -o cat
clean:
	rm -rf cat *.txt
clang:
	clang-format -i *.c *.h || echo "OK"
	clang-format -n *.c *.h || echo "OK"
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
memcheck:
	valgrind --tool=memcheck --leak-check=yes ./cat
rebuild: clean cat

test: clean
	$(CC) $(CFLAGS) -g --std=c11 cat.c -o cat	
	bash tests.sh
	rm -rf cat