PR = "r0"


BASEPV = "2.63"
SRC_URI = "git://github.com/snapcore/snapd.git;protocol=https;branch=release/${BASEPV};destsuffix=git/"
PV = "${BASEPV}+git${SRCPV}"
S = "${WORKDIR}/git"

SRCREV = "40efd81c2f35213eabf2df83fb9efabe88fa124e"

DEFAULT_PREFERENCE ??= "-1"

# Allow fetching dependencies during compilation.
# Normally they are a part of the tarball
do_compile[network] = "1"
