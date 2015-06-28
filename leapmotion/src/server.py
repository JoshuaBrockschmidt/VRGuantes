# This script recieves data from the Leap Motion Controller, interprets it, and
# sends the coordinates of a red dot to a client.

import ctypes
import os, sys, inspect
src_dir = os.path.dirname(inspect.getfile(inspect.currentframe()))
arch_dir = '../lib/x64' if sys.maxsize > 2**32 else '../lib/x86'
sys.path.insert(0, os.path.abspath(os.path.join(src_dir, arch_dir)))
import Leap

class CustomListener(Leap.Listener):
    def on_init(self, ctrl):
        print "Initialized"

    def on_connect(self, ctrl):
        print "Connected"

    def on_disconnect(self, ctrl):
        print "Disconnected"

    def on_images(self, ctrl):
        print "Image gotten"
        print ctrl.images[0].data
        sys.exit()

    def on_frame(self, ctrl):
        print "Frame gotten"
        frame = ctrl.frame()
        img = frame.images[0]
        if img.is_valid:
            array_def = ctypes.c_ubyte * img.width * img.height
            array_data = array_def.from_address(int(img.data_pointer))
            print("Worked?")
            os._exit(1)

def main():
    ctrl = Leap.Controller()
    print ctrl.is_policy_set(Leap.Controller.POLICY_IMAGES)
    print ctrl.is_policy_set(Leap.Controller.POLICY_BACKGROUND_FRAMES)
    print ctrl.is_policy_set(Leap.Controller.POLICY_OPTIMIZE_HMD)
    ctrl.set_policy(Leap.Controller.POLICY_BACKGROUND_FRAMES)
    ctrl.set_policy(Leap.Controller.POLICY_IMAGES)
    ctrl.set_policy(Leap.Controller.POLICY_OPTIMIZE_HMD)
    print ctrl.is_policy_set(Leap.Controller.POLICY_IMAGES)
    print ctrl.is_policy_set(Leap.Controller.POLICY_BACKGROUND_FRAMES)
    print ctrl.is_policy_set(Leap.Controller.POLICY_OPTIMIZE_HMD)
    lstn = CustomListener()
    ctrl.add_listener(lstn)

    print "Press Enter to quit..."
    try:
        sys.stdin.readline()
    except KeyboardInterrupt:
        pass
    finally:
        ctrl.remove_listener(lstn)
        print("Program terminated")

main()
