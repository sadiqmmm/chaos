#include "errors.h"

extern int yylineno;
extern char *last_token;

void throw_error_var(throw_error_args in) {
    unsigned short code = in.code ? in.code : 0;
    char *str1 = in.str1 ? in.str1 : "";
    char *str2 = in.str2 ? in.str2 : "";
    long long lld1 = in.lld1 ? in.lld1 : 0;
    unsigned long long llu = in.llu1 ? in.llu1 : 0;
    throw_error_base(code, str1, str2, lld1, llu);
}

void throw_error_base(unsigned short code, char *str1, char *str2, long long lld1, unsigned long long llu1) {
    char title_msg[__KAOS_MSG_LINE_LENGTH__];
    char current_module_msg[__KAOS_MSG_LINE_LENGTH__];
    char line_no_msg[__KAOS_MSG_LINE_LENGTH__];
    char error_msg[__KAOS_MSG_LINE_LENGTH__];
    char error_msg_out[__KAOS_MSG_LINE_LENGTH__];

    if (last_token != NULL && strcmp(last_token, "\n") != 0) yylineno++;

    sprintf(title_msg, "  %s Error:", __KAOS_LANGUAGE_NAME__);
    sprintf(current_module_msg, "    Module: %s", getCurrentModule());
    sprintf(line_no_msg, "    Line: %d", yylineno);

    switch (code)
    {
        case E_UNKNOWN_VARIABLE_TYPE:
            sprintf(error_msg, "Unknown variable type: %s for variable: %s", str1, str2);
            break;
        case E_VARIABLE_ALREADY_DEFINED:
            sprintf(error_msg, "The variable name '%s' is already defined!", str1);
            break;
        case E_UNDEFINED_VARIABLE:
            sprintf(error_msg, "Undefined variable: %s", str1);
            break;
        case E_MEMORY_ALLOCATION_FOR_ARRAY_FAILED:
            sprintf(error_msg, "Memory allocation for array '%s' is failed!", str1);
            break;
        case E_ILLEGAL_ELEMENT_TYPE_FOR_TYPED_ARRAY:
            sprintf(error_msg, "Illegal element type: %s for the typed array: %s", str1, str2);
            break;
        case E_VARIABLE_IS_NOT_AN_ARRAY:
            sprintf(error_msg, "Variable '%s' is not an array!", str1);
            break;
        case E_INDEX_OUT_OF_RANGE:
            sprintf(error_msg, "Index out of range: %lld for array: %s", lld1, str1);
            break;
        case E_ILLEGAL_VARIABLE_TYPE_FOR_VARIABLE:
            sprintf(error_msg, "Illegal variable type: %s, for variable: %s", str1, str2);
            break;
        case E_ARRAYS_ARE_NOT_MASS_ASSIGNABLE:
            sprintf(error_msg, "Arrays are not mass assignable! Target variable: %s", str1);
            break;
        case E_VARIABLE_IS_NOT_A_DICTIONARY:
            sprintf(error_msg, "Variable '%s' is not a dictionary!", str1);
            break;
        case E_UNDEFINED_KEY:
            sprintf(error_msg, "Undefined key: %s for dictionary: %s", str1, str2);
            break;
        case E_UNRECOGNIZED_COMPLEX_DATA_TYPE:
            sprintf(error_msg, "Unrecognized complex data type: %s for variable: %s", str1, str2);
            break;
        case E_ILLEGAL_VARIABLE_TYPE_FOR_FUNCTION:
            sprintf(error_msg, "Illegal variable type: %s for function: %s", str1, str2);
            break;
        case E_UNDEFINED_FUNCTION:
            sprintf(error_msg, "Undefined function: %s", str1);
            break;
        case E_MEMORY_ALLOCATION_FOR_FUNCTION_FAILED:
            sprintf(error_msg, "Memory allocation for the function is failed!");
            break;
        case E_MAXIMUM_RECURSION_DEPTH_EXCEEDED:
            sprintf(error_msg, "Maximum recursion depth %d exceeded!", __KAOS_MAX_RECURSION_DEPTH__);
            break;
        case E_UNEXPECTED_VALUE_TYPE:
            sprintf(error_msg, "Unexpected value type: %s for variable: %s", str1, str2);
            break;
        case E_FUNCTION_DID_NOT_RETURN_ANYTHING:
            sprintf(error_msg, "The function '%s' did not return anything!", str1);
            break;
        case E_MODULE_IS_EMPTY_OR_NOT_EXISTS_ON_PATH:
            sprintf(error_msg, "The module %s is either empty or not exists on the path!", str1);
            break;
        case E_NO_VARIABLE_WITH_ID:
            sprintf(error_msg, "No variable with given id: %llu is found!", llu1);
            break;
        case E_INDEX_OUT_OF_RANGE_STRING:
            sprintf(error_msg, "Index out of range: %lld for string: %s", lld1, str1);
            break;
        case E_ILLEGAL_CHARACTER_ASSIGNMENT_FOR_STRING:
            sprintf(error_msg, "Illegal character assignment for string: %s", str1);
            break;
        case E_NOT_A_CHARACTER:
            sprintf(error_msg, "Right hand side of the assignment is not a character for string: %s", str1);
            break;
        case E_PROGRAM_FILE_DOES_NOT_EXISTS_ON_PATH:
            sprintf(error_msg, "Program file does not exists on the given path: %s", str1);
            break;
        default:
            sprintf(error_msg, "Unkown error.");
            break;
    }

    sprintf(error_msg_out, "    %s", error_msg);

    str_replace(error_msg_out, "\n", "\\n");

    int cols[4];
    cols[0] = (int) strlen(title_msg) + 1;
    cols[1] = (int) strlen(current_module_msg) + 1;
    cols[2] = (int) strlen(line_no_msg) + 1;
    cols[3] = (int) strlen(error_msg_out) + 1;
    int ws_col = largest(cols, 4) + 4;
    InteractiveShellErrorAbsorber_ws_col = ws_col;

    #if defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        printf("\033[1;41m");
    #endif
    printf("%-*s", ws_col, title_msg);
    #if defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        printf("\033[0m");
    #endif
    printf("\n");

    #if defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        printf("\033[0;41m");
    #endif
    printf("%-*s", ws_col, current_module_msg);
    #if defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        printf("\033[0m");
    #endif
    printf("\n");

    #if defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        printf("\033[0;41m");
    #endif
    printf("%-*s", ws_col, line_no_msg);
    #if defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        printf("\033[0m");
    #endif
    printf("\n");

    #if defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        printf("\033[0;41m");
    #endif
    printf("%-*s", ws_col, error_msg_out);
    #if defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        printf("\033[0m");
    #endif
    printf("\n");

    if (!is_interactive) {
        freeEverything();
        exit(code);
    } else {
        longjmp(InteractiveShellErrorAbsorber, 1);
    }
}
