FLAGS = -pedantic-errors -std=c++11

main.o: main.cpp AI_Bot.h FileIO.h Grid_Functions.h

  g++ $(FLAGS) -c $<

AI_Bot.o: AI_Bot.cpp AI_Bot.h Struct_Guard.h
  g++ $(FLAGS) -c $<
  
FileIO.o: FileIO.cpp FileIO.h
  g++ $(FLAGS) -c $<
  
Grid_Functions.o: Grid_Functions.cpp Grid_Functions.h FileIO.h AI_Bot.h Struct_Guard.h
  g++ $(FLAGS) -c $<

Notakto:main.o AI_Bot.o FileIO.o Grid_Functions.o
  g++ $(FLAGS) $^ -o $@
  
clean:
  rm -f project.o AI_Bot.o FileIO.o Grid_Functions.o Notakto

.PHONY: clean 
