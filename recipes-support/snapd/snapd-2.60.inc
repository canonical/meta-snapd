SRC_URI = "https://${GO_IMPORT}/releases/download/${PV}/snapd_${PV}.vendor.tar.xz"

SRC_URI[md5sum] = "bad2ff907110e0c095c1f245101a2968"
SRC_URI[sha256sum] = "1d940ba7cee1b6a1fd961c591abf8fdde9d313eff0fb8b6967ad01f40426f33e"

S = "${WORKDIR}/${PN}-${PV}"
