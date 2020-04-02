#include "extension.h"

void callRegisterInSharedObject(char* so_path) {
    lib_func func = getFunctionFromSharedObject(so_path, __EXTENSION_REGISTER_FUNCTION__);
    func();
}

void callFunctionFromSharedObject(_Function* function) {
    char* function_name = "";
    function_name = strcat_ext(function_name, __EXTENSION_FUNCTION_PREFIX__);
    function_name = strcat_ext(function_name, function->name);
    lib_func func = getFunctionFromSharedObject(function->module_context, function_name);
    func();
    free(function_name);
}

lib_func getFunctionFromSharedObject(char* so_path, char* function_name) {
    void     *handle  = NULL;
    lib_func  func    = NULL;

    handle = dlopen(so_path, RTLD_NOW | RTLD_GLOBAL);

    if (handle == NULL) {
        fprintf(stderr, "Unable to open lib: %s\n", dlerror());
    }
    func = dlsym(handle, function_name);

    if (func == NULL) {
        fprintf(stderr, "Unable to get symbol\n");
    }

    return func;
}
