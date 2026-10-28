# Just the snap tool, as there is no real use case for running the whole snapd
# on the native system
SUMMARY = "The snap tool to enable building snaps and system seeds"
HOMEPAGE = "https://www.snapcraft.io"
LICENSE = "GPL-3.0-only"
LIC_FILES_CHKSUM = "file://${S}/COPYING;md5=d32239bcb673463ab874e80d47fae504"

require snapd-2.78.inc

RDEPENDS:${PN} += "		\
	ca-certificates		\
	bash \
"

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
	install -m 0755 ${B}/${GO_BUILD_BINDIR}/snapd ${D}${bindir}
	# acts as the snap CLI when invoked as snap
	ln -s snapd ${D}${bindir}/snap
}

RDEPENDS:${PN} += "squashfs-tools"

INHIBIT_SYSROOT_STRIP = "1"
