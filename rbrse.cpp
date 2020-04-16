#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
//#include <iterator>

// rbr setup extractor
// find beginning of the setup
// find end of the setup

int main(int argc, char *argv[])
{
    std::ifstream repfile;
    std::ofstream setfile;
    std::streampos size;
    std::vector<char> buffer;
    std::ptrdiff_t start_pos;
    std::ptrdiff_t end_pos;
    std::string repname;
    std::string setname;

    std::vector<char> wanted_start{'(', '(', '\"'};
    std::vector<char> wanted_end{')', '\n', ' ', ')', ')'};

    std::cout << "RBR Setup Extractor \n";
    std::cout << "https://github.com/wbsth/rbr-setup-extractor\n";

    // check for proper number of args
    if(argc != 2){
        std::cout << "Error - proper usage: extractor.exe <replay_file_path>\n";
    }
    else{
        // get the file names
        repname = argv[1];
        setname = repname.substr(0, repname.find_last_of("."));

        // open replay file (binary mode, pos to end of file)
        repfile.open(repname, std::ios::binary | std::ios::ate);
        if (repfile.is_open())
        {
            std::cout << "Replay loaded\n";
            // get replay file size
            size = repfile.tellg();

            // move pos back to 0
            repfile.seekg(0, std::ios::beg);

            // resize buffer according to the size of the rep, loading data into buffer
            buffer.resize(size);
            repfile.read(buffer.data(), size);

            // look for start and end of the setup 
            auto set_beg = std::search(buffer.begin(), buffer.end(), wanted_start.begin(), wanted_start.end());
            auto set_end = std::search(buffer.begin(), buffer.end(), wanted_end.begin(), wanted_end.end());

            // if start and end of the setup were found 
            if (true) //set_beg != buffer.end() && set_end != buffer.end()
            {
                // calculate vector indexes of the begging and end of the setup
                start_pos = std::distance(buffer.begin(), set_beg);
                end_pos = std::distance(buffer.begin(), set_end) + wanted_end.size();

                // open output file and write setup to it
                setfile.open(setname + ".lsp");
                setfile.write(&buffer[start_pos], end_pos - start_pos);
                std::cout << "Setup extracted as " << setname << ".lsp" << std::endl;
                setfile.close();
            }
            repfile.close();
        }
        else{
            std::cout << "Error during loading replay file\n";
        }
    }
    system("pause");
    return 0;
}