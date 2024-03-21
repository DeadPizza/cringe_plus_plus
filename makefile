all: app/FuncAsMethod

app/%: src/%.cpp
	g++ $^ -o $@