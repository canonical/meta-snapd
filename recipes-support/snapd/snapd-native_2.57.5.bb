# Just the snap tool, as there is no real use case for running the whole snapd
# on the native system
SUMMARY = "The snap tool to enable building snaps and system seeds"
HOMEPAGE = "https://www.snapcraft.io"
LICENSE = "GPL-3.0-only"
LIC_FILES_CHKSUM = "file://${WORKDIR}/snapd-${PV}/COPYING;md5=d32239bcb673463ab874e80d47fae504"

SRC_URI = "									\
	https://${GO_IMPORT}/releases/download/${PV}/snapd_${PV}.vendor.tar.xz	\
"

SRC_URI[md5sum] = "722be543c98df28ab04df1ade4ab8d38"
SRC_URI[sha256sum] = "22873493d9cd389b7d33775f3af22d663a749ecf53c4b93c03fd880350ee612d"

RDEPENDS_${PN} += "		\
	ca-certificates		\
	bash \
"

S = "${WORKDIR}/snapd-${PV}"

require snapd-go.inc

inherit native

do_configure() {
	snapd_go_do_configure
}

do_compile() {
	snapd_go_do_compile_snap
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 ${B}/${GO_BUILD_BINDIR}/snap ${D}${bindir}
}

RDEPENDS_${PN} += "squashfs-tools"

INHIBIT_SYSROOT_STRIP = "1"
