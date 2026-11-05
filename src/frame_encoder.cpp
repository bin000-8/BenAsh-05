#include "../header/frame_encoder.h"

plFrame_encoder::plFrame_encoder(size_t width, size_t height, size_t fps) {
	this->width = width;
	this->height = height;
	this->fps = fps;
}

void plFrame_encoder::start(const std::string& output_file) {
	std::string command =
        "ffmpeg -y -hide_banner -loglevel warning "
        "-f rawvideo "
        "-pixel_format rgba "
        "-video_size " + std::to_string(width) + "x" +
                          std::to_string(height) + " "
        "-framerate " + std::to_string(fps) + " "
        "-i pipe:0 "
        "-vf vflip "
        "-c:v libx264 "
        "-preset veryfast "
        "-crf 23 "
        "-pix_fmt yuv420p "
        "\"" + output_file + "\"";
    ffmpeg = _popen(command.c_str(), "wb");
}

void plFrame_encoder::write_frame(const std::vector<unsigned char>& pixels) {
    size_t written = fwrite(
        pixels.data(),
        1,
        pixels.size(),
        ffmpeg
    );
}

void plFrame_encoder::finish() {
    if (ffmpeg == nullptr) {
        return;
    }
    ffmpeg = nullptr;
}