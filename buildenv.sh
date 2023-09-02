#!/bin/bash

set -e

declare sdk="Timex_WA_SDK_Installer_1_18.zip"
declare c88="s5u1c88000c16.zip"
declare sdkurl="https://assets.timex.com/developer/developer_downloads/${sdk}"
declare c88url="https://web.archive.org/web/20190411141705if_/http://www.epsondevice.com/products_and_drivers/semicon/products/micro_controller/zip/${c88}"
declare tmpdir=$(mktemp -d)

mkdir -p include/asm
mkdir -p include/sys
mkdir -p bin
mkdir -p etc
mkdir -p lib
mkdir -p dist

pushd dist > /dev/null

test -e "${sdk}" || wget -O "${sdk}" "${sdkurl}"
test -e "${c88}" || wget -O "${c88}" "${c88url}"

unzip -o "${sdk}" -d "${tmpdir}"
unzip -o "${c88}" -d "${tmpdir}"

msiextract --directory "${tmpdir}" "${tmpdir}/${sdk%.*}.msi" > /dev/null
unshield -L -g "TARGET" -d "${tmpdir}" x "${tmpdir}/data1.cab" > /dev/null

popd > /dev/null

# These are windows binaries, but useful. The rest are kinda junk.
mv "${tmpdir}"/SOURCEDIR/M851/bin/PeriodicTask.exe bin/periodictask.exe
mv "${tmpdir}"/SOURCEDIR/M851/bin/WristAppDL.exe bin/wristappdl.exe
mv "${tmpdir}"/SOURCEDIR/M851/bin/tucp.dll bin/tucp.dll

# toolchain
mv "${tmpdir}"/target/bin/ar88.exe  bin/    # archiver
mv "${tmpdir}"/target/bin/as88.exe  bin/    # assembler
mv "${tmpdir}"/target/bin/c88.exe   bin/    # compiler
mv "${tmpdir}"/target/bin/lc88.exe  bin/    # locator
mv "${tmpdir}"/target/bin/lk88.exe  bin/    # linker
mv "${tmpdir}"/target/bin/pr88.exe  bin/    # objdump
mv "${tmpdir}"/target/bin/sy88.exe  bin/    # nm

# This just generates assembler header files
mv "${tmpdir}"/SOURCEDIR/M851/bin/MakeEqu.exe bin/makeequ.exe

# locator files
mv "${tmpdir}"/target/dev/88349/s1c88349.mem  etc/
mv "${tmpdir}"/target/dev/88349/s1c88349.cpu  etc/

# c runtime
mv "${tmpdir}"/target/lib/src/*.{asm,c} lib/

# headers
mv "${tmpdir}"/SOURCEDIR/M851/include/*.h include/asm/
mv "${tmpdir}"/target/include/*.h include/sys/

# fixup perms for wsl
chmod 755 bin/*.exe

rm -rf "${tmpdir}"
