SRC_URI = "https://${GO_IMPORT}/releases/download/${PV}/snapd_${PV}.vendor.tar.xz"

SRC_URI[md5sum] = "a79b53b0de79153d597bc07c7bd76e4d"
SRC_URI[sha256sum] = "2f0083d2c4e087c29f48cd1abb8a92eb2e63cf04cd433256c86fac05d0b28cab"

S = "${WORKDIR}/${PN}-${PV}"
