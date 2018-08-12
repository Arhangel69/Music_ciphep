#include "mc_pr/mymidi.hpp"
#include <iostream>

namespace mymidi
{
    std::ofstream& operator << (std::ofstream& file, const midi_note note)
    {
        unsigned char start = 0x90;
        unsigned char end = 0x80;
        file<<note.time_start;
        file<<start;
        file<<note.note<<note.speed_of_tap;
        file<<note.time_end;
        file<<end;
        file<<note.note<<note.speed_of_tap;
        return file;
    }

    std::ifstream& operator >> (std::ifstream& file, midi_note note)
    {
        unsigned char start = 0x90;
        unsigned char end = 0x80;
        file>>note.time_start;
        file>>start;
        file>>note.note>>note.speed_of_tap;
        file>>note.time_end;
        file>>end;
        file>>note.note>>note.speed_of_tap;
        return file;
    }

    bool operator == (midi_note right, midi_note left)
    {
        if (right.time_start != left.time_start) return false;
        if (right.time_end != left.time_end) return false;
        if (right.note != left.note) return false;
        if (right.speed_of_tap != left.speed_of_tap) return false;
        return true;
    }

    bool operator != (midi_note right, midi_note left)
    {
        if ((right.time_start == left.time_start)&&
                (right.time_end == left.time_end)&&
                (right.note == left.note)&&
                (right.speed_of_tap == left.speed_of_tap))
                return false;
        return true;
    }

    midi::midi(const std::string path, const std::string filename)
    {
        mfout.open(path+filename);
    }

    midi::~midi()
    {
        if (mfout.is_open()) mfout.close();
    }

    unsigned char midi::get_time(const mymidi::midi_note note)
    {
        return note.time_end;
    }

    void midi::set_midi_note(const mymidi::midi_note note)
    {
        //mymidi::midi_note ins_note;
        //ins_note = note;
        /*std::size_t ts = static_cast <std::size_t> (note.time_start);
        std::size_t te = static_cast <std::size_t> (note.time_end);
        std::size_t tm = static_cast <std::size_t> (time);
        ts+=tm;
        te+=tm;
        ins_note.time_start = static_cast <unsigned char> (ts);
        ins_note.time_end = static_cast <unsigned char> (te);*/
        unsigned char start = 0x90;
        unsigned char end = 0x80;
        //ins_note.time_start = note.time_start;
        //ins_note.time_end = note.time_end;
        mfout<<note.time_start;
        mfout<<start;
        mfout<<note.note<<note.speed_of_tap;
        mfout<<note.time_end;
        mfout<<end;
        mfout<<note.note<<note.speed_of_tap;
        //return ins_note.time_end;
    }

    void midi::set_midi_settings() //bpm = 60 000 000 / fbt sbt tbt
    {
        mymidi::midi_settings settings;
        mfout<<settings.time_from_previous<<settings.meta_prefix<<
               settings.tempo_sign<<settings.lenght<<
               settings.fbt<<settings.sbt<<
               settings.tbt<<settings.r<<
               settings.t<<settings.u;
    }

    void midi::set_midi_header()
    {
        for (std::size_t i = 0; i < 14; i++)
        {
            mfout<<midi_header[i];
        }
    }

    void midi::set_midi_mtrk_header()
    {
        for (std::size_t i = 0; i < 4; i++)
        {
            mfout<<midi_mtrk_header[i];
        }
    }

    void midi::set_midi_mtrk_lenght(std::ifstream &file)
    {
        //unsigned char lenght = 0x0e;
        unsigned char drop;
        //unsigned char hex_zero = 0x00;
        int lenght = 14;
        unsigned char drop_len = 0x00;
        unsigned char lenght1 = 0x0e;
        unsigned char lenght2 = 0x00;
        unsigned char lenght3 = 0x00;
        unsigned char lenght4 = 0x00;
        std::ofstream debug;
        debug.open("/home/user/debug.txt");
        while (file>>drop)
        {
            drop_len = lenght1 + 0x08;
            //if ((lenght1+0x07)<lenght1)
            if (drop_len<lenght1)
            {
                lenght1 = (0xff-lenght1);
                drop_len = lenght2 + 0x01;
                if (drop_len<lenght2)
                {
                    lenght2 = 0x00;
                    drop_len = lenght3 + 0x01;
                    if (drop_len<lenght3)
                    {
                        lenght3 = 0x00;
                        drop_len = lenght4 + 0x01;
                        if (drop_len<lenght4)
                        {
                            lenght4 = 0x00;
                        }
                        else lenght4+=0x01;
                    }
                    else lenght3+=0x01;
                }
                else lenght2+=0x01;
                lenght += 8;
                debug<<std::dec<<lenght;
                debug<<std::hex<<static_cast <int>(lenght2)<<" + "<<static_cast <int>(lenght1)<<'\n';
                /*if ((lenght2+0x08)<lenght2)
                {
                    lenght2 = (0xff-lenght2);
                    if ((lenght3+0x08)<lenght3)
                    {
                        lenght3 = (0xff-lenght3);
                        if ((lenght4+0x08)<lenght4)
                        {
                            lenght4 = (0xff-lenght4);
                        }
                        else lenght4+=0x01;
                    }
                    else lenght3+=0x01;
                }
                else lenght2+=0x01;*/
            }
            else
            {
                lenght1+=0x08;
                lenght+=8;
                debug<<std::dec<<lenght<<" - ";
                debug<<std::hex<<static_cast <int>(lenght1)<<'\n';
            }
            drop_len = 0x00;
            /*if (lenght1<=0xf6)
            {
                //if (drop != ' ')
                lenght1+=0x08;
            }
            else if (lenght2<=0xf7)
            {
                if (lenght1 == 0xfe)
                {
                    lenght1 += 0x01;
                    lenght2 += 0x07;
                }
                else lenght2+=0x08;
                lenght1 = 0x00;
            }
            else if (lenght3<=0xf0)
            {
                lenght3 += 0x08;
            }
            else if (lenght4<=0xf6)
            {
                if (lenght3 == 0xfe)
                {
                    lenght3 += 0x01;
                    lenght4 += 0x07;
                }
                else lenght4 += 0x08;
            }*/
        }
        debug<<std::hex<<lenght;
        mfout<<lenght4<<lenght3<<lenght2<<lenght1;
    }

    void midi::set_midi_end()
    {
        for (std::size_t i = 0; i < 4; i++)
        {
            mfout<<midi_end[i];
        }
        mfout.close();
    }

    void midi::get_midi_track()
    {

    }
}
