#ifndef MYMUSICCIPHER_HPP
#define MYMUSICCIPHER_HPP
#include <fstream>
#include <cctype>
#include <string>
#include <cstdio>
#include <QString>
#include "mc_pr/mymidi.hpp"

namespace mmc
{
    /*std::ifstream mmcin;
    std::ofstream mmcout;*/
    //toolover need
    class mymusiccipher
    {
    private:
        std::ifstream mmcin;
        std::ofstream mmcout;
        unsigned char alphabet_EN[29] =
        {
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
            'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
            'y', 'z', ' ', ',' , '.'
        };
        unsigned char alphabet_RUS[35] =
        {
            /*'а','б','в','г','д','е','ж','з','и','й','к','л','м','н','о',
            'п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э',
            'ю','я',' ',',','.',*/
        };
        mymidi::midi_note new_alphabet_EN[29]{};
        mymidi::midi_note new_alphabet_RUS[34]{};
        unsigned char durations[3] =
        {
            0x30, 0x48, 0x24
        };
        unsigned char notes[21] =
        {
            0x30, 0x32, 0x34, 0x35, 0x37, 0x39, 0x3B,
            0x3c, 0x3e, 0x40, 0x41, 0x43, 0x45, 0x47,
            0x48, 0x4a, 0x4c, 0x4d, 0x4f, 0x51, 0x53
        };
        int uniform_random(int min,int max);
    public:
        mymusiccipher();
        ~mymusiccipher();
        void keygen(std::string language = "EN");
        void get_key();
        /*void encrypt(const std::string &clearpath = "/home/user/",
                     const std::string &clearfilename = "text.txt",
                     const std::string &cipherpath = "/home/user/",
                     const std::string &cipherfilename = ".mid",
                     const std::string &keypath = "/home/user/",
                     const std::string &keyfilename = "key.kdakey");*/
        void encrypt(const std::string &clearpath = "/home/user/",
                     const std::string &cipherpath = "/home/user/");
        void decrypt(const std::string &clearpath = "/home/user/",
                     const std::string &cipherpath = "/home/user/");
        void write_key(const std::string keypath, const std::string keyfilename);
        void read_key(const std::string keypath);
    };
}
#endif // MYMUSICCIPHER_HPP
