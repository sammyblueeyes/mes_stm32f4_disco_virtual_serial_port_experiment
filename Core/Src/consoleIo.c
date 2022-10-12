// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include "usbd_cdc_if.h"
#include <string.h>


#include "circular_buffer.h"

static cbuf_handle_t g_receive_buf_handle;
#define RECEIVE_BUF_SIZE 256
static uint8_t g_receive_buf[RECEIVE_BUF_SIZE];


eConsoleError ConsoleIoInit(void)
{
	g_receive_buf_handle = circular_buf_init(g_receive_buf, RECEIVE_BUF_SIZE);
	return CONSOLE_SUCCESS;
}
eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
	*readLength = 0;
    while (*readLength < bufferLength) {
    	if (circular_buf_get(g_receive_buf_handle, &(buffer[*readLength])) == 0) {
    		(*readLength)++;
    	} else {
    		break;
    	}
    }

	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	uint16_t Len = strlen(buffer);
	while (CDC_Transmit_FS(buffer, Len) != 0) {
		HAL_Delay(5);
	}
	return CONSOLE_SUCCESS;
}

void ReceiveUSBData(uint8_t* Buf, uint32_t Len)
{
	for (int i = 0; i < Len; i++) {
		circular_buf_put(g_receive_buf_handle, Buf[i]);
	}
}
