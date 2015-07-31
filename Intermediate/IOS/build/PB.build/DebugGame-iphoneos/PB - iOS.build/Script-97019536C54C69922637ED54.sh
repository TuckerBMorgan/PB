#!/bin/sh
if [ $DEPLOYMENT_LOCATION = "YES" ]
then
cp -R PB/Binaries/IOS/Payload/PB.app/ $DSTROOT/$LOCAL_APPS_DIR/PB.app
fi
