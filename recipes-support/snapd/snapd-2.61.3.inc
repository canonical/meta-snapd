SRC_URI = "https://${GO_IMPORT}/releases/download/${PV}/snapd_${PV}.vendor.tar.xz"

SRC_URI[md5sum] = "407a07be765fc817c7030ce606e74944"
SRC_URI[sha256sum] = "90d427ca0a0e1306e647c6091176fba678522e2af04228aa274a34d011c82123"

S = "${WORKDIR}/${PN}-${PV}"
