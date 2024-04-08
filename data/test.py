'''******************************************************************************
PROGRAM: test.cpp
AUTHER: Mitsuki Ishiyama
DATE: 2024/04/09
Think a Bit, Code a Bit, Test a Bit
******************************************************************************'''

import os
import random
import numpy as np

extension = ".dat"
dir_name = "test_data"
output_data_file01 = "test_python"
write_file01 = os.path.join(dir_name, output_data_file01 + extension)

'''**************************************************************************'''

if not os.path.exists(dir_name):
    os.makedirs(dir_name)

mu = 700 
variance = 8000
sigma = np.sqrt(variance) 
size = 100  # Number of random numbers to generate

# Generates random numbers that follow a normal distribution
numbers = np.random.normal(mu, sigma, size)

# Write file
with open(write_file01, 'w') as fout:
    for num in numbers:
        fout.write(f"{num}\n")

print(f"write_file01: {write_file01}")
