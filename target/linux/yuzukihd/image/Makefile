# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2013 OpenWrt.org

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

DEVICE_VARS += UBOOT_DEVICE_NAME

define Build/boot-common
	# This creates a new folder copies the dtb (as sunxi.dtb) 
	# and the kernel image (as kernel.img)
	mkdir -p $@.boot

	$(CP) $(DTS_DIR)/$(DEVICE_DTS).dtb $@.boot/sunxi.dtb
	$(CP) $(IMAGE_KERNEL) $@.boot/kernel.img
endef

define Build/boot-script
	# Make an boot script and copy it to the boot partition
	mkdir -p $@.boot/extlinux
	$(CP) extlinux.conf $@.boot/extlinux/extlinux.conf
endef

define Build/sunxi-img
	# Creates the final SD/eMMC images, 
	# combining boot partition, root partition as well as the u-boot bootloader

	rm -f $@.boot
	mkfs.fat $@.boot -C $(FAT32_BLOCKS)

	./gen_sunxi_sdcard_img.sh $@ \
		$@.boot \
		$(IMAGE_ROOTFS) \
		$(CONFIG_SUNXI_SD_BOOT_PARTSIZE) \
		$(CONFIG_TARGET_ROOTFS_PARTSIZE) \
	rm -f $@.boot

	# Copy the u-boot-with-spl image to the image at sector 0x40 and 0x4000
	dd if="boot0_sdcard.fex of="$@" bs=1K seek=8 conv=notrunc
	dd if="boot_package.fex of="$@" bs=1K seek=12288 conv=notrunc
	dd if="boot_package.fex of="$@" bs=1K seek=16400 conv=notrunc
	#dd if="$(STAGING_DIR_IMAGE)"/u-boot-with-spl.bin of="$@" seek=34 conv=notrunc
endef

### Devices ###
define Device/Default
  PROFILES := Default
  KERNEL := kernel-bin
  IMAGES := sysupgrade.img.gz
endef

include $(SUBTARGET).mk

$(eval $(call BuildImage))
