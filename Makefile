build:
	clang++ main.cpp `llvm-config-16 --cxxflags --ldflags --system-libs --libs all` -o main
