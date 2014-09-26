
#include <stdio.h>
#include <unistd.h>

#include <ftdi.h>
#include <libusb.h>


#define	FT232_EEPROM_SIZE	128

static struct ftdi_context fc;  /* USB port handle */

unsigned char buf[FT232_EEPROM_SIZE] = {
	0x00, 0x40, 0x03, 0x04, 0x01, 0x60, 0x00, 0x06, 
	0x80, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x98, 0x08, 
	0xA0, 0x38, 0xC2, 0x12, 0xA1, 0xAA, 0x01, 0x00, 
	0x08, 0x03, 0x46, 0x00, 0x45, 0x00, 0x52, 0x00, 
	0x38, 0x03, 0x46, 0x00, 0x45, 0x00, 0x52, 0x00, 
	0x20, 0x00, 0x55, 0x00, 0x4C, 0x00, 0x58, 0x00, 
	0x32, 0x00, 0x53, 0x00, 0x20, 0x00, 0x62, 0x00, 
	0x6F, 0x00, 0x61, 0x00, 0x72, 0x00, 0x64, 0x00, 
	0x20, 0x00, 0x4A, 0x00, 0x54, 0x00, 0x41, 0x00, 
	0x47, 0x00, 0x20, 0x00, 0x2F, 0x00, 0x20, 0x00, 
	0x55, 0x00, 0x41, 0x00, 0x52, 0x00, 0x54, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0xD3, 
};


int
main(int argc, char *argv[]) {
	int res;

	res = ftdi_init(&fc);
	if (res < 0) {
		fprintf(stderr, "ftdi_init() failed\n");
		return (res);
	}

	res = ftdi_usb_open(&fc, 0x0403, 0x6001);
	if (res < 0) {
		fprintf(stderr, "ftdi_usb_open() failed\n");
		return (res);
	}

#if 0
	res = ftdi_read_eeprom(&fc, buf);
	if (res < 0) {
		fprintf(stderr, "ftdi_read_eprom() failed\n");
		return (res);
	}
	
	for (int i = 0; i < FT232_EEPROM_SIZE; i++) {
#if 1
		printf("0x%02X, ", buf[i]);
#else
		if (buf[i] >= 32 && buf[i] < 127)
			printf("%c ", buf[i]);
		else
			printf(". ");
#endif
		if ((i & 7) == 7)
			printf("\n");
	}
#else
	res = ftdi_write_eeprom(&fc, buf);
	if (res < 0) {
		fprintf(stderr, "ftdi_read_eprom() failed\n");
		return (res);
	}
	
#endif

        res = ftdi_usb_reset(&fc);
        if (res < 0) {
                fprintf(stderr, "ftdi_usb_reset() failed\n");
                return (res);
        }

	sleep(1);
	libusb_reset_device((void *) fc.usb_dev);

        res = ftdi_usb_close(&fc);
	return (res);
}
