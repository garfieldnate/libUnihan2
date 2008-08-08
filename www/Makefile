REMOTE_SITE=shell.sourceforge.net
REMOTE_DIR=/home/groups/l/li/libunihan
REMOTE_DIR_HTDOCS=${REMOTE_DIR}/htdocs/
RSYNC_ARGS=--cvs-exclude --recursive --verbose --update --compress --exclude *.core --stats --progress --archive --copy-links
RSYNC=/usr/bin/rsync
CLEAN_FLAGS=--delete
USER=dingyichen
SSH_ARGS=-e "ssh -l ${USER}"

JS_FILES=*.js
CSS_FILES=*.css
HTML_FILES=*.html
ALL_FILES= ${JS_FILES} ${CSS_FILES} ${HTML_FILES} api

put:
	${RSYNC} ${RSYNC_ARGS} ${SSH_ARGS}  ${ALL_FILES} ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS}

putClean:
	${RSYNC} --dry-run ${CLEAN_FLAGS} ${RSYNC_ARGS} ${SSH_ARGS} ../www ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS}

get:
	${RSYNC} ${RSYNC_ARGS} ${SSH_ARGS}  ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS} .
getClean:
	${RSYNC} ${CLEAN_FLAGS} ${RSYNC_ARGS} ${SSH_ARGS}  ${REMOTE_SITE}:${REMOTE_DIR_HTDOCS} ../www

