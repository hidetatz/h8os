#ifndef H8OS_OS_LIB_H_
#define H8OS_OS_LIB_H_

/*
 * for serial
 */

// put a charactor
int putc(unsigned char c);
// put a string
int puts(unsigned char *str);
// get a character
unsigned char getc(void);
// get a string
int gets(unsigned char *buf);

/*
 * utilities
 */

void *memset(void *b, int c, long len);
void *memcpy(void *dst, const void *src, long len);
int memcmp(const void *b1, const void *b2, long len);
int strlen(const char *s);
char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, int len);
int putxval(unsigned long value, int column);

#endif // H8OS_OS_LIB_H_
