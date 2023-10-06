#include <stdio.h>
#include <spawn.h>
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */
#define SC_PATH "/System/Applications/Shortcuts.app/Contents/MacOS/Shortcuts"

int main(int argc, char **argv) {
 /* find resources folder */
 if (argv) {
  char *runPath = argv[0];
  if (runPath) {
   /* find_resource_path */
   /* This may be i > 0 instead idk */
   for (int runPathLen = strlen(runPath); runPathLen >= 0; runPathLen--) {
    if (runPath[runPathLen] == '/') {
     /* Copy into resourcesPath */
     /* Cut the beginning and ending " */
     char *start = &runPath[0];
     /* Note the + 1 here, to have a null terminated substring */
     runPathLen += 1;
     char *pathToDylib = (char *)calloc(1, runPathLen + 9);
     memcpy(pathToDylib, start, runPathLen);
     /* find_resource */
     int pathToDylibLen = 9+runPathLen;
     char *resource = "mod.dylib";
     /* Copy resource to pathToDylib */
     for (int i = 0; i < 9; i++) {
      pathToDylib[i+runPathLen] = resource[i];
     }
     pathToDylib[pathToDylibLen] = '\0';
     unsigned int dylibPathLen = pathToDylibLen + 23; /* +1 bc null byte, 22 for DYLD_INSERT_LIBRARIES= */
     char* dylibPath = malloc(sizeof(char) * dylibPathLen);
     strncat(dylibPath, "DYLD_INSERT_LIBRARIES=", 22);
     strncat(dylibPath, pathToDylib, pathToDylibLen);
     free(pathToDylib);
     char **ugh = malloc(sizeof(char *) * dylibPathLen);
     char *const *envp = ugh;
     /* copy dylibPath to envp */
     *ugh = dylibPath;
     printf("envp: %s\n",*envp);
     posix_spawn(NULL, SC_PATH, NULL, NULL, NULL, envp);
     return 0;
    }
   }
  } else {
   fprintf(stderr,"Unsigncuts Error: argv[0] returned NULL\n");
   exit(1);
  }
 } else {
  fprintf(stderr,"Unsigncuts Error: No argv present??\n");
  exit(1);
 }
 fprintf(stderr, "Unsigncuts Error: Unable to find resource path\n");
 exit(1);
}