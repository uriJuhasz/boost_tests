//============================================================================
// Name        : boost_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <iomanip>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include <iostream>
using namespace std;

class Exception final : std::exception{
public:
	Exception(std::string _message) : message(_message){};
	const std::string message;
};


void test();

int main() {
	cout << "Start" << endl;
	try{
		test();
	}catch(Exception& e){
		cerr << "E: " << e.message << endl;
	}
	cout << "End" << endl;
	return 0;
}

const string rPathS = "/usr";

void testR(const path& p, int indent);
void test(){
	auto rPath = path(rPathS);
	testR(rPath,0);
}
void testR(const path& p, int indent){
	if (!exists(p))
		throw new Exception("\"" + rPathS + "\" not found");
	if (!is_directory(p))
		throw new Exception("\"" + rPathS + "\" is not a directory");

	vector<path> dirs;
	const string indentS = string(indent, ' ');
	cout << indentS << "[D]" << p << endl;
	auto perms = status(p).permissions();
	cout << indentS << "  perms=" << hex << perms << endl;
//	if (perms.)
	try{
	for (auto fi = directory_iterator(p);fi!=directory_iterator();fi++)
		if (!is_directory(*fi)){
			{}//cout << indentS << " [F]" << fi->path().filename() << endl;

		}else
			dirs.push_back(*fi);
	}catch(filesystem_error & e){
		cout << indentS << " skipped " << p << " because of " << e.what() << endl;
	}

	for (auto dir : dirs)
		testR(dir,indent+2);
    /*typedef vector<path> PathSeq;             // store paths,
    PathSeq paths;                                // so we can sort them later

    copy(directory_iterator(p), directory_iterator(), back_inserter(paths));


    sort(v.begin(), v.end());             // sort, since directory iteration
                                          // is not ordered on some file systems

    for (vec::const_iterator it (v.begin()); it != v.end(); ++it)
    {
      cout << "   " << *it << '\n';
    }*/


}
