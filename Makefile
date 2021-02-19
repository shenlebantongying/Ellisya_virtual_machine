.PHONY dump:
	hexdump -e '8/1 " %02X" "\n"' ./vm.image