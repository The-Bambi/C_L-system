import subprocess
from os import remove
from os.path import isfile
from PIL import Image
import numpy as np

subprocess.run("./l_system")

if subprocess.CompletedProcess:
    print("Done!")
    img = Image.open("./output.bmp")
    arr = np.array(img)
    if isfile("./output_arr.npy"):
        name_number  = 1
        while isfile("./output_arr{}.npy".format(name_number)):
            name_number+=1
    else:
        name_number = ''
    np.save("output_arr{}".format(name_number),arr)
    
else:
    print("Cos poszlo nie tak...")