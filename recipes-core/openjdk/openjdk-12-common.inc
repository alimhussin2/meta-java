SUMMARY = "Java runtime based upon the OpenJDK Project"
HOMEPAGE = "http://openjdk.java.net/"
LICENSE  = "GPL-2.0-with-classpath-exception"

LIC_FILES_CHKSUM = "file://LICENSE;md5=3e0b59f8fac05c3c03d4a26bbda13f8f"

require openjdk-common.inc

AUTOTOOLS_SCRIPT_PATH = "${S}/make/autoconf"
export AUTOCONF_DIR="${AUTOTOOLS_SCRIPT_PATH}"
export TOPDIR="${S}"

FILESPATH =. "${FILE_DIRNAME}/patches-openjdk-12:"

# for weird openjdk-common.inc
S = "${WORKDIR}/${OPENJDK_HG_U}-${OPENJDK_CHANGESET}"

SRC_URI = " \
    ${OPENJDK_URI} \
    ${PATCHES_URI} \
"

def package_config_option_cleanup(d):
    distro_x11 = bb.utils.contains('DISTRO_FEATURES', 'x11', True, False, d)
    distro_alsa = bb.utils.contains('DISTRO_FEATURES', 'alsa', True, False, d)
    distro_pulseaudio = bb.utils.contains('DISTRO_FEATURES', 'pulseaudio', True, False, d)

    with_x11 = bb.utils.contains('PACKAGECONFIG', 'x11', True, False, d)
    with_cups = bb.utils.contains('PACKAGECONFIG', 'cups', True, False, d)
    with_alsa = bb.utils.contains('PACKAGECONFIG', 'alsa', True, False, d)
    with_pulseaudio = bb.utils.contains('PACKAGECONFIG', 'pulseaudio', True, False, d)

    option_headless = bb.utils.contains('PACKAGECONFIG', 'headless', True, False, d)
    option_headful = bb.utils.contains('PACKAGECONFIG', 'headful', True, False, d)
    option_soundless = bb.utils.contains('PACKAGECONFIG', 'soundless', True, False, d)

    if option_headless and option_headful:
        option_headless = False

    if option_headful and not with_x11:
        with_x11 = True

    if option_headful and not with_cups:
        with_cups = True

    if option_soundless and with_alsa:
        with_alsa = False

    if option_soundless and with_pulseaudio:
        with_pulseaudio = False

    if with_x11 and not distro_x11:
        with_x11 = False

    if with_alsa and not distro_alsa:
        with_alsa = False

    if with_pulseaudio and not distro_pulseaudio:
        with_pulseaudio = False

    if option_headful and not with_x11:
        option_headful = False

    if option_headful and not with_cups:
        option_headful = False

    if not option_headless and not with_x11:
        option_headless = True

    if not option_headless and not with_cups:
        option_headless = True

    if not option_soundless and not with_alsa:
        option_soundless = True

    if not option_soundless and not with_pulseaudio:
        option_soundless = True

    options = {'make': [], 'cpp': [], 'env': [], 'configure': ["--disable-ccache"] }

    if option_headful:
        options['configure'].append("--enable-headful")

    if option_headless:
        options['configure'].append("--disable-headful")
        options['make'].append("BUILD_HEADLESS_ONLY=1")
        options['make'].append("BUILD_HEADLESS=true")

    if option_soundless:
        options['make'].append("BUILD_SOUNDLESS_ONLY=1")

    if not with_x11:
        options['make'].append("X11_NOT_NEEDED=1")
        options['env'].append("X11_NOT_NEEDED=yes")

    if not with_cups:
        options['make'].append("CUPS_NOT_NEEDED=1")
        options['env'].append("CUPS_NOT_NEEDED=yes")

    if not with_alsa:
        options['make'].append("ALSA_NOT_NEEDED=1")
        options['env'].append("ALSA_NOT_NEEDED=yes")

    if not with_pulseaudio:
        options['make'].append("PULSE_NOT_NEEDED=1")
        options['env'].append("PULSE_NOT_NEEDED=yes")

    options = [ ' '.join(options['make']), ' '.join(options['cpp']), ' '.join(options['env']), ' '.join(options['configure']) ]

    return options

def jdk_make_options(d):
    options = package_config_option_cleanup(d)
    return options[0]

def jdk_cpp_options(d):
    options = package_config_option_cleanup(d)
    if not options[1]:
        return ""

    return " " + options[1]

def jdk_environment_options(d):
    options = package_config_option_cleanup(d)
    return options[2]

def jdk_configure_options(d):
    options = package_config_option_cleanup(d)
    return options[3]

do_configure_prepend() {
        export ${@jdk_environment_options(d)}
}

export DEBUG_BINARIES = "true"

ALTERNATIVE_PRIORITY = "50"

OPENJDK_UPDATE_VERSION = "${@d.getVar('PV').split('+')[0]}"
OPENJDK_BUILD_NUMBER = "b${@d.getVar('PV').split('+')[1]}"
EXTRA_OECONF_append = "\
        --with-build-number=${OPENJDK_BUILD_NUMBER} \
        --with-update-version=${OPENJDK_UPDATE_VERSION} \
"

# flags for -native, and for bits that need a host-tool during -cross
BUILD_CFLAGS_append = " ${@openjdk_build_helper_get_build_cflags(d)}"
BUILD_CXXFLAGS_append = " ${@openjdk_build_helper_get_build_cflags(d)}"
# flags for -cross
TARGET_CFLAGS_append = " ${@openjdk_build_helper_get_target_cflags(d)}"
TARGET_CXXFLAGS_append = " ${@openjdk_build_helper_get_target_cflags(d)}"
