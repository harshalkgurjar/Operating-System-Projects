# change this to where your npheap is.
cd kernel_module
make
sudo make install
cd ..
cd library
make
sudo make install
cd ..
sudo insmod ../501_NPHeap/kernel_module/npheap.ko
sudo chmod 777 /dev/npheap
sudo insmod kernel_module/tnpheap.ko
sudo chmod 777 /dev/tnpheap
./benchmark/benchmark 256 8192 4
cat *.log > trace
sort -n -k 3 trace > sorted_trace
./benchmark/validate 256 8192 < sorted_trace
rm -f *.log
sudo rmmod tnpheap
sudo rmmod npheap
