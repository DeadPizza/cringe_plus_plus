all: app/FuncAsMethod app/ShittyHooking app/ShittyHookingMethod

app/%: src/%.cpp
	g++ -O0 $^ -o $@