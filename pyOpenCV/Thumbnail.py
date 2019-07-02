from PIL import Image

im = Image.open('lena.jpg')

size = (512,512)
im.thumbnail(size)
im.show()

im.save('lena-thumb.jpg')
