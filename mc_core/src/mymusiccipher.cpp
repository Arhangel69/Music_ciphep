#include "mc_pr/mymusiccipher.hpp"
#include <random>

namespace mmc
{
    mymusiccipher::mymusiccipher()
    {

    }

    mymusiccipher::~mymusiccipher()
    {
        if (mmcin.is_open()) mmcin.close();
        if (mmcout.is_open()) mmcout.close();
    }

    int mymusiccipher::uniform_random(int min,int max)
    {
        static std::mt19937 prng(std::random_device{}());
        return std::uniform_int_distribution<>(min,max)(prng);
    }

    void mymusiccipher::keygen(std::string language)
    {
        if (language == "EN")
        {
            for (std::size_t i = 0; i < 28; i++)
            {
            regen_en:
                new_alphabet_EN[i].note = notes[uniform_random(0,20)];
                new_alphabet_EN[i].time_end = durations[uniform_random(0,2)];
                /*new_alphabet_EN[i].note = notes[rand()%21];
                new_alphabet_EN[i].time_end = durations[rand()%3];*/
                if (i>0)
                {
                    for (std::size_t j = 0; j < i-1; j++)
                    {
                        if (new_alphabet_EN[i]==new_alphabet_EN[j]) goto regen_en;
                    }
                }
            }
        }
        if (language == "RUS")
        {
            for (std::size_t i = 0; i < 33; i++)
            {
            regen_rus:
                new_alphabet_RUS[i].note = notes[rand()%14];
                new_alphabet_RUS[i].time_end = durations[rand()%3];
                for (std::size_t j =0; j < i-1; j++)
                {
                    if (new_alphabet_RUS[i]==new_alphabet_RUS[j]) goto regen_rus;
                }
            }
        }
    }

    /*void mymusiccipher::encrypt(const std::string &clearpath, const std::string &clearfilename,
                                const std::string &cipherpath, const std::string &cipherfilename,
                                const std::string &keypath, const std::string &keyfilename)
    {
        std::ofstream keyout;
        keyout.open(keypath+keyfilename);
        for (std::size_t i = 0; i<29; i++)
        {
            keyout<<alphabet_EN[i]<<" - ";
            keyout<<new_alphabet_EN[i]<<'\n';
        }
        keyout.close();
        mymidi::midi midifile(cipherpath, cipherfilename);
        midifile.set_midi_header();
        midifile.set_midi_mtrk_header();
        mmcin.open(clearpath+clearfilename);
        midifile.set_midi_mtrk_lenght(mmcin);
        mmcin.close();
        midifile.set_midi_settings();
        unsigned char character;
        //mmcout.open(cipherpath+cipherfilename);
        //while (!mmcin.eof())
        mmcin.open(clearpath+clearfilename);
        while (mmcin>>character)
        {
            //mmcin>>character;
            if ((character != ',')||(character != '.'))
            character = tolower(character);
            for (std::size_t i = 0; i < 28; i++)
            {
                if(character == alphabet_EN[i])
                {
                    midifile.set_midi_note(new_alphabet_EN[i]);
                    //time += midifile.set_midi_note(new_alphabet_EN[i], time);
                    midifile.get_time(new_alphabet_EN[i]);
                    break;
                }
            }
        }
        midifile.set_midi_end();
        mmcin.close();
        //mmcout.close();
    }*/

    void mymusiccipher::encrypt(const std::string &clearpath,
                                const std::string &cipherpath)
    {
        std::ofstream keyout;
        keyout.open("/home/user/key.kdakey");
        for (std::size_t i = 0; i<29; i++)
        {
            keyout<<new_alphabet_EN[i];
        }
        keyout.close();
        mymidi::midi midifile(cipherpath, ".mid");
        midifile.set_midi_header();
        midifile.set_midi_mtrk_header();
        mmcin.open(clearpath);
        midifile.set_midi_mtrk_lenght(mmcin);
        mmcin.close();
        midifile.set_midi_settings();
        unsigned char character;
        //mmcout.open(cipherpath+cipherfilename);
        //while (!mmcin.eof())
        mmcin.open(clearpath);
        while (mmcin>>character)
        {
            //mmcin>>character;
            if ((character != ',')||(character != '.'))
            character = tolower(character);
            for (std::size_t i = 0; i < 28; i++)
            {
                if(character == alphabet_EN[i])
                {
                    midifile.set_midi_note(new_alphabet_EN[i]);
                    //time += midifile.set_midi_note(new_alphabet_EN[i], time);
                    midifile.get_time(new_alphabet_EN[i]);
                    break;
                }
            }
        }
        midifile.set_midi_end();
        mmcin.close();
    }

    void mymusiccipher::read_key(const std::string keypath)
    {
        std::ifstream keyin;
        keyin.open(keypath);
        for (std::size_t i = 0; i<29; i++)
        {
            keyin>>new_alphabet_EN[i];
        }
        keyin.close();
    }

    void mymusiccipher::write_key(const std::string keypath, const std::string keyfilename)
    {
        std::ofstream keyout;
        keyout.open(keypath + keyfilename);
        for (std::size_t i = 0; i<29; i++)
        {
            keyout<<new_alphabet_EN[i];
        }
        keyout.close();
    }

    void mymusiccipher::decrypt(const std::string &clearpath,
                                const std::string &cipherpath)
    {

    }
}
