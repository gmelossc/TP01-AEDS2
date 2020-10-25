all:
	gcc src/main.c src/tst/tst.c src/patricia/patricia.c src/menu/menu.c src/stats/stats.c src/word/word.c -o main
production:
	gcc src/main.c src/tst/tst.c src/patricia/patricia.c src/menu/menu.c src/stats/stats.c src/word/word.c -o main
clean:
	rm main
