SRC_URI = "https://${GO_IMPORT}/releases/download/${PV}/snapd_${PV}.vendor.tar.xz"

SRC_URI[md5sum] = "dfa4cfb493147c368a12489384f31e98"
SRC_URI[sha256sum] = "af30dc20c09872bf42faedb8f5306abc85faf9e3b010cb2388086cbc42a0909a"

S = "${WORKDIR}/${PN}-${PV}"
