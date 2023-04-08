#ifndef H8OS_SERIAL_H_
#define H8OS_SERIAL_H_

int serial_init(int index);
int serial_is_send_enable(int index);
int serial_send_byte(int index, unsigned char b);

#endif // H8OS_SERIAL_H_
