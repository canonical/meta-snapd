# Just the snap tool, as there is no real use case for running the whole snapd
# on the native system
SUMMARY = "The snap tool to enable building snaps and system seeds"
HOMEPAGE = "https://www.snapcraft.io"
LICENSE = "GPL-3.0-only"
LIC_FILES_CHKSUM = "file://${WORKDIR}/snapd-${PV}/COPYING;md5=d32239bcb673463ab874e80d47fae504"

SRC_URI = "									\
	https://${GO_IMPORT}/releases/download/${PV}/snapd_${PV}.vendor.tar.xz	\
"

SRC_URI[md5sum] = "bad2ff907110e0c095c1f245101a2968"
SRC_URI[sha256sum] = "1d940ba7cee1b6a1fd961c591abf8fdde9d313eff0fb8b6967ad01f40426f33e"

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

RDEPENDS:${PN} += "squashfs-tools"

INHIBIT_SYSROOT_STRIP = "1"
