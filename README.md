# uboot extra

## script

simple uboot plain script run from mem without mkimage wrapers

`script` is cool alternative for `autoscript` and `source`
simle usage without mkimage

+ https://github.com/hyphop/uboot-extra
+ [cmd/cmd_script.c](cmd/cmd_script.c)
+ https://raw.githubusercontent.com/hyphop/uboot-extra/master/cmd/cmd_script.c

# sintax and parsing

```
#!script - script must begin from this marker
##END##  - its end marker - after this lines all strings ignored
'\0'     - its same end marker
```

script parsed by run_command_list

# features

we can use same `script` cmd for wrapped scripts with 72 bytes mkimage header
which parsed by `source` or `autoscript`

# how to install it 

just add next line to Makefile

    obj-y += cmd_script.o

# uboot usage

    script [addr] [bytes] [nochk] [silent] - run script starting at addr
	    bytes - read bytes (hex) limit
	    nochk - no check #!script header
	    silent - be silent

# uboot usage  examples

    script 0x1000000				- simple run from addr 0x1000000
    script 0x1000000 32 			- same but only fist 32 bytes
    script 0x1000000 $filesize 			- same but limited by file size value 
    script 0x1000000 $filesize nochk 		- same but without header check
    script 0x1000000 $filesize nochk silent	- same but silent

    # tftp script usage
    ADDR=0x1000000; tftp $ADDR test.script && script $ADDR $filesize 

    # usage as files
    ADDR=100000; ext4load mmc 1:5 $ADDR dhcp.cmd_test.script; script $ADDR $filesize

    # spi flash usage
    ADDR=100000; sf read $ADDR $SCRIPT_OFFSET $SCRIPT_BYTES; script $ADDR
