#ifndef _GENERAL_
#define _GENERAL_

#define MAX_STR_LEN 255

#define COLSE_RETURN_0(fp) do { fclose(fp); return 0; } while (0)
#define CHECK_RETURN_NULL(ptr) {if(!ptr) return NULL;}


char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size, FILE* source);
char*	myGetsF(char* buffer, int size, FILE* fp);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength);
void	generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));

#endif