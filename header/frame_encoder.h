#ifndef FRAME_ENCODER_H
#define FRAME_ENCODER_H
#include <string>
#include <vector>

struct plFrame_encoder {
	FILE* ffmpeg = nullptr;
    size_t width;
    size_t height;
    size_t fps;
	
	plFrame_encoder(size_t width, size_t height, size_t fps);
	void start(const std::string& output_file);
    void write_frame(const std::vector<unsigned char>& pixels);
    void finish();
};
#endif