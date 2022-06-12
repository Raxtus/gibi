#include <iostream>
#include <fstream>
#include <string>

const unsigned int MB = 1024*1024;
const unsigned int PACKAGE = 16;

using namespace std;

void unify(const char *path);
void split(const char *path);

void help()
{
	cout << "To split file use -s [PATH]" << endl;
	cout << "To unify use -u [CONFIG_FILE_PATH]" << endl;
	return;
}
int main(int argc, char*argv[])
{
	if (argc == 1)
	{
		unify("config.txt");
	}
	else if (argc == 2)
	{
		split(argv[1]);
	}
	else
	{
		help();
		return -1;
	}

}


void unify(const char *path)
{
	ifstream infile;
	ofstream outfile;
	int files = 0;
	int i;
	char *buff = new char[MB*PACKAGE];
	string outputFileName;

	infile.open("config.txt");
	if (!infile.good())
	{
		cerr << "Infile couldn't be opened or doesn't exist\n";
		exit(-1);
	}
	infile >> files;
	infile >> outputFileName;
	infile.close();
	outfile.open(outputFileName.c_str(), ios::binary);

	for (i = 0; i < files ; i++)
	{
		infile.open(to_string(i).c_str(), ios::binary);
		if (!infile.good())
		{
			cerr << "Infile couldn't be opened or doesn't exist\n\n";
			exit(-1);
		}
		infile.read(buff, (MB*PACKAGE));
		outfile.write(buff, (MB*PACKAGE));
		infile.close();
	}

	infile.open(to_string(i).c_str(), ios::binary);
	if (!infile.good())
	{
		cerr << "Infile couldn't be opened or doesn't exist\n\n";
		exit(-1);
	}
	infile.seekg(0, infile.end);
	unsigned int length = infile.tellg();
	infile.seekg(0, infile.beg);
	delete[] buff;
	buff = new char[length];
	infile.read(buff, length);
	outfile.write(buff, length);
	infile.close();

	outfile.close();
}

void split(const char * path)
{
	ifstream infile;
	ofstream outfile;
	int name=0;
	char *buff = new char[MB*PACKAGE];
	int rest = 0;

	infile.open(path, ios::binary);
	if (!infile.good())
	{
		cerr << "Infile couldn't be opened or doesn't exist\n";
		exit(-1);
	}
	
	infile.seekg(0, infile.end);
	unsigned int length = infile.tellg();
	infile.seekg(0, infile.beg);
	
	rest = length % (MB*PACKAGE);
	for (name = 0; name < (length - rest) / (MB*PACKAGE); name++)
	{
		outfile.open(to_string(name).c_str(), ios::binary);
		if (!outfile.good())
		{
			cerr << "Outfile couldn't be opened or created\n";
			exit(-1);
		}
		infile.read(buff, (MB*PACKAGE));
		outfile.write(buff, (MB*PACKAGE));
		outfile.close();
	}
	delete[] buff;
	buff = new char[rest];
	outfile.open(to_string(name).c_str(), ios::binary);
	if (!outfile.good())
	{
		cerr << "Outfile couldn't be opened or created\n";
		exit(-1);
	}
	infile.read(buff, rest);
	outfile.write(buff, rest);
	outfile.close();
	infile.close();

	outfile.open("config.txt");
	if (!outfile.good())
	{
		cerr << "Outfile couldn't be opened or created\n";
		exit(-1);
	}
	outfile << name << endl;
	string edit = path;
	size_t pos = edit.find_last_of("/");
	if (pos == string::npos) pos = 0;
	outfile << edit.substr(pos, string::npos);
	outfile.close();

	
	return;	
}
