# Just the snap tool, as there is no real use case for running the whole snapd
# on the native system
SUMMARY = "The snap tool to enable building snaps and system seeds"
HOMEPAGE = "https://www.snapcraft.io"
LICENSE = "GPL-3.0"
LIC_FILES_CHKSUM = "file://${WORKDIR}/snapd-${PV}/COPYING;md5=d32239bcb673463ab874e80d47fae504"

SRC_URI = "									\
	https://${GO_IMPORT}/releases/download/${PV}/snapd_${PV}.vendor.tar.xz	\
"

SRC_URI[md5sum] = "5952bd537b14f74aa2c33ecba84e9d9a"
SRC_URI[sha256sum] = "ee4096ef1a74a8d29b4cb7f43d442244beec413c21a517f34476270eb6a59fed"

GO_IMPORT = "github.com/snapcore/snapd"

RDEPENDS_${PN} += "		\
	ca-certificates		\
	bash \
"

S = "${WORKDIR}/snapd-${PV}"

inherit go native

# disable shared runtime for x86
# https://forum.snapcraft.io/t/yocto-rocko-core-snap-panic/3261
# GO_DYNLINK is set with arch overrides in goarch.bbclass
GO_DYNLINK_x86 = ""
GO_DYNLINK_x86-64 = ""
GO_DYNLINK_arm = ""
GO_DYNLINK_aarch64 = ""

# The go class does export a do_configure function, of which we need
# to change the symlink set-up, to target snapd's environment.
do_configure() {
	mkdir -p ${S}/src/github.com/snapcore
	ln -snf ${S} ${S}/src/${GO_IMPORT}
	go_do_configure
	# internally calls go run to generate some assets
	(cd ${S} ; GOARCH=${GOHOSTARCH} sh -x ./mkversion.sh ${PV})
}

do_compile() {
	# only build the snap tool
	(
		cd ${S}
		${GO} install -tags '${GO_BUILD_TAGS}' -mod=vendor ${GOBUILDFLAGS} github.com/snapcore/snapd/cmd/snap
	)
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 ${B}/${GO_BUILD_BINDIR}/snap ${D}${bindir}
}

RDEPENDS_${PN} += "squashfs-tools"

INHIBIT_SYSROOT_STRIP = "1"
