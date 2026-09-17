#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

#if defined(_WIN32) || defined(_WIN64)
#include "win_getopt.h" 
#else
#include <unistd.h>
#include <getopt.h>
#endif

#include "pontifex.h"


namespace fs = std::filesystem;


void printSinopsys(void) {
    printf("\n");
    printf( "*  Pontifex library sinopsys:\n" \
            "*  Small libs representing Bruce Schneier PONTIFEX(SOLITARE) crypto algorithm work\n" \
            "*  Inspired by NIl Stivenson CRYPTONOMICON book\n" \
            "*  This example build binary with different optargs for encrypt or decrypt some text info\n"\
    );
    printf("\n");
}

void printUsing(char* name) {
    printf( "Usage: pontifexcmd [enc option] [in option] <text/file> [out option] <text/file> [key option] <text/file> \n" \
            "Examples:\n" \
            "  *  %s -e -i <ClearText arg> -o <stdout CipherText> -k <Key arg>\n" \
            "  *  %s -e -I <ClearText filepath> -O <CipherText filepath> -K <Key filepath>\n" \
            "  *  %s -d -i <CipherText arg> -o <stdout ClearText> -k <Key arg>\n" \
            "  *  %s -d -I <CipherText filepath> -O <ClearText filepath> -K <Key filepath>\n" \
            "  *  %s -g  -k <stdout new generated key>\n" \
            "  *  %s -g  -K <Save new generated key to filepath>\n" \
            , name, name, name, name, name, name \
    );
    printf("\nBasic options:\n"\
           " -e  --enc            Encrypt proccess\n"\
           " -d  --dec            Dencrypt proccess\n"\
           " -g  --gen            Generating new key proccess\n"\
           " -i  --in             Clear or Cipher text in arg based on e\\d key\n"\
           " -I  --fin            Clear or Cipher text from filepath in arg based on e\\d key\n"\
           " -o  --out            Clear or Cipher text in arg based on e\\d key\n"\
           " -O  --fout           Clear or Cipher text from filepath in arg based on e\\d key\n"\
           " -k  --key            Key text from arg\n"\
           " -K  --fkey           Key text from filepath in arg\n"\
		   " -h  --help           Help and using examples\n"\
		   " -?  		          Sinopsys, help and using examples\n"\
    );
    printf("\n");
}

static struct option long_options[] ={
    {"enc", 	no_argument, 	   nullptr, 'e'},
	{"dec", 	no_argument,       nullptr, 'd'},
	{"gen", 	no_argument,       nullptr, 'g'},
	{"in",      required_argument, nullptr, 'i'},
	{"fin",     required_argument, nullptr, 'I'},
    {"out",     no_argument, 	   nullptr, 'o'},
    {"fout",    required_argument, nullptr, 'O'},
    {"key",     required_argument, nullptr, 'k'},
    {"fkey",    required_argument, nullptr, 'K'},
    {"sin",     no_argument,       nullptr, '?'},
    {"help",    no_argument,       nullptr, 'h'},
    {nullptr,   0,                 nullptr,  0 }
};

static bool argPass(int argc, char* argv[]) {
    int opt = 0;
	std::string key;
	std::string cleartxt;
	std::string enctxt;
    while ((opt = getopt_long(argc, argv, "?hedgio:I:O:k:K:", long_options, nullptr))) {
        switch (opt) {
            case 'e': {
				if(opt != 5) {
					printf("Argument error!\n");
					printUsing(argv[0]);
					return false;
				}
                break;
            }
            case 'd' : {
                if(opt != 5) {
					printf("Argument error!\n");
                	printUsing(argv[0]);
                    return false;
                }
                break;
            }
			case 'g' : {
                if(opt != 3) {
					printf("Argument error!\n");
                    printUsing(argv[0]);
                    return false;
                }
				break;
			}
            case 'h': {
                printUsing(argv[0]);
                return true;
            }
            case '?':
            default:{
                printSinopsys();
                printUsing(argv[0]);
                return opt == '?' ? true : false;
            }
        }
    }
    return argc;
}

bool isFileOk(const std::string& _path, const std::string& _filetype) {
	fs::path tmp_path = _path;
	if(_path.empty() || !fs::exists(_path) || tmp_path.extension() != _filetype) {
		return false;
	}
	return true;
}

bool storeToFile(const std::string& data, const std::string& filename) {
	std::ofstream out(filename,  std::ios::out | std::ios::binary);
	if(out.good()) {
		out << data;
		out.close();
		return true;
	}
	return false;
}

bool readFromFile(std::string& data, const std::string& filename) {
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	data.clear();
    if(in.good()) {
		std::ostringstream ss;
	 	ss << in.rdbuf();
		in.close();
		data = ss.str();
    }
    return !data.empty();
}


int main(int argc, char* argv[]) {   
    return argPass(argc, argv) ? 0 : -1;
}
