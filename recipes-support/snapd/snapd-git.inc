PR = "r0"

SRC_URI = "git://github.com/snapcore/snapd.git;protocol=https;branch=release/2.58;destsuffix=git/"

PV = "2.60+git${SRCPV}"
S = "${WORKDIR}/git"

SRCREV = "87725a5df4574605c6acc90a4dcedab87d760e6b"

DEFAULT_PREFERENCE ??= "-1"

# Allow fetching dependencies during compilation.
# Normally they are a part of the tarball
do_compile[network] = "1"
