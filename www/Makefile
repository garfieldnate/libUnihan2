##
#  For format of ../DEVELOPER_SETTING file,
#  See ../CMakeList.txt.
#
include ../DEVELOPER_SETTING


REMOTE_SITE=web.sourceforge.net
REMOTE_DIR=/home/groups/l/li/libunihan
REMOTE_DIR_HTDOCS=${REMOTE_DIR}/htdocs/
RSYNC_ARGS=--cvs-exclude --recursive --verbose --update --compress --exclude *.core --stats --progress --archive 
RSYNC=/usr/bin/rsync
UPLOAD_FLAGS=--copy-links
DOWNLOAD_FLAGS=--keep-dirlinks
CLEAN_FLAGS=--delete
SSH_PASS_ARGS=-e "ssh -l ${SSH_USER},libunihan ${SSH_ARGS}"


JS_FILES=*.js
CSS_FILES=*.css
HTML_FILES=*.html
ALL_FILES= ${JS_FILES} ${CSS_FILES} ${HTML_FILES} api

upload:
	${RSYNC} ${RSYNC_ARGS} ${UPLOAD_FLAGS} ${SSH_PASS_ARGS}  ${ALL_FILES} ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS}

uploadClean:
	${RSYNC} ${CLEAN_FLAGS} ${RSYNC_ARGS} ${UPLOAD_FLAGS} ${SSH_PASS_ARGS} ../www ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS}

download:
	${RSYNC} ${RSYNC_ARGS} ${DOWNLOAD_FLAGS} ${SSH_PASS_ARGS}  ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS} .
downloadClean:
	${RSYNC} ${CLEAN_FLAGS} ${RSYNC_ARGS} ${DOWNLOAD_FLAGS} ${SSH_PASS_ARGS}  ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS} ../www

