from PIL import Image

def create_test_image(filename):
    width, height = 100, 100
    image = Image.new("RGB", (width, height))
    for x in range(width):
        for y in range(height):
            image.putpixel((x, y), (int(255 * x / width), int(255 * y / height), 128))
    image.save(filename)

create_test_image("test_image.png")
