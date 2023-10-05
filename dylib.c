#include <stdio.h>
#include <spawn.h>
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */

#include <objc/runtime.h>

typedef struct objc_selector *SEL;

static unsigned char hook_WFShortcutExtractor_allowsOldFormatFile(void) {
 return 0x1;
}

__attribute__((constructor)) static void init() {
 Class cls = objc_getClass("WFShortcutExtractor");
 SEL name = sel_getUid("allowsOldFormatFile");
 const char *hookMethod = method_getTypeEncoding(class_getInstanceMethod(cls, name));
 if (!hookMethod) {
  return;
 }
 IMP imp = (IMP)&hook_WFShortcutExtractor_allowsOldFormatFile;
 unsigned int numberOfMethods;
 Method *methods = class_copyMethodList(cls, &numberOfMethods);
 for (int i = 0; i < numberOfMethods; i++) {
  Method m = methods[i];
  if (method_getName(m) == name) {
   /* the method is in this class so we can safely replace the method */
   class_replaceMethod(cls, name, imp, hookMethod);
   free(methods);
   return;
  }
 }
 /* the method is in the superclass, add the method instead to not override superclass and get IMP of orig */
 class_addMethod(cls, name, imp, hookMethod);
 free(methods);
}