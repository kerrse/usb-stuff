#include <stdio.h>

int main(int argc, char *argv[]) {
	
	if (argc != 2) return 1;

	FILE *usb = fopen(argv[1], "rb");

	// requires sudo
	if (usb == NULL) {
    	perror("fopen");
    	return 1;
	}

	// buffer for the main boot sector
	// main boot sector has an offset of 0 (sectors) and a size of 1 (sectors)
	unsigned char buffer[512];
	fread(buffer, 1, 512, usb);

	// locations defined in exFAT specifications
	const int BytesPerSectorShift = 1U << buffer[108];
	const int SectorsPerClusterShift = 1U << buffer[109];
	printf("BytesPerSectorShift: %i\n", BytesPerSectorShift);
	printf("SectorsPerClusterShift: %i\n", SectorsPerClusterShift);

	fclose(usb);
	return 0;
}
