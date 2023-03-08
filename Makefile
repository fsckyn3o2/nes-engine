NAME = nes-template
BOARD = nes-nrom-128
EMULATOR = fceux

build:
	rm -f src/*.o src/*.s data/screen/*/*.o data/music/*.o lib/*.o $(NAME).nes
	cc65 -Cl -Oi -Idata/screen/*/*.h -Ilib/ src/*.c --add-source
	ca65 -Ilib -Idata/ -Idata/musics lib/crt0.s
	ls src/main.s | xargs -n 1 ca65
	ld65 -C data/nes-nrom-32.cfg -o $(NAME).nes lib/*.o src/main.o nes.lib
    
clean:
	rm -f src/*.o src/*.s data/screen/*/*.o data/music/*.o lib/*.o $(NAME).nes

play: $(NAME).nes
	$(EMULATOR) $(NAME).nes

play-win: $(NAME).nes
	$(EMULATOR).exe $(NAME).nes

all:
	rm -f src/*.o src/*.s data/screen/*/*.o data/music/*.o lib/*.o $(NAME).nes
	cc65 -Cl -Oi -Idata/screen/*/*.h -Ilib/ src/*.c --add-source
	ca65 -Ilib -Idata/ -Idata/musics lib/crt0.s
	ls src/main.s | xargs -n 1 ca65
	ld65 -C data/nes-nrom-32.cfg -o $(NAME).nes lib/*.o src/main.o nes.lib

	$(EMULATOR) $(NAME).nes