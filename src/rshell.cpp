#include "../header/rshellclass.h"
#include "../header/rshellutils.h"

#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	// unordered_map<string, bool> config = initConfig("../.rshellrc");

	if (argc == 1) {
		RShell shellobj = RShell(true); // (usually) Run with debug when in rshell mode, turned off for submission

		string currInput = "";
		while (currInput != "exit") {
			cout << "$ ";
			getline(cin, currInput);
			shellobj.makeCommandDeque(currInput);
			shellobj.executeCommandDeque();
			if (shellobj.EXIT_STATUS) {
				break;
			}
		}

		return 0;
	} else {
		// Run without debug when in argv mode
		RShell shellobj = RShell(false);

		vector<string> args(argv, argv+argc);
		args.erase(args.begin()); // Unfortunate inefficiency...
		string cmd = joinVector(args, ' ');
		shellobj.makeCommandDeque(cmd);
		shellobj.executeCommandDeque();
	}
}
