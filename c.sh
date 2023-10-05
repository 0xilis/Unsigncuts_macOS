clang -o Unsigncuts -Wall main.c -Oz -flto
clang  -o mod.dylib -Wall -lobjc -dynamiclib dylib.c -Oz -flto
