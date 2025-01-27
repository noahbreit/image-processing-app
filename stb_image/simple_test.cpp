#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>
#include "image.h"

// Include your image loading and saving functions here
// (The code from the previous response with loadImage and saveImage functions)

// Simple test framework
#define TEST(name) void name()
#define ASSERT(condition) do { if (!(condition)) throw std::runtime_error("Assertion failed: " #condition); } while(0)

// Test cases
TEST(test_load_and_save_image) {
    const char* testImagePath = "test_image.png";
    const char* outputImagePath = "output_image.png";

    // Load the test image
    auto image = loadImage(testImagePath);
    ASSERT(!image.empty());

    // Save the loaded image
    bool saveResult = saveImage(outputImagePath, image);
    ASSERT(saveResult);

    // Reload the saved image and compare
    auto reloadedImage = loadImage(outputImagePath);
    ASSERT(!reloadedImage.empty());
    ASSERT(image.size() == reloadedImage.size());
    ASSERT(image[0].size() == reloadedImage[0].size());

    // Compare pixel values
    for (size_t y = 0; y < image.size(); ++y) {
        for (size_t x = 0; x < image[y].size(); ++x) {
            ASSERT(memcmp(&image[y][x], &reloadedImage[y][x], sizeof(Pixel)) == 0);
        }
    }
}

TEST(test_load_non_existent_image) {
    auto image = loadImage("non_existent_image.png");
    ASSERT(image.empty());
}

TEST(test_save_image_to_invalid_path) {
    std::vector<std::vector<Pixel>> dummyImage(10, std::vector<Pixel>(10, {255, 0, 0, 255}));
    bool saveResult = saveImage("/invalid/path/image.png", dummyImage);
    ASSERT(!saveResult);
}

// Test runner
void run_tests() {
    std::vector<std::pair<const char*, void(*)()>> tests = {
        {"Load and save image", test_load_and_save_image},
        {"Load non-existent image", test_load_non_existent_image},
        {"Save image to invalid path", test_save_image_to_invalid_path}
    };

    int passed = 0;
    int failed = 0;

    for (const auto& test : tests) {
        try {
            std::cout << "Running test: " << test.first << "... ";
            test.second();
            std::cout << "PASSED" << std::endl;
            passed++;
        } catch (const std::exception& e) {
            std::cout << "FAILED" << std::endl;
            std::cout << "Error: " << e.what() << std::endl;
            failed++;
        }
    }

    std::cout << "\nTest summary:" << std::endl;
    std::cout << "Passed: " << passed << std::endl;
    std::cout << "Failed: " << failed << std::endl;
}

int main() {
    run_tests();
    return 0;
}
