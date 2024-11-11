from build import motor
import numpy as np


print(motor.vec1)


can_ids = np.array([0xff,0xff,0x12], dtype=np.uint8)
motor_types = np.array([0x03,0x03,0x03], dtype=np.uint8)

m = motor.Motor("can0", can_ids,motor_types)

with np.printoptions(formatter={'int':lambda x:hex(int(x))}):
    print("can_ids:",m.can_ids)
    print("num_motors:",m.num_motors)
    print("motor_types:",m.motor_types)
