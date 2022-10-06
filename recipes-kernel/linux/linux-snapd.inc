FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# patches cherry-picked from Ubuntu's kernel source code at:
# https://git.launchpad.net/~ubuntu-kernel/ubuntu/+source/linux/+git/focal/log/security/apparmor?h=hwe-5.11

SRC_URI += "file://snaps.cfg \
            file://0001-UBUNTU-SAUCE-apparmor-af_unix-mediation.patch \
            file://0002-UBUNTU-SAUCE-apparmor-patch-to-provide-compatibility.patch \
            file://0003-UBUNTU-SAUCE-apparmor-fix-use-after-free-in-sk_peer_.patch \
            file://0004-UBUNTU-SAUCE-apparmor-fix-apparmor-mediating-locking.patch \
            file://0005-UBUNTU-SAUCE-apparmor-rename-kzfree-to-kfree_sensiti.patch \
            "
