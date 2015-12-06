#!/bin/bash

version="0.1.`git rev-list HEAD --count`"
name="inventory-files"

echo $version > version

# remove old deb package
find . -name "*.deb" -delete

# clear old lintian log
echo "" > "lintian.log"

rm -rf deb-pkg_create
mkdir deb-pkg_create
cp -R deb-pkg/* deb-pkg_create/

cd deb-pkg_create

find -type f | grep -re ~$ | while read f; do rm -rf "$f"; done

if [ ! -d "usr" ]; then
	mkdir "usr"
fi

if [ ! -d "usr/bin" ]; then
	mkdir "usr/bin"
fi

if [ ! -d "usr/share" ]; then
	mkdir "usr/share"
fi

if [ ! -d "usr/share/doc" ]; then
	mkdir "usr/share/doc"
fi

if [ ! -d "usr/share/doc/inventory-files" ]; then
	mkdir "usr/share/doc/inventory-files"
fi

if [ ! -d "usr/share/inventory-files" ]; then
	mkdir "usr/share/inventory-files"
fi

if [ ! -d "usr/share/inventory-files/libs" ]; then
	mkdir "usr/share/inventory-files/libs"
fi

cd ../../
	qmake && make

if [ ! -f "inventory-files.bin" ]; then
	echo "Could not build elf file"
	exit;
fi

strip -S -o deb/deb-pkg_create/usr/bin/inventory-files inventory-files.bin

cd deb/deb-pkg_create

cp ../../LICENSE usr/share/doc/inventory-files/copyright

find usr/share/inventory-files/ -name *~  | while read f; do  rm "$f"; done
find usr/share/inventory-files/ -name .gitignore  | while read f; do  rm "$f"; done

# change log
echo "$name ($version) unstable; urgency=low" > usr/share/doc/inventory-files/changelog.Debian
echo "" >> usr/share/doc/inventory-files/changelog.Debian

git log --oneline | while read line
do
	echo "  * $line " >> usr/share/doc/inventory-files/changelog.Debian
done
echo "" >> usr/share/doc/inventory-files/changelog.Debian
echo " -- Evgenii Sopov <mrseakg@gmail.com> `date --rfc-2822` " >> usr/share/doc/inventory-files/changelog.Debian
echo "" >> usr/share/doc/inventory-files/changelog.Debian

gzip -9 usr/share/doc/inventory-files/changelog.Debian

# todo manual
# gzip -9 "usr/share/man/man1/inventory-files.1"

# help: https://www.debian.org/doc/manuals/maint-guide/dreq.ru.html

if [ ! -d "DEBIAN" ]; then
	mkdir "DEBIAN"
fi

# config files
# echo "/etc/bottle/attachments.properties" >> DEBIAN/conffiles

# control
# todo section ???
# $ objdump -p ../../inventory-files.bin | grep NEEDED
# NEEDED               libQt5Widgets.so.5
# NEEDED               libQt5Sql.so.5
# NEEDED               libQt5Gui.so.5
# NEEDED               libQt5Core.so.5
# NEEDED               libstdc++.so.6
# NEEDED               libgcc_s.so.1
# NEEDED               libc.so.6

# dpkg -S libQt5Widgets.so.5



size=($(du -s ./))
size=${size[0]}
echo "Source: $name
Section: utils
Priority: optional
Maintainer: Evgenii Sopov <mrseakg@gmail.com>
Depends: libqt5widgets5:i386, libqt5sql5:i386, libqt5gui5:i386, libqt5core5a:i386, libstdc++6:i386, libgcc1:i386, libc6:i386
Version: $version
Installed-Size: $size
Homepage: http://inventory-files.sea-kg.com
Package: $name
Architecture: i386
Description: Applciation for inventory files
 Application has some gui for inventory files, and search by them.
" > DEBIAN/control

# create md5sums
echo -n "" > DEBIAN/md5sums
find "." -type f | while read f; do
	md5sum "$f" >> DEBIAN/md5sums
done

find usr -type f | while read f; do  chmod 644 "$f"; done
find var -type f | while read f; do  chmod 644 "$f"; done
find DEBIAN -type f | while read f; do  chmod 644 "$f"; done

find usr -type d | while read d; do  chmod 755 "$d"; done
find var -type d | while read d; do  chmod 755 "$d"; done
find DEBIAN -type d | while read d; do  chmod 755 "$d"; done

chmod +x usr/bin/inventory-files
chmod +x DEBIAN/preinst
chmod +x DEBIAN/postinst
chmod +x DEBIAN/prerm
chmod +x DEBIAN/postrm

find usr -type f | while read f; do md5sum "$f"; done > DEBIAN/md5sums
find var -type f | while read f; do md5sum "$f"; done >> DEBIAN/md5sums

cd ..

echo "from deb-pkg_create"

#build
fakeroot dpkg-deb --build deb-pkg_create ./

# todo uncommneted:
rm -rf deb-pkg_create
rm -rf version
rm -rf lintian.log


#check
lintian *.deb > lintian.log
cat lintian.log


