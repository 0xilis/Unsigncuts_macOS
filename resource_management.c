/*
 * Copyright (C) 2023 Snoolie K / 0xilis. All rights reserved.
 *
 * This document is the property of Snoolie K / 0xilis.
 * It is considered confidential and proprietary.
 *
 * This document may not be reproduced or transmitted in any form,
 * in whole or in part, without the express written permission of
 * Snoolie K / 0xilis.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource_management.h"

/* Resource Finder */

char *find_resource_path(char* runPath) {
  int runPathLen = strlen(runPath);
  /* This may be i > 0 instead idk */
  for (int i = runPathLen; i >= 0; i--) {
    if (runPath[i] == '/') {
      /* Copy into resourcesPath */
      /* Cut the beginning and ending " */
      char *start = &runPath[0];
      char *end = &runPath[i+1];
      /* Note the + 1 here, to have a null terminated substring */
      char *resourcesPath = (char *)calloc(1, end - start + 1);
      memcpy(resourcesPath, start, end - start);
      return resourcesPath;
    }
  }
  fprintf(stderr, "Unsigncuts Error: Unable to find resource path\n");
  exit(1);
}