# Unsigncuts_macOS
macOS version of Unsigncuts (import unsigned shortcut files). Instead of being a tweak, this has you launch a compiled Unsigncuts.app, which is a launcher for the Shortcuts app that will inject mod.dylib (which uses libsubsidiary to swizzle a method to always return true). This allows you to still launch Shortcuts normally if you want to.

# Compiling
cd to the directory, and run c.sh. This will output a Unsigncuts binary (the launcher to inject the dylib) and mod.dylib (the dylib that will be injected). Create a directory named `Unsigncuts.app`, create `Contents/MacOS/` inside, and place the binary and mod.dylib in it. Now, you should be able to launch `Unsigncuts.app` anytime you want to launch Unsigncuts.

# Licensing
Unsigncuts for macOS is licensed under MIT.
