define Device/yuzuki_tinyvision
  DEVICE_VENDOR := YuzukiHD
  DEVICE_MODEL := TinyVision
  DEVICE_DTS = sun8i-v851se-tinyvision
  IMAGE/sysupgrade.img.gz := sunxi-img | gzip | append-metadata
endef
TARGET_DEVICES += yuzuki_tinyvision
