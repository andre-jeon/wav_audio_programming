#include <iostream>
#include <fstream>

using namespace std;

// Riff Chunk
const string chunk_id = "RIFF";
const string chunk_size = "----"; // requires at least 4 bytes
const string format = "WAVE";

// FMT sub-chunk
const string subchunk1_id = "fmt ";
const int subchunck1_size = 16;
const int audio_format = 1;
const int num_channels = 2;
const int sample_rate = 44100;
const int byte_rate = sample_rate * num_channels * (subchunck1_size / 8);
const int block_align = num_channels * (subchunck1_size / 8);
int bits_per_sample = 16;

// Data sub-chunk
const string subchunk2_id = "data";
const string subchunk2_size = "----";

void write_as_bytes(ofstream &file, int value, int byte_size) {
    file.write(reinterpret_cast<const char*>(&value), byte_size);   
}


int main() {

    ofstream wav;
    wav.open("test.wav", ios::binary);

    if (wav.is_open()) {

        wav << chunk_id;
        wav << chunk_size;
        wav << format;

        wav << subchunk1_id;
        write_as_bytes(wav, subchunck1_size, 4);
        write_as_bytes(wav, audio_format, 2);
        write_as_bytes(wav, num_channels, 2);
        write_as_bytes(wav, sample_rate, 4);
        write_as_bytes(wav, byte_rate, 4);
        write_as_bytes(wav, block_align, 2);
        write_as_bytes(wav, bits_per_sample, 2);

        wav << subchunk2_id;
        wav << subchunk2_size;

    }

    return 0;
}