# compile and run all note all contains name of each part that we want to run
all: main clean
# compile and run partwise 
main:
	g++ -o mygit main.cpp -lpthread -lssl -lcrypto -lz 
# code for cleaning stuffs
# note main is variable name to run use command make main
clean:
	rm -f mygit
	rm -f -r .init

#./mygit add .
#./mygit add file1 file2
#./mygit ls-tree <hash>
