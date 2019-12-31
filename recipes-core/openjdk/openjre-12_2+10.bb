INC_FILE_SUFFIX = ""
INC_FILE_SUFFIX_aarch64 = "-aarch64"
INC_FILE_SUFFIX_armv7a = "-aarch32"
INC_FILE_SUFFIX_armv7ve = "-aarch32"
require openjdk-12-release-${PV}${INC_FILE_SUFFIX}.inc
require openjdk-12-cross.inc

do_install() {
    rm -rf ${D}${JRE_HOME}
    mkdir -p ${D}${JRE_HOME}
    cp -rp ${B}/images/jdk/* ${D}${JRE_HOME}
    install -d ${D}${JRE_HOME}/lib/${JDK_ARCH}
    install -m644 ${WORKDIR}/jvm.cfg  ${D}${JRE_HOME}/lib/${JDK_ARCH}/
    chown -R root:root ${D}${JRE_HOME}
    find ${D}${JRE_HOME} -name "*.debuginfo" -print0 | xargs -0 rm
}

PACKAGES_append = " \
    ${PN}-demo \
    ${PN}-source \
"

FILES_${PN}_append = "\
    ${JRE_HOME}/bin/[a-z]* \
    ${JRE_HOME}/lib/[a-z]* \
    ${JRE_HOME}/release \
    ${JRE_HOME}/conf/[a-z]* \
    ${JRE_HOME}/jmods/[a-z]* \
    ${JRE_HOME}/legal/[a-z]* \
"

FILES_${PN}-dbg_append = "\
    ${JRE_HOME}/include \
"

FILES_${PN}-demo = "\
     ${JRE_HOME}/demo \
"

RDEPENDS_${PN}-demo = " ${PN} "

FILES_${PN}-doc_append = "\
    ${JRE_HOME}/man \
"


RPROVIDES_${PN} = "java2-runtime"

inherit update-alternatives

ALTERNATIVE_${PN} = "java"
ALTERNATIVE_LINK_NAME[java] = "${bindir}/java"
ALTERNATIVE_TARGET[java] = "${JRE_HOME}/bin/java"
ALTERNATIVE_PRIORITY[java] = "100"
