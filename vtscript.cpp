

int main(int argc, char* argv[])
{
	if (argc == 1) {
		//repl
	}
	else if (argc == 2) {
		//read from file
	}
	else if (argc == 3) {
		if (argv[1] == "-e")
			eval(parse(argv[2]));
	}
	else {
		//invalid arguments
	}

}