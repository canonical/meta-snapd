SRC_URI = "https://${GO_IMPORT}/releases/download/${PV}/snapd_${PV}.vendor.tar.xz"

SRC_URI[md5sum] = "852110945dd61f22258ae1a80af55447"
SRC_URI[sha256sum] = "7b8319b5ce1c2957651d0fec8c935bfbee02a1340927d9055ac1bdfdb9c1fca5"

S = "${WORKDIR}/${PN}-${PV}"
