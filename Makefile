TARGET_BIN:=emWin_eli9325_stm32f103.bin

all: tests runnable

analysis:
	make -f MakeAnalysis.mk V=${V} all

code_beautifier:
	make -f MakeBeautifier.mk V=${V} all

runnable:
	make -f MakeRunnable.mk V=${V} all

tests:
	make -f MakeTests.mk V=${V} all

tests_coverage:
	make -f MakeTests.mk V=${V} coverage

flash:
	st-flash write $(TARGET_BIN) 0x8000000

erase:
	st-flash erase

clean:
	make -f MakeRunnable.mk V=${V} clean
	make -f MakeTests.mk V=${V} clean
	make -f MakeTests.mk V=${V} coverage_clean
	@ rm -rf ./build/objs/ ./build/lib/
