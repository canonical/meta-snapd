inherit go-mod

GO_IMPORT = "github.com/snapcore/snapd"

# disable shared runtime for x86
# https://forum.snapcraft.io/t/yocto-rocko-core-snap-panic/3261
# GO_DYNLINK is set with arch overrides in goarch.bbclass
GO_DYNLINK:x86 = ""
GO_DYNLINK:x86-64 = ""
GO_DYNLINK:arm = ""
GO_DYNLINK:aarch64 = ""
# modules are vendored in the release tarball.
GOBUILDFLAGS:append = " -mod=vendor"

# tags to disable unnecessary functionality:
# nosecboot  - disable secboot support, only useful for Ubuntu Core
# nomanagers - disable the managers code which could have been be imported but
#              isn't useful in binaries that aren't actual snapd daemon binary
GO_BUILD_TAGS_snapd = "nosecboot"
GO_BUILD_TAGS = "nosecboot nomanagers"
# GO_BUILD_TAGS is expanded by bitbake, but must be a single string when passed
# to go build -tags, hence it's single quoted where needed

# The go class does export a do_configure function, of which we need
# to change the symlink set-up, to target snapd's environment.
snapd_go_do_configure() {
	mkdir -p ${S}/src/github.com/snapcore
	ln -snf ${S} ${S}/src/${GO_IMPORT}
	go_do_configure
	# internally calls go run to generate some assets; build those helpers
	# statically with the Go internal linker, so they run on the build host
	# instead of getting the target's dynamic loader from the cross linker
	(cd ${S} ; GOARCH=${GOHOSTARCH} CGO_ENABLED=0 sh -x ./mkversion.sh ${PV})
}

snapd_go_do_compile() {
	(
		cd ${S}
		test -d vendor || ${GO} mod vendor "${@bb.utils.contains('GOBUILDFLAGS', '-modcacherw', '-modcacherw', '', d)}"
		# snapd is a multi-call binary: it is also the snap CLI and
		# snapd-apparmor, see packaging/snapd.mk
		${GO} install -tags '${GO_BUILD_TAGS_snapd}' ${GOBUILDFLAGS} github.com/snapcore/snapd/cmd/snapd
		${GO} install -tags '${GO_BUILD_TAGS}' ${GOBUILDFLAGS} github.com/snapcore/snapd/cmd/snap-seccomp
		${GO} install -tags '${GO_BUILD_TAGS}' ${GOBUILDFLAGS} github.com/snapcore/snapd/cmd/snap-failure

		# these *must* be built statically; snap-exec is a symlink to snapctl
		for prog in snap-update-ns snapctl; do
			${GO} install -tags '${GO_BUILD_TAGS}' -v \
			      -ldflags="${GO_RPATH} -linkmode=external -extldflags '${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS} ${GO_RPATH_LINK} ${LDFLAGS} -static'" \
			      -trimpath \
			      "${@bb.utils.contains('GOBUILDFLAGS', '-mod=vendor', '-mod=vendor', '', d)}" \
			      "${@bb.utils.contains('GOBUILDFLAGS', '-modcacherw', '-modcacherw', '', d)}" \
			      github.com/snapcore/snapd/cmd/$prog
		done
	)
}

snapd_go_install() {
	install -m 0755 ${B}/${GO_BUILD_BINDIR}/snapd ${D}${libdir}/snapd/
	install -m 0755 ${B}/${GO_BUILD_BINDIR}/snap-seccomp ${D}${libdir}/snapd/
	install -m 0755 ${B}/${GO_BUILD_BINDIR}/snap-update-ns ${D}${libdir}/snapd/
	install -m 0755 ${B}/${GO_BUILD_BINDIR}/snapctl ${D}${libdir}/snapd/
	install -m 0755 ${B}/${GO_BUILD_BINDIR}/snap-failure ${D}${libdir}/snapd/
	ln -s snapctl ${D}${libdir}/snapd/snap-exec
	# snapd-tool-wrap comes from the autotools build in cmd/
	ln -sf snapd-tool-wrap ${D}${libdir}/snapd/snapd-apparmor
	ln -s ${libdir}/snapd/snapd ${D}${bindir}/snap
	ln -s ${libdir}/snapd/snapctl ${D}${bindir}/snapctl
}

snapd_go_do_compile_snap() {
	# only build the snap tool, which is the snapd multi-call binary
	(
		cd ${S}
		${GO} install -tags '${GO_BUILD_TAGS_snapd}' ${GOBUILDFLAGS} github.com/snapcore/snapd/cmd/snapd
	)
}
