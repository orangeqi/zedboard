mount /mnt/sd
cp xillydemo.bit /mnt/sd
sudo reboot
logout
unzip cordic.zip 
cd cordic_tutorial/zedboard/
make
./cordic-fpga
make fpga_batch
logout
mount /mnt/sd
cp xillydemo.bit /mnt/sd
sudo reboot
logout
ll
unzip assignment4_digitrec.zip 
cd assignment4_digitrec/
ll
cd zedboard/
make
cd ..
ll
cd amdpool
ll
make
cd ../zedboard/
ll
vi host.cpp 
vi Makefile 
logout
ll
vi zedboard
cd assignment4_digitrec/
cd zedboard/
ll
cp ../../zedboard .
ll
rm zedboard host.cpp
ll
cp ../../zedboard .
rm zedboard host.cpp
cp ../../zedboard .
mv zedboard host.cpp
ll
vi host.cpp 
cd ../../
ll
rm zedboard
ll
cd assignment4_digitrec/zedboard/
ll
make
cd ..
ll
mount /mnt/sd
cp xillydemo.bit /mn/sd
cp xillydemo.bit /mnt/sd
sudo reboot
cd assignment4_digitrec/zedboard/
make sw
make fpga
vi host.cpp
make fpga
vi host.cpp
make fpga
vi host.cpp
make fpga
vi host.cpp
make fpga
cd ..
ll
logout
ll
cd assignment4_digitrec/
ll
cd ..
cd assignment4_digitrec/amdpool/
cp ../../amdpool/digitrec.cpp .
ll
vi digitrec.cpp
vi digitrec.h
cd ..
cd zedboard/
make
:q
cp ../amdpool/digitrec.cpp .
vi digitrec.h
make
cd ..
ll
rm -r amdpool
ll
git init
git add .
git commit -m "Initialize zedboard 5 for hw4"
git config --global user.email "mq58@cornell.edu"
git config user.name "orangeqi"
git commit -m "Initialize zedboard 5 for hw4"
git remote add origin
git remote add origin https://github.com/orangeqi/zedboard.git
git remote -v
git push origin master
git remote add origin https://github.com/orangeqi/zedboard
git push origin master
git remote -v
git remote rename origin destination
git remote -v
git push origin master
git remote -v
git remote rename destination origin
git remote -v
git push origin master
