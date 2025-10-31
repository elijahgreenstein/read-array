tests: test/test-read-array test/test-examples

test/test-read-array: src/read-array.c test/test-read-array.c
	gcc -Wall -o $@ $< test/test-read-array.c

test/test-examples: src/read-array.c test/test-examples.c
	gcc -Wall -o $@ $< test/test-examples.c

.PHONY: runtests
runtests:
	@./test/test-read-array
	@./test/test-examples

.PHONY: cleantests
cleantests:
	rm ./test/test-read-array ./test/test-examples
