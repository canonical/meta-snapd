SUMMARY = "The snapd and snap tools enable systems to work with .snap files."
HOMEPAGE = "https://www.snapcraft.io"
LICENSE = "GPL-3.0-only"
LIC_FILES_CHKSUM = "file://${WORKDIR}/${PN}-${PV}/COPYING;md5=d32239bcb673463ab874e80d47fae504"

PACKAGECONFIG ??= "${@bb.utils.contains('DISTRO_FEATURES', 'apparmor', 'apparmor', '', d)}"
PACKAGECONFIG[apparmor] = "--enable-apparmor,--disable-apparmor,apparmor,apparmor"

SRC_URI:append = " file://0001-mkversion-data-generate-supported-assert-formats-inf.patch"

LIC_FILES_CHKSUM = "file://${S}/COPYING;md5=d32239bcb673463ab874e80d47fae504"

DEPENDS += " \
	glib-2.0		\
	libcap			\
	libseccomp		\
	udev			\
	xfsprogs		\
	autoconf-archive	\
"

RDEPENDS:${PN} += " \
	bash			\
	ca-certificates		\
	kernel-module-squashfs	\
	squashfs-tools		\
"

EXTRA_OECONF += "			\
	--libexecdir=${libdir}/snapd	\
	--with-snap-mount-dir=/snap     \
"

inherit systemd autotools pkgconfig

require snapd-go.inc

# Our tools build with autotools are inside the cmd subdirectory
# and we need to tell the autotools class to look in there.
AUTOTOOLS_SCRIPT_PATH = "${S}/cmd"

SYSTEMD_SERVICE:${PN} = "snapd.service \
	${@bb.utils.contains('PACKAGECONFIG', 'apparmor', 'snapd.apparmor.service', '', d)} \
"

do_configure() {
	snapd_go_do_configure
	autotools_do_configure
}

do_compile() {
	snapd_go_do_compile
	# build the rest
	(
		cd ${B}
		autotools_do_compile
	)
}

do_install() {
	install -d ${D}${libdir}/snapd
	install -d ${D}${bindir}
	install -d ${D}${systemd_unitdir}/system
	install -d ${D}/var/lib/snapd
	install -d ${D}/var/lib/snapd/snaps
	install -d ${D}/var/lib/snapd/lib/gl
	install -d ${D}/var/lib/snapd/desktop
	install -d ${D}/var/lib/snapd/environment
	install -d ${D}/var/snap
	install -d ${D}${sysconfdir}/profile.d
	install -d ${D}${systemd_unitdir}/system-generators

	oe_runmake -C ${B} install DESTDIR=${D}
	oe_runmake -C ${S}/data install \
		DESTDIR=${D} \
		BINDIR=${bindir} \
		LIBEXECDIR=${libdir} \
		SYSTEMDSYSTEMUNITDIR=${systemd_system_unitdir} \
		SNAP_MOUNT_DIR=/snap \
		SNAPD_ENVIRONMENT_FILE=${sysconfdir}/default/snapd

	# systemd system-environment-generators directory is not handled with a
	# varaible in systemd.pc so the build code does an educated guess of using
	# ${prefix}/lib/systemd/system-environment-generators which ends up as
	# /usr/lib/systemd/.., but we want /lib/systemd/..
	cp -av ${D}${prefix}${systemd_unitdir}/system-environment-generators \
	   ${D}${systemd_unitdir}
	rm -rf ${D}${prefix}${systemd_unitdir}

	snapd_go_install

	echo "PATH=\$PATH:/snap/bin" > ${D}${sysconfdir}/profile.d/20-snap.sh

	# ubuntu-core-launcher is dead
	rm -fv ${D}${bindir}/ubuntu-core-launcher
	# drop unnecessary units
	rm -fv ${D}${systemd_unitdir}/system/snapd.system-shutdown.service
	rm -fv ${D}${systemd_unitdir}/system/snapd.snap-repair.*
	rm -fv ${D}${systemd_unitdir}/system/snapd.core-fixup.*
	rm -fv ${D}${systemd_unitdir}/system/snapd.recovery-chooser-trigger.service
	rm -fv ${D}${systemd_unitdir}/system/snapd.aa-prompt-listener.service
	# and related scripts and binaries
	rm -fv ${D}${libdir}/snapd/snapd.core-fixup.sh
	rm -fv ${D}${libdir}/snapd/system-shutdown

	# drop fish completion files
	rm -rfv ${D}${datadir}/fish

	# drop desktop files
	rm -rfv ${D}${datadir}/applications
}

FILES:${PN} += "                                          \
	${systemd_unitdir}/system/                        \
	${systemd_unitdir}/system-generators/             \
	${systemd_unitdir}/system-environment-generators/ \
	${nonarch_libdir}/tmpfiles.d/                     \
	${nonarch_libdir}/environment.d/                  \
	${datadir}/dbus-1/                                \
	/var/lib/snapd                                    \
	/var/snap                                         \
"
