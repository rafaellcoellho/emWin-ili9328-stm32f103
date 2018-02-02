all: folder

folder:
	@ echo 'Running Uncrustify in src folder...'
	@ echo ' '
	@ echo 'Create txt with filename'
	find ./src/ -name "*.c" > source_list.txt
	find ./src_stm32/ -name "*.c" >> source_list.txt
	@ echo ' '
	uncrustify -c ./scripts/kernel_linux.cfg --no-backup --replace -F source_list.txt
	@ echo ' '
	rm source_list.txt
	@ echo ' '
	@ echo 'Finished'
