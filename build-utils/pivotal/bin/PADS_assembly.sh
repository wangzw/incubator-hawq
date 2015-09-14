#!/bin/bash
## ======================================================================

PULSE_BUILD_NUMBER=${PULSE_BUILD_NUMBER:=9999}
PADS_PUBLISH_LOCATION="${PADS_PUBLISH_LOCATION:=build@dist.greenplum.com:/data/dist/PHD/latest/}"

pushd src

BUILD_NUMBER=${PULSE_BUILD_NUMBER}

ls hawq*.rpm > /dev/null
if [ $? = 0 ]; then
	HAWQ_RPM=$( ls hawq*.rpm )
else
	echo "HAWQ rpm artifact does not exist."
	exit 2
fi

ls hawq*.tar.gz > /dev/null
if [ $? = 0 ]; then
	HAWQ_TARBALL=$( ls hawq*.tar.gz )
else
	echo "HAWQ tarball artifact does not exist."
	exit 2
fi

ls pxf/build/distributions/pxf*.rpm > /dev/null
if [ $? = 0 ]; then
	PXF_RPM=$( ls pxf/build/distributions/pxf*.rpm )
else
	echo "PXF rpm artifacts do not exist."
	exit 2
fi

ls pxf/build/distributions/pxf*.tar.gz > /dev/null
if [ $? = 0 ]; then
	PXF_TARBALL=$( ls pxf/build/distributions/pxf*.tar.gz )
else
	echo "PXF tarball artifacts do not exist."
	exit 2
fi

wget -nv http://build-prod.dh.greenplum.com/releases/tomcat/7.0.62/apache-tomcat-7.0.62.tar.gz
ls apache-tomcat*.tar.gz > /dev/null
if [ $? = 0 ]; then
	TOMCAT_TARBALL=$( ls apache-tomcat*.tar.gz )
else
	echo "Tomcat tarball aftifact does not exist."
	exit 2
fi

wget -nv http://build-prod.dh.greenplum.com/releases/tomcat/7.0.62/apache-tomcat-7.0.62.noarch.rpm
ls apache-tomcat*.rpm > /dev/null
if [ $? = 0 ]; then
	TOMCAT_RPM=$( ls apache-tomcat*.rpm )
else
	echo "Tomcat rpm artifact does not exist."
	exit 2
fi

PADS_VERSION=$( echo ${HAWQ_RPM} | sed -e 's/hawq-\([0-9]\.[0-9]\.[0-9]\.[0-9]\).*/\1/' )

PADS_TAR=PADS-${PADS_VERSION}-${BUILD_NUMBER}-${BLD_ARCH}.tar.gz

cat <<-EOF
	======================================================================
	TIMESTAMP ........ : $( date )
	PADS_VERSION ..... : ${PADS_VERSION}
	PADS_TAR ......... : ${PADS_TAR}

----------------------------------------------------------------------
Creating tarball: ${PADS_TAR}
----------------------------------------------------------------------

EOF

PADS_WORK_DIR=PADS-${PADS_VERSION}
rm -rf ${PADS_WORK_DIR}

mkdir ${PADS_WORK_DIR}

cp ${HAWQ_RPM} ${PXF_RPM} ${TOMCAT_RPM} ${PADS_WORK_DIR}

pushd ${PADS_WORK_DIR}
createrepo .
if [ $? != 0 ]; then
    echo "FATAL: createrepo failed"
    exit 1
fi

git clone git@github.com:hortonworks/phd-misc-peacock.git
cp -v phd-misc-peacock/stack-utils/setup_repo.sh .
if [ $? != 0 ]; then
    echo "FATAL: setup_repo.sh copy failed"
    exit 1
fi

rm -rf phd-misc-peacock
if [ $? != 0 ]; then
    echo "FATAL: cleanup of git repo failed"
    exit 1
fi

chmod a+x setup_repo.sh
ls -al
popd

tar zcvf ../${PADS_TAR} ${PADS_WORK_DIR}
if [ $? != 0 ]; then
    echo "FATAL: tar failed"
    exit 1
fi

popd

PADS_TAR_MD5=$( openssl dgst -md5 ${PADS_TAR} )

cat <<-EOF
	
	----------------------------------------------------------------------
	file(s):
	$( ls -al ${PADS_TAR} ${PADS_BIN_TAR} )

	PADS_TAR_MD5 ....... : ${PADS_TAR_MD5}
	======================================================================
EOF

##
## Publish artifacts?
##

if [ "${PUBLISH_HAWQ_ARTIFACTS}" = "true" ] && ( [[ "${PULSE_PROJECT}" =~ ^HAWQ-[\.0-9X]+-opt$ ]] || [[ "${PULSE_PROJECT}" =~ ^HAWQ-main-opt$ ]] || [[ "${PULSE_PROJECT}" =~ ^HAWQ-1.3.x-opt$ ]] ); then 

    GPPKGS=$( ls src/*-hawq-*.gppkg )

	cat <<-EOF
		======================================================================
		TIMESTAMP ........ : $( date )
		PADS_TAR ......... : ${PADS_TAR}
		GPPKGS ........... : ${GPPKGS}
	
		Destination(s):
		  ${PADS_PUBLISH_LOCATION}
		======================================================================
	
		----------------------------------------------------------------------
		Shipping out files:
		  scp -o StrictHostKeyChecking=no ${PADS_TAR} ${GPPKGS} ${PADS_PUBLISH_LOCATION}
		----------------------------------------------------------------------
	
	EOF
	
	scp -o StrictHostKeyChecking=no ${PADS_TAR} ${GPPKGS} ${PADS_PUBLISH_LOCATION}
	if [ $? != 0 ]; then
	    echo "FATAL: scp failed (${PADS_PUBLISH_LOCATION})"
	    exit 1
	fi
else
    echo "Publishing is disabled ({BLDWRAP_PUBLISH_ARTIFACTS})"
fi

exit 0
