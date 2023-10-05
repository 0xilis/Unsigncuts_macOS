clang -o Unsigncuts -Wall main.c -Oz -flto
clang  -o mod.dylib -Wall -framework Foundation -dynamiclib dylib.c libsubsidiary/libsubsidiary.c -Oz -flto
