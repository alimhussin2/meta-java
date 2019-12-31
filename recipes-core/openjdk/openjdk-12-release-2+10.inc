require openjdk-12-release-2+10-common.inc

# We do not yet work for aarch64, and we make sure
# to use the aarch32 port for ARMv7.
COMPATIBLE_HOST = "^(?!(aarch64)).*$"
COMPATIBLE_HOST_armv7a = "^$"
COMPATIBLE_HOST_armv7ve = "^$"

OPENJDK_CHANGESET = "7b6accc7c009"
SRC_URI[openjdk.md5sum] = "b809f90bb002472b1ad211586f0110ea"
SRC_URI[openjdk.sha256sum] = "85d7c8c0938baf05cb214ffa65d18d07027379836c221a863d84fce03801ca9b"
