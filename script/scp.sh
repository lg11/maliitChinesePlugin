scp ~/sb-home/workspace/maliit/src/plugin/libcuteinputmethod.so developer@192.168.2.15:/home/developer
scp -r ~/sb-home/workspace/maliit/src/qml developer@192.168.2.15:/home/developer
ssh developer@192.168.2.15 'pkill meego-im-uiserver'
