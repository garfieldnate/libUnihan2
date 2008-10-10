##
#  For format of ../DEVELOPER_SETTING file,
#  See ../CMakeList.txt.
#
include ../DEVELOPER_SETTING


REMOTE_SITE=web.sourceforge.net
REMOTE_DIR=/home/groups/l/li/libunihan
REMOTE_DIR_HTDOCS=${REMOTE_DIR}/htdocs/
RSYNC_ARGS=--cvs-exclude --recursive --verbose --update --compress --exclude *.core --stats --progress --archive --copy-links
RSYNC=/usr/bin/rsync
CLEAN_FLAGS=--delete
SSH_PASS_ARGS=-e "ssh -l ${SSH_USER},libunihan ${SSH_ARGS}"


JS_FILES=*.js
CSS_FILES=*.css
HTML_FILES=*.html
ALL_FILES= ${JS_FILES} ${CSS_FILES} ${HTML_FILES} api

put:
	${RSYNC} ${RSYNC_ARGS} ${SSH_PASS_ARGS}  ${ALL_FILES} ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS}

putClean:
	${RSYNC} --dry-run ${CLEAN_FLAGS} ${RSYNC_ARGS} ${SSH_PASS_ARGS} ../www ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS}

get:
	${RSYNC} ${RSYNC_ARGS} ${SSH_PASS_ARGS}  ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS} .
getClean:
	${RSYNC} ${CLEAN_FLAGS} ${RSYNC_ARGS} ${SSH_PASS_ARGS}  ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS} ../www

