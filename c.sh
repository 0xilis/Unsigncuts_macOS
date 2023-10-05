clang -o Unsigncuts -Wall main.c resource_management.c -Oz -flto
clang -framework Foundation -dynamiclib dylib.c libsubsidiary/*.c -o mod.dylib
