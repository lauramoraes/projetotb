#!/bin/sh

PROJECT_ROOT=$(pwd)
PATIENTS_FILE_NAME=$(pwd)/xml/pacientesGuadalupe.xml
TIMESTAMP=$(date +%F_%H-%M-%S)
BACKUP_DIR=$(pwd)/backup
TMPDIR=$(mktemp -t -d guadalupe.XXXXXXXXXX)
BACKUP_NAME=Guadalupe_${TIMESTAMP}_backup

cd $TMPDIR 

cp $PATIENTS_FILE_NAME $BACKUP_NAME.xml
sha256sum $BACKUP_NAME.xml > $BACKUP_NAME.sha256
tar jcf $BACKUP_DIR/$BACKUP_NAME.tar.bz2 .

cd $PROJECT_ROOT

rm -rf $TMPDIR

echo Content-Type: application/octet-stream
echo "Content-Disposition: attachment; filename=$BACKUP_NAME.tar.bz2"
echo
cat $BACKUP_DIR/$BACKUP_NAME.tar.bz2
