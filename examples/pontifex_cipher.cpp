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


bool run (bool is_enc, const std::string& data, const std::string& key, ptfxcpr::PontifexCipher& handler);

void printSinopsys(void) {
    printf("\n");
    printf( "*  Pontifex library sinopsys:\n" \
            "*  Small libs representing Bruce Schneier PONTIFEX(SOLITARE) crypto algorithm work\n" \
            "*  Inspired by Nil Stivenson CRYPTONOMICON book\n" \
            "*  This example build binary with different optargs for encrypt or decrypt some text info\n"\
    );
    printf("\n");
}

void printUsing(char* name) {
    printf( "Usage: pontifexcmd [enc option] [in option] <text> [key option] <text> \n" \
            "Examples:\n" \
            "  *  %s -e -i <ClearText arg>  -k $'<Key arg>'\n" \
            "  *  %s -d -i <CipherText arg> -k $'<Key arg>'\n" \
            "  *  %s -g    <stdout new generated key>\n" \
            , name, name, name \
    );
    printf("\nBasic options:\n"\
           " -e  --enc            Encrypt proccess\n"\
           " -d  --dec            Dencrypt proccess\n"\
           " -g  --gen            Generating new key proccess\n"\
           " -i  --in             Clear or Cipher text in arg based on e\\d key\n"\
           " -k  --key            Key text from arg\n"\
		   " -h  --help           Help and using examples\n"\
		   " -?  		      Sinopsys, help and using examples\n"\
    );
    printf("\n");
}

static struct option long_options[] ={
    {"enc", 	no_argument, 	   nullptr, 'e'},
	{"dec", 	no_argument,       nullptr, 'd'},
	{"gen", 	no_argument,       nullptr, 'g'},
	{"in",      required_argument, nullptr, 'i'},
    {"key",     required_argument, nullptr, 'k'},
    {"sin",     no_argument,       nullptr, '?'},
    {"help",    no_argument,       nullptr, 'h'},
    {nullptr,   0,                 nullptr,  0 }
};

static bool argPass(int argc, char* argv[]) {
    int opt = 0;
	[[maybe_unused]]bool to_enc = false;
	std::string key;
	std::string data;
	ptfxcpr::PontifexCipher cypher;
    while ((opt = getopt_long(argc, argv, "?hedgi:k:", long_options, nullptr))) {
        switch (opt) {
            case 'e': {
				if (argc != 6) {
					std::cout << "Arguments error\n";
					printSinopsys();
                    printUsing(argv[0]);
                    return false;
				}
				to_enc = true;
                break;
            }
            case 'd': {
                  if (argc != 6) {
                      std::cout << "Arguments error\n";
                      printSinopsys();
                      printUsing(argv[0]);
                      return false;
                  }
				to_enc = false;
                break;
            }
			case 'g': {
				cypher.generateEncryptionKey();
				key = cypher.getEncriptionkey();
				std::cout << "Generated key is: " << key.c_str() << std::endl;
				return true;
			}
			case 'k': {
				key = argv[5];
				break;
			}
			case 'i': {
				data = argv[3];
				break;
			}
            case 'h': {
                printUsing(argv[0]);
                return true;
            }
            case '?': 
            default: {
				if (opt == '?') {
	                printSinopsys();
                	printUsing(argv[0]); 
					return true;
				}
				return run(to_enc, data, key, cypher);
            }
        }
    }
    return argc;
}

bool run (bool to_enc, const std::string& data, const std::string& key, ptfxcpr::PontifexCipher& handler) {
	if (data.empty()) {
		std::cout << "Error given data is empty, exiting\n";
		return false;
	}
	if (key.empty()) {
    	std::cout << "Error given data is empty, exiting\n";
        return false;
    }

	std::cout << "Start to " << (to_enc ? "encrypt" : "decrypt") << " this data: " << data << " with key: " << key << std::endl;
	if ( !handler.setEncriptionKey(key.c_str()) ) {
		std::cout << "Set encryption key is faild, exitting\n";
		return false;
	}

	std::string responsed(4096, '0');
	const unsigned char * req_ptr = reinterpret_cast<const unsigned char*> (data.data());
	unsigned char * res_ptr = reinterpret_cast<unsigned char*> (responsed.data());
	return to_enc ? handler.encryptMessage(req_ptr, res_ptr) : handler.decryptMessage(req_ptr, res_ptr);
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
	if (argc == 1) {
		std::cout << "Error given data is empty, exiting\n";
        return -1;
	}
    return argPass(argc, argv) ? 0 : -1;
}
