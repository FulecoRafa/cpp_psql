#ifndef PRINT
#define PRINT

#define pinfo(format, ...) printf("\033[34m" format "\033[0m", ##__VA_ARGS__)
#define perror(format, ...) printf("\033[31m" format "\033[0m", ##__VA_ARGS__)

#endif // PRINT
