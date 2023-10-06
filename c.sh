clang -o Unsigncuts -Wall main.c -Oz -flto
strip Unsigncuts
clang -o mod.dylib -Wall -lobjc -dynamiclib dylib.c -Oz -flto
