PR = "r0"


BASEPV = "2.78"
SRC_URI = "git://github.com/snapcore/snapd.git;protocol=https;branch=release/${BASEPV};destsuffix=git/"
PV = "${BASEPV}+git${SRCPV}"
S = "${UNPACKDIR}/git"

SRCREV = "00b63144e44cdb7bd059e40e947e720b942c55ec"

DEFAULT_PREFERENCE ??= "-1"

# Allow fetching dependencies during compilation.
# Normally they are a part of the tarball
do_compile[network] = "1"
