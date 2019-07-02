from PIL import Image

im = Image.open('lena.jpg')

print(im.size)
im.show()

im.save('pillow_Lena.jpg')
