# compile and run all note all contains name of each part that we want to run
all: main clean

#code for cleaning the previous stuffs if exists
clean:
	rm -f mygit
	rm -f -r .init

# compile and run partwise 
main:
	g++ -o mygit main.cpp -lpthread -lssl -lcrypto -lz


