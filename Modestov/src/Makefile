(FL)=-Wall -Werror -Wextra

solve:
	g++ $(FL) -lncurses example_duchp.cpp -o duchp
	./duchp
	@echo Finished!

style:
	clang-format -i example_duchp.cpp
	clang-format -n example_duchp.cpp

clean:
	rm duchp

rebuild: clean solve
