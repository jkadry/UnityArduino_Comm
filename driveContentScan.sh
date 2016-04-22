#! /bin/bash
cd /volumes

# Identify Drive
echo -e "\n*****Pick a Drive from the list below*****"
select d in */; do test -n "$d" && break; echo ">>> Invalid Selection"; done
cd "$d" && pwd

# Is this the correct drive to Mount?
d=${d%/}
echo -e "\n*****Is this the correct drive '$d' to Mount? Y/N*****"

read input
	if [[ $input =~ ^([yY][eE][sS]|[yY])$ ]];
	then
		echo -e "*****Enter title name (Leave blank if unknown): *****"
		read titleName
		echo -e "\n*****Enter Barcode: *****" 
		read barcode
		tree > "$d"_Barcode_"$barcode"_ContentScan.csv
		ssconvert "$d"_Barcode_"$barcode"_ContentScan.csv "$d"_Barcode_"$barcode"_ContentScan.xls
		rm "$d"_Barcode_"$barcode"_ContentScan.csv
		cp "$d"_Barcode_"$barcode"_ContentScan.xls /../JavierK/HardDriveContentScanDocs //path to save excel file to
	else
		echo -e "\n*****Please re-run script to view options again.*****"
	fi

# Enter user email
echo -e "\n*****Enter an email to send content to.*****"
read UserEmail

# email users (create html just for email)
simpleTree=`tree -d -L 2`
echo -e "Title: $titleName \nDrive Name: $d \nBarcode: $barcode \n$simpleTree" |  mutt -a ./"$d"_Barcode_"$barcode"_ContentScan.xls -s "Drive Content Scan Complete - Barcode: $barcode" -- "$UserEmail"
echo -e "Title: $titleName \nDrive Name: $d \nBarcode: $barcode \n$simpleTree" |  mutt -a ./"$d"_Barcode_"$barcode"_ContentScan.xls -s "Drive Content Scan Complete" -- user1@paramount.com
echo -e "Title: $titleName \nDrive Name: $d \nBarcode: $barcode \n$simpleTree" |  mutt -a ./"$d"_Barcode_"$barcode"_ContentScan.xls -s "Drive Content Scan Complete" -- user2@paramount.com
echo -e "Title: $titleName \nDrive Name: $d \nBarcode: $barcode \n$simpleTree" |  mutt -a ./"$d"_Barcode_"$barcode"_ContentScan.xls -s "Drive Content Scan Complete" -- user3@paramount.com
echo -e "Email sent. Thank you! \nExiting script."