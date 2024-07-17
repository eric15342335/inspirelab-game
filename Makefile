# Run make on all game directories
default: all-emulator

all-emulator:
	$(MAKE) emulator -C snakegame
	$(MAKE) emulator -C tic-tac-toe
	$(MAKE) emulator -C donut

all-riscv:
	$(MAKE) -C snakegame
	$(MAKE) -C tic-tac-toe
	$(MAKE) -C donut

.PHONY: all-emulator all-riscv
