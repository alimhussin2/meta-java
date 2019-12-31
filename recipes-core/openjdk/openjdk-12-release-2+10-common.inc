PATCHES_URI = "\
    file://remove-shell-variables-from-autoheader.patch;striplevel=0 \
    file://filter-aclocal-copy-too.patch;striplevel=0 \
    file://openjdk12-find-compiler-fix-env-respect.patch;striplevel=0 \
    file://0001-fix-stringop-truncate-gcc8.patch;striplevel=0 \
    file://0002-fix-stringop-truncate-gcc8.patch;striplevel=0 \
"

# Name of the directory containing the compiled output
BUILD_DIR = "openjdk.build"
BUILD_DIR_ECJ = "openjdk.build-ecj"

# Force arm mode for now
ARM_INSTRUCTION_SET_armv4t = "ARM"

# WORKAROUND: disable the "specified bound depends on the length of the source argument"
# compiler error on gcc8
BUILD_CFLAGS_append = " -Wno-error=stringop-overflow"
TARGET_CFLAGS_append = " -Wno-error=stringop-overflow"

# Enable zero mode for arm based builds, as normal hotspot fails to build
PACKAGECONFIG_append_armv4 = " zero"
PACKAGECONFIG_append_armv5 = " zero"
PACKAGECONFIG_append_armv6 = " zero"

OPENJDK_ARCH_PORT = "jdk-updates"
OPENJDK_ARCH_PORT_aarch64 = "aarch64-port"
OPENJDK_ARCH_PORT_armv7a = "aarch32-port"
OPENJDK_ARCH_PORT_armv7ve = "aarch32-port"
OPENJDK_HG_U = "jdk12u"
OPENJDK_HG_URL = "http://hg.openjdk.java.net/${OPENJDK_ARCH_PORT}/${OPENJDK_HG_U}"

OPENJDK_FILE = "${OPENJDK_CHANGESET}.tar.bz2"
OPENJDK_FILE_LOCAL = "openjdk12-${PV}-jdk12u-${OPENJDK_FILE}"
OPENJDK_URI = "${OPENJDK_HG_URL}/archive/${OPENJDK_FILE};downloadfilename=${OPENJDK_FILE_LOCAL};name=openjdk"
