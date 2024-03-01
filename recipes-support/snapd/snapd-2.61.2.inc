SRC_URI = "https://${GO_IMPORT}/releases/download/${PV}/snapd_${PV}.vendor.tar.xz"

SRC_URI[md5sum] = "06b54b66fc2090903f89548dae45351e"
SRC_URI[sha256sum] = "d000725250a4d9c8a931b74df9733479a2851d03fe1e663a81fcb61b21509702"

S = "${WORKDIR}/${PN}-${PV}"
