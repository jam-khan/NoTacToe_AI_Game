FLAGS = -pedantic-errors -std=c++11

project.o: project.cpp AI_Bot.h FileIO.h Grid_Functions.h

  g++ $(FLAGS) -c $<

AI_Bot.o: AI_Bot.cpp AI_Bot.h
  g++ $(FLAGS) -c $<
  
FileIO.o: FileIO.cpp FileIO.h
  g++ $(FLAGS) -c $<
  
Grid_Functions.o: Grid_Functions.cpp Grid_Functions.h
  g++ $(FLAGS) -c $<
  
  
FileIO.o: gcd.o gcd_main.o
  g++ $(FLAGS) $^ -o $@
  
clean:
  rm -f gcd gcd.o gcd_main.o gcd.tgz
  
tar:
  tar -czvf gcd.tgz *.cpp *.h
  
.PHONY: clean tar
