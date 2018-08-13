#include <stdio.h>
#define _DEBUG_ 
#ifdef _DEBUG_
#define log_debug(arg...) {\
printf("[log_debug]:%s:%s:%d ---->",__FILE__,__FUNCTION__,__LINE__);\
printf(arg);\
fflush(stdout);\
} 
#else 
#define log_debug(arg...) {} 
#endif 