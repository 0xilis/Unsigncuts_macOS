#include <stdio.h>
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
 class_replaceMethod(cls, name, imp, hookMethod);
}