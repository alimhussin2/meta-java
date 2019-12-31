require openjdk-12-release-2+10-common.inc

COMPATIBLE_HOST = "^$"
COMPATIBLE_HOST_armv7a = "arm"
COMPATIBLE_HOST_armv7ve = "arm"

OPENJDK_CHANGESET = "7b6accc7c009"
SRC_URI[openjdk.md5sum] = "b809f90bb002472b1ad211586f0110ea"
SRC_URI[openjdk.sha256sum] = "85d7c8c0938baf05cb214ffa65d18d07027379836c221a863d84fce03801ca9b"

PACKAGECONFIG_append_armv7a = " client"
PACKAGECONFIG_append_armv7ve = " client"

JDK_ARCH_armv7a = "aarch32"
JDK_ARCH_armv7ve = "aarch32"
