#include "util.h"

extern void start(void);
extern void intr_softerr(void);
extern void intr_syscall(void);
extern void intr_serintr(void);

void (*vectors[])(void) = {
	start, NULL, NULL, NULL, NULL, NULL, NULL, NULL, intr_syscall, intr_softerr,  // 0: reset, 8-9: trap
	intr_softerr, intr_softerr, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // 10-11: trap
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL,
	intr_serintr,intr_serintr, intr_serintr, intr_serintr, // 52-55: SCI0
	intr_serintr,intr_serintr, intr_serintr, intr_serintr, // 56-59: SCI1
	intr_serintr,intr_serintr, intr_serintr, intr_serintr, // 60-63: SCI2
};
