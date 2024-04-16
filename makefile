all: app/FuncAsMethod app/ShittyHooking app/ShittyHookingMethod app/WhoIsCalling

app/%: src/%.cpp
	g++ -O0 $^ -o $@