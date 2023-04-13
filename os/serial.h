#ifndef H8OS_OS_SERIAL_H_
#define H8OS_OS_SERIAL_H_

// initialize serial device
int serial_init(int index);

// check if send is enabled
int serial_is_send_enable(int index);

// send a byte
int serial_send_byte(int index, unsigned char b);

// check if receive is enabled
int serial_is_recv_enable(int index);

// receive a byte
unsigned char serial_recv_byte(int index);

int serial_intr_is_send_enable(int index);
void serial_intr_send_enable(int index);
void serial_intr_send_disable(int index);
int serial_intr_is_receive_enable(int index);
void serial_intr_receive_enable(int index);
void serial_intr_receive_disable(int index);

#endif // H8OS_OS_SERIAL_H_
