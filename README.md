# Unsigncuts_macOS
macOS version of Unsigncuts (import unsigned shortcut files). Instead of being a tweak, this has you launch a compiled Unsigncuts.app, which is a launcher for the Shortcuts app that will inject mod.dylib. This allows you to still launch Shortcuts normally if you want to.

# Contributing
Ok; I don't actually expect anyone to contribute TBH (I don’t really have an idea of any contributions that can even be made). But, if you want to contribute, feel free, it's greatly appreciated! If you want a more readable version of the launcher, `main.c`, IMO the initial commit is a bit more readable https://github.com/0xilis/Unsigncuts_macOS/tree/fa9af01890ed8abd58b98e586c6e675cfa2ad164. In the modern commits I've sacrificed readability for speed. Also, in modern commits, rather than embedding libsubsidiary and calling libsubsidiary from dylib.c, I just embed libsubsidiary in dylib.c itself, which helps speed and size a very small amount. README contributions are also appreciated.

# TODO
Not much. I should note that this doesn’t support any contact importing ATM, but if anyone wants me to (or I end up getting bored and deciding to do it anyway) I can easily implement it.

# Compiling
cd to the directory, and run c.sh. This will output a Unsigncuts binary (the launcher to inject the dylib) and mod.dylib (the dylib that will be injected). Create a directory named `Unsigncuts.app`, create `Contents/MacOS/` inside, and place the binary and mod.dylib in it. Now, you should be able to launch `Unsigncuts.app` anytime you want to launch Unsigncuts.

# Licensing
Unsigncuts for macOS is licensed under MIT.
