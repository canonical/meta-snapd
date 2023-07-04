PR = "r0"

SRC_URI = "git://github.com/snapcore/snapd.git;protocol=https;branch=release/2.58;destsuffix=git/"

PV = "2.58.3+git${SRCPV}"
S = "${WORKDIR}/git"

SRCREV = "6c067a778203ac0696084bf2b42bbf46ef35706a"

DEFAULT_PREFERENCE ??= "-1"

# Allow fetching dependencies during compilation.
# Normally they are a part of the tarball
do_compile[network] = "1"
