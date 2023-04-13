#ifndef H8OS_OS_INTR_H_
#define H8OS_OS_INTR_H_

#define SOFTVEC_TYPE_NUM 3

#define SOFTVEC_TYPE_SOFTERR 0 // software error (a.k.a. exception)
#define SOFTVEC_TYPE_SYSCALL 1 // system call
#define SOFTVEC_TYPE_SERINTR 2 // serial

#endif // H8OS_OS_INTR_H_
