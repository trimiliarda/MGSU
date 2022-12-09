(FL)=-Wall -Werror -Wextra
(D)=-demangle -lto_library /Library/Developer/CommandLineTools/usr/lib/libLTO.dylib -dynamic -arch x86_64 -platform_version macos 11.0.0 11.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -o main -L/usr/local/lib G8.o ../dislin/libdiscpp.dylib -lc++ -lSystem /Library/Developer/CommandLineTools/usr/lib/clang/12.0.0/lib/darwin/libclang_rt.osx.a

5: 55.o
	g++ $(FL) 55.o ../dislin/libdiscpp.11.dylib -o main
	./main
	@echo Finished!
	rm main

55.o:
	g++ $(FL) -c 55.cpp -o 55.o

7:
	g++ $(FL) G7.cpp -o main_7
	./main_7
	@echo Finished!
	rm main_7

8:
	g++ $(FL) $(D) G8.cpp -o main
	./main
	@echo Finished!
	rm main

G8.o:
	g++ $(FL) -c G8.cpp -o G8.o

16:
	g++ $(FL) G16.cpp -o main_16
	./main_16
	@echo Finished!
	rm main_16

17:
	g++ $(FL) G17.cpp -o main
	./main
	@echo Finished!
	rm main