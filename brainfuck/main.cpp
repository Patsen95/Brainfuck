/*
    ########## THE BEST BRAINFUCK INTERPRETER ##########

    by Patryk Sienkiewicz (@patsen95) (C) 2021

    Under GNU license, so you can do with this anything you want, except making money <3

    Have fun and happy brainfucking! ^_^
*/

#include <iostream>
#include <string>
#include <fstream>


#define BF_VERSION "1.0_pre-alpha"


int main(int argc, char **argv)
{
    /* If someone want just to enter the program name, well... */
    if(argc < 2)
    {
        std::cerr <<
            "\nError: unrecognized or incomplete command line.\n"
            "Usage:\n"
            "\tbfi <option>\n\n"
            "Type \"help\" or \"?\" for available command list."
            << std::endl;
        return -1;
    }
    /* Instruction (for pro-players ofc) */
    if(std::string(argv[1]) == "help" || std::string(argv[1]) == "?")
    {
        std::cout <<
            "\nAvailable options:"
            "\n\thelp or ?\t\t Display this\n"
            "\tver\t\t\t Display version info\n"
            "\t-c <filename> [option]\t Execute source file\n"
            "\n\tCompilation options:\n"
            "\n\t-m <x>\t\t\t Use memory buffer with size of <x> bytes (default: 30 kB)\n"
            << std::endl;
        return 0;
    }
    if(std::string(argv[1]) == "ver")
    {
        std::cout <<
            "\nThe Best Brainfuck Compiler v" BF_VERSION
            "\nPatryk Sienkiewicz (@patsen95) (C) 2021"
            "\n\nProject link (cause why not?): https://github.com/Patsen95/Brainfuck"
            << std::endl;
        return 0;
    }
    if(std::string(argv[1]) == "-c") // Now the fun begins! TIME TO RULE THE WORLD!
    {       
        /* Default size (in bytes) of memory buffer */
        static unsigned _bSize = 30000;

        /* Probably NOT AT ALL overcomplicated way to check for an aditional argument */
        if(argc >= 4)
        {
            if(std::string(argv[3]) == "-m")
            {
                if(argc >= 5)
                {
                    std::string tmp(argv[4]);
                    int sz = std::stoi(tmp);
                    _bSize = (sz < 1 ? 30000 : sz); // Kidproof?
                }
                else
                {
                    std::cerr << "Error: value not specified." << std::endl;
                    return -1;
                }
            }
        }

        /* Loading source file (I should say "trying to load", heh) */
        std::string _filename = argv[2];
        std::ifstream fsrc;

        fsrc.open(_filename);
        if(!fsrc.is_open())
        {
            std::cerr << "Error: unable to open the file. Check paths, filenames." << std::endl;
            return -1;
        }

        /*
            Let's assume it's successfully loaded.
            Now we can get it's content, parse it and throw some crazy & evil errors! (or maybe not...)
        */
        std::string theSource;
        for(std::string line; std::getline(fsrc, line);)
        {
            theSource += line;
        }
        fsrc.close();

        /* Removing all non-brainfucky-syntax characters and whitespaces */
        const std::string _syntax = "><+-.,[]"; // PURE BRAINFUCK IN JUST ONE LINE AWWW UwU <3 !!!!!!!!!!

        theSource.erase(std::remove_if(theSource.begin(), theSource.end(), [&_syntax](const char& c) {
            return _syntax.find(c) == std::string::npos;
        }), theSource.end());
        
        /* After parsing, we're preparing the Holy Memory Buffer */
        static char* _hmb = new char[_bSize] { 0 };

        /* Memory pointer, like literally */
        unsigned ptr = 0;

        /* This little thingy will help with those '[' & ']' badboyz */
        unsigned short loops = 0;

        /* Now it's time for the GREAT BRAIN OF THIS MAGNIFICENT MACHINE!!!! */
        size_t idx = 0;
        unsigned sourceLen = theSource.length();
        while(idx < sourceLen)
        {
            switch(theSource[idx])
            {
                case '>':
                    if(ptr > _bSize)
                    {
                        std::cerr << "Error: Out of memory range!" << std::endl;
                        break;
                    }
                    ptr++;
                    break;

                case '<':
                    if(ptr < 0)
                    {
                        std::cerr << "Error: Out of memory range!" << std::endl;
                        break;
                    }
                    ptr--;
                    break;

                case '+':
                    _hmb[ptr]++;
                    break;

                case '-':
                    _hmb[ptr]--;
                    break;

                case '.':
                    std::cout << _hmb[ptr];
                    break;

                case ',':
                    std::cin >> _hmb[ptr];
                    break;

                case '[':
                    if(_hmb[ptr] == 0)
                    {
                        loops = 0;
                        idx++;
                        while(idx < sourceLen)
                        {
                            if(theSource[idx] == ']' && loops == 0)
                                break;
                            else if(theSource[idx] == '[')
                                loops++;
                            else if(theSource[idx] == ']')
                                loops--;
                            idx++;
                        }
                    }
                    break;

                case ']':
                    if(_hmb[ptr] != 0)
                    {
                        loops = 0;
                        idx--;
                        while(idx >= 0)
                        {
                            if(theSource[idx] == '[' && loops == 0)
                                break;
                            else if(theSource[idx] == ']')
                                loops++;
                            else if(theSource[idx] == '[')
                                loops--;
                            idx--;
                        }
                    }
                    break;
                    /* All the other characters are considered as a comment */
                default:
                    std::cerr << "Syntax error" << std::endl;
                    break;
            }
            idx++;
        }
        delete[] _hmb;
    }
    return 0;
}
