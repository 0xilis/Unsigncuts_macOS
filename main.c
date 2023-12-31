#include <stdio.h>
#include <spawn.h>
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */
#define SC_PATH "/System/Applications/Shortcuts.app/Contents/MacOS/Shortcuts"
#include <limits.h> /* UINT_MAX */

int main(int argc, char **argv) {
 /* find resources folder */
 if (argv) {
  char *runPath = argv[0];
  if (runPath) {
   /* find_resource_path */
   #if __x86_64__
   unsigned int runPathLen = strlen(runPath);
   res_find:
   /* we need to inline asm runPathLen-- or else compiler optimizations messes it up */
   asm volatile (
        "dec %0\n\t"
        : "=r" (runPathLen)
        : "r" (runPathLen)
    );
   if (runPathLen == UINT_MAX) { goto res_err; };
   if (runPath[runPathLen] != '/') { goto res_find; };
   #else
   /* yes, we take into the account the two extra }'s */
   for (int runPathLen = strlen(runPath); runPathLen >= 0; runPathLen--) {
    if (runPath[runPathLen] == '/') {
   #endif
   runPathLen += 1;
   unsigned int dylibPathLen = 9 + runPathLen + 22; /* +1 bc null byte, 22 for DYLD_INSERT_LIBRARIES= */
   char* dylibPath = malloc(sizeof(char) * dylibPathLen+1);
   strncat(dylibPath, "DYLD_INSERT_LIBRARIES=", 22);
   strncat(dylibPath, runPath, runPathLen);
   /* find_resource */
   runPathLen += 22;
   char *resource = "mod.dylib";
   /* Copy resource to pathToDylib */
   #if __x86_64__
   int i = 0;
   hacky_optimized_for_loop:
   dylibPath[i+runPathLen] = resource[i];
   i++;
   if (i != 9) { goto hacky_optimized_for_loop; };
   #else
   for (int i = 0; i < 9; i++) {
    dylibPath[i+runPathLen] = resource[i];
   }
   #endif
   dylibPath[dylibPathLen] = '\0';
   /* dunno how this works but it does */
   char *const *envp = &dylibPath;
   posix_spawn(NULL, SC_PATH, NULL, NULL, NULL, envp);
   return 0;
   #if __x86_64__
   #else
   }
   }
   #endif
  } else {
   fprintf(stderr,"Unsigncuts Error: argv[0] returned NULL\n");
   return 1;
  }
 } else {
  fprintf(stderr,"Unsigncuts Error: No argv present??\n");
  return 1;
 }
 res_err:
 fprintf(stderr, "Unsigncuts Error: Unable to find resource path\n");
 return 1;
}
