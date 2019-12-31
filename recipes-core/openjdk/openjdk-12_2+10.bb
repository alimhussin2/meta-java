INC_FILE_SUFFIX = ""
INC_FILE_SUFFIX_aarch64 = "-aarch64"
INC_FILE_SUFFIX_armv7a = "-aarch32"
INC_FILE_SUFFIX_armv7ve = "-aarch32"
require openjdk-12-release-${PV}${INC_FILE_SUFFIX}.inc
require openjdk-12-cross.inc

do_install() {
    rm -rf ${D}${JDK_HOME}
    mkdir -p ${D}${JDK_HOME}
    cp -rp ${B}/images/jdk/* ${D}${JDK_HOME}
    install -d ${D}${JDK_HOME}/lib/${JDK_ARCH}/
    install -m644 ${WORKDIR}/jvm.cfg  ${D}${JDK_HOME}/lib/${JDK_ARCH}/
    chown -R root:root ${D}${JDK_HOME}
    find ${D}${JDK_HOME} -name "*.debuginfo" -print0 | xargs -0 rm
}

PACKAGES_append = " \
    ${PN}-demo \
    ${PN}-source \
"

FILES_${PN}_append = "\
    ${JDK_HOME}/bin/[a-z]* \
    ${JDK_HOME}/lib/[a-z]* \
    ${JDK_HOME}/LICENSE \
    ${JDK_HOME}/release \
    ${JDK_HOME}/conf/[a-z]* \
    ${JDK_HOME}/jmods/[a-z]* \
    ${JDK_HOME}/legal/[a-z]* \
"

FILES_${PN}-dev_append = "\
    ${JDK_HOME}/include \
"

FILES_${PN}-demo = " ${JDK_HOME}/demo "
RDEPENDS_${PN}-demo = " ${PN} "

FILES_${PN}-doc_append = "\
    ${JDK_HOME}/man \
"

FILES_${PN}-source = " ${JDK_HOME}/src.zip "

RPROVIDES_${PN} = "java2-runtime"

inherit update-alternatives

ALTERNATIVE_PRIORITY = "100"

ALTERNATIVE_${PN} = "java javac"
ALTERNATIVE_LINK_NAME[java] = "${bindir}/java"
ALTERNATIVE_TARGET[java] = "${JDK_HOME}/bin/java"

ALTERNATIVE_LINK_NAME[javac] = "${bindir}/javac"
ALTERNATIVE_TARGET[javac] = "${JDK_HOME}/bin/javac"
