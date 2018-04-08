CPP=g++
FILE=CampoMinado



all:
	$(CPP) $(FILE).cpp -o $(FILE)

clean:
	rm $(FILE)
