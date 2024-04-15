all: app/FuncAsMethod app/ShittyHooking

app/%: src/%.cpp
	g++ -O0 $^ -o $@