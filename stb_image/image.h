#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <vector>
#include <iostream>

struct Pixel {
    unsigned char r, g, b, a;
};

std::vector<std::vector<Pixel>> loadImage(const char* filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 4);
    
    if (!data) {
        std::cerr << "Error loading image: " << filename << std::endl;
        return {};
    }

    std::vector<std::vector<Pixel>> image(height, std::vector<Pixel>(width));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * 4;
            image[y][x] = {data[index], data[index + 1], data[index + 2], data[index + 3]};
        }
    }

    stbi_image_free(data);
    return image;
}

bool saveImage(const char* filename, const std::vector<std::vector<Pixel>>& image) {
    int height = image.size();
    int width = image[0].size();
    std::vector<unsigned char> data(width * height * 4);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * 4;
            data[index] = image[y][x].r;
            data[index + 1] = image[y][x].g;
            data[index + 2] = image[y][x].b;
            data[index + 3] = image[y][x].a;
        }
    }

    int result = stbi_write_png(filename, width, height, 4, data.data(), width * 4);
    return result != 0;
}
