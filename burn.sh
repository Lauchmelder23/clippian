#!/bin/bash

mount -t drvfs f: /mnt/f
cp bin/kernel8.img /mnt/f
umount /mnt/f
echo "Done!"