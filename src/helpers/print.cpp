#ifndef PRINT
#define PRINT

#define pinfo(format, ...) printf("\033[34m" format "\033[0m", ##__VA_ARGS__)
#define perror(format, ...) printf("\033[31m" format "\033[0m", ##__VA_ARGS__)
#define todo() perror("Not yet implemented"); exit(1);

#endif // PRINT
