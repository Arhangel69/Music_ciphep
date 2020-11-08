#ifndef MYMIDI_HPP
#define MYMIDI_HPP
#include <fstream>
#include <string>

namespace mymidi
{
    struct midi_note
    {
        unsigned char time_start = 0x00, time_end; //0x48 - quarter
        unsigned char note = 0x00;
        unsigned char speed_of_tap = 0x48;
    };
    struct midi_settings
    {
        /*00 ff 51 03 0b 71 b0 00 c0 4a*/
        unsigned char time_from_previous = 0x00; unsigned char meta_prefix = 0xff;
        unsigned char tempo_sign = 0x51;
        unsigned char lenght = 0x03; unsigned char fbt = 0x0b; unsigned char sbt = 0x71;
        unsigned char tbt = 0xb0; unsigned char r = 0x00;
        unsigned char t = 0xc0; unsigned char u = 0x4a;
    };
    std::ofstream& operator << (std::ofstream& file, const midi_note note);
    std::ifstream& operator >> (std::ifstream& file, midi_note note);
    bool operator == (midi_note right, midi_note left);
    bool operator != (midi_note right, midi_note left);

    class midi
    {
    private:
        std::ofstream mfout;
        const unsigned char midi_header[14] =
        {
            0x4D, 0x54, 0x68, 0x64, //MThd идентификатор
            0x00, 0x00, 0x00, 0x06, //Длина записи MThd всегда равна 6 байтам
            0x00, 0x00, //Формат данного MIDI-файла 0
            0x00, 0x01, //В данном файле содержится 1 запись типа MTrk
            0x01, 0xe0 //тиков за такт
            /*0x4D, 0x54, 0x68, 0x64, //MThd идентификатор
            0x00, 0x00, 0x00, 0x06, //Длина записи MThd всегда равна 6 байтам
            0x00, 0x00, //Формат данного MIDI-файла 0
            0x00, 0x01, //В данном файле содержится 1 запись типа MTrk
            0x00, 0x60, //Временной интервал
            0x4d, 0x54, 0x72, 0x6b, //MThd идентификатор
            0x00, 0x00, 0x00, 0x32*/
            /*0x4d, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06,
            0x00, 0x01, 0x00, 0x01, 0x01, 0xe0,
            0x4d, 0x54, 0x72, 0x6b, 0x00, 0x00, 0x00, 0x22, 0x00, 0xff,
            0x03, 0x00, 0x00, 0xc0, 0x4a, 0x00, 0xff, 0x51,
            0x03, 0x07, 0xa1, 0x20, 0x00, 0xff, 0x58, 0x04, 0x04, 0x02, 0x18, 0x08*/
        };

        unsigned char midi_mtrk_header[5] =
        {
            0x4d, 0x54, 0x72, 0x6b, //MTrk идентфикатор
        };

        unsigned char midi_end[5] =
        {
            /*0x00*/0x54, 0xff, 0x2f ,0x00
        };
    public:
        midi(const std::string path = "/home/user/", const std::string filename = "midi.mid");
        ~midi();
        void set_midi_settings();
        void set_midi_note(const midi_note note);
        unsigned char get_time(const mymidi::midi_note note);
        void set_midi_header();
        void set_midi_mtrk_header();
        void set_midi_mtrk_lenght(std::ifstream &file);
        void set_midi_end();
        void get_midi_track();
    };
}
#endif // MYMIDI_HPP
