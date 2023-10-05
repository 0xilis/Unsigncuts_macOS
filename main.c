#include <stdio.h>
#include <spawn.h>
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */
#define SC_PATH "/System/Applications/Shortcuts.app/Contents/MacOS/Shortcuts"

/* path to mod.dylib to inject in Shortcuts */
char *pathToDylib;

void launchSC(char **argv) {
 /* find resources folder */
 if (argv) {
  char *runPath = argv[0];
  if (runPath) {
   /* find_resource_path */
   int runPathLen = strlen(runPath);
   /* This may be i > 0 instead idk */
   for (int i = runPathLen; i >= 0; i--) {
    if (runPath[i] == '/') {
     /* Copy into resourcesPath */
     /* Cut the beginning and ending " */
     char *start = &runPath[0];
     char *end = &runPath[i+1];
     /* Note the + 1 here, to have a null terminated substring */
     int resPathLen = end - start;
     char *pathToDylib = (char *)calloc(1, resPathLen + 9);
     memcpy(pathToDylib, start, resPathLen);
     /* find_resource */
     int pathToDylibLen = 9+resPathLen;
     char *resource = "mod.dylib";
     /* Copy resource to pathToDylib */
     for (int i = 0; i < 9; i++) {
      pathToDylib[i+resPathLen] = resource[i];
     }
     pathToDylib[pathToDylibLen] = '\0';
     if (!pathToDylib) {
      fprintf(stderr,"Unsigncuts Error: could not find mod.dylib\n");
      exit(1);
     }
     unsigned int dylibPathLen = pathToDylibLen + 23; /* +1 bc null byte, 22 for DYLD_INSERT_LIBRARIES= */
     char* dylibPath = malloc(sizeof(char) * dylibPathLen);
     strncat(dylibPath, "DYLD_INSERT_LIBRARIES=", 22);
     strncat(dylibPath, pathToDylib, pathToDylibLen);
     free(pathToDylib);
     char **ugh = malloc(sizeof(char *) * dylibPathLen);
     char *const *envp = ugh;
     /* copy dylibPath to envp */
     *ugh = dylibPath;
     pid_t pid;
     const char* args[] = {"Shortcuts", NULL};
     posix_spawn(&pid, SC_PATH, NULL, NULL, (char* const*)args, envp);
     return;
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

int main(int argc, char **argv) {
 launchSC(argv);
 return 0;
}