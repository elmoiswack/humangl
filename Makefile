all: delete_appledouble
	@mkdir -p build
	@cmake -S . -B build
	@cmake --build build
	@./build/humanGL

clean:
	@rm -rf build

re: clean all

delete_appledouble:
	@echo "Deleting AppleDouble files..."
	@find . -name '._*' -type f -delete

.PHONY: all clean re delete_appledouble
