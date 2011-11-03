/scratchbox/login -p -d workspace/maliit/src/plugin make && \
scp ~/sb-home/workspace/maliit/src/plugin/libcuteinputmethod.so developer@192.168.20.1:/home/developer && \
scp -r ~/sb-home/workspace/maliit/src/qml developer@192.168.20.1:/home/developer && \
ssh developer@192.168.20.1 'pkill meego-im-uiserver'
