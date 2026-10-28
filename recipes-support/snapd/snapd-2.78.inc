SRC_URI = "https://${GO_IMPORT}/releases/download/${PV}/snapd_${PV}.vendor.tar.xz"

SRC_URI[sha256sum] = "197d5e5870ae7f3681276cea37339d5ee528ddfaf47f53509f858fdad46e4aed"

S = "${UNPACKDIR}/snapd-${PV}"
