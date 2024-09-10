echo "*******************************"
echo "Copy udev rules for CAN2COM_HUB"
echo "///////////////////////////////"
FILE=/etc/udev/rules.d/CAN2COM_HUB.rules
if [ ! -f "$FILE" ];then
echo "Copy CAN2COM_HUB.rules"
sudo cp `rospack find xpkg_comm`/scripts/CAN2COM_HUB.rules /etc/udev/rules.d
else
echo "CAN2COM_HUB.rules existed"
fi
echo "*******************************"
echo ""
sudo service udev reload
sudo service udev restart
