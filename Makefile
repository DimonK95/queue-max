all: qmax

%: %.c
	gcc $< -o $@

