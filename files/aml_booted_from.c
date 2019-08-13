/*

## hyphop ##

#= detect amlogic boot source from special register
#/ insert next lines after => int board_late_init(void)

*/

		char BOOTED[5];
		//  0   1    2    3   4  5
		//  res emmc nand spi sd usb // read this magic register
		char booted=readl(AO_SEC_GP_CFG0) & 0xf;
		sprintf(BOOTED, "%s",
		booted == 4 ? "sd" : booted == 3 ? "spi" : booted == 1 ? "emmc" : ""
		);
		printf("[i] uboot BOOTED from: %u - %s\n", booted, BOOTED);
		setenv("BOOTED", BOOTED );
