#include <stdio.h>
#include <spawn.h>
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */
#include "resource_management.h"
#define SC_PATH "/System/Applications/Shortcuts.app/Contents/MacOS/Shortcuts"

/* path to mod.dylib to inject in Shortcuts */
char *pathToDylib;

void launchSC(char **argv) {
 pid_t pid;
 const char* args[] = {"Shortcuts", NULL};
 /* find resources folder */
 if (argv) {
  char *executablePath = argv[0];
  if (executablePath) {
   resourcesPath = find_resource_path(executablePath);
  } else {
   fprintf(stderr,"Unsigncuts Error: argv[0] returned NULL\n");
   exit(1);
  }
 } else {
  fprintf(stderr,"Unsigncuts Error: No argv present??\n");
  exit(1);
 }
 /* find_resource */
 char *resource = "mod.dylib";
 int resPathLen = strlen(resourcesPath);
 char *pathToDylib;
 pathToDylib = malloc(sizeof(char) * (resPathLen + 10));
 /* Copy resourcesPath to pathToDylib */
 for (int i = 0; i < resPathLen; i++) {
  pathToDylib[i] = resourcesPath[i];
 }
 /* Copy resource to pathToDylib */
 for (int i = 0; i < 9; i++) {
  pathToDylib[i+resPathLen] = resource[i];
 }
 int pathToDylibLen = 9+resPathLen;
 pathToDylib[pathToDylibLen] = '\0';
 free(resourcesPath);
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
 printf("envp: %s\n",*envp);
 posix_spawn(&pid, SC_PATH, NULL, NULL, (char* const*)args, envp);
}

int main(int argc, char **argv) {
 launchSC(argv);
 return 0;
}