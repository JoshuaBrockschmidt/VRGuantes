# This script recieves data from the Leap Motion Controller, interprets it, and
# sends the coordinates of a red dot to a client.

import ctypes, os, sys, inspect
from PIL import Image
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
        for k, img in enumerate(ctrl.images):
            if not img.is_valid:
                print "Well f***"
                continue
            imageData = ctypes.cast(
                img.data.cast().__long__(),
                ctypes.POINTER(img.width*img.height*ctypes.c_ubyte)
            ).contents
            newImg = Image.frombuffer(
                "L", (img.width, img.height),
                imageData, "raw", "L", 0, 1
            )
            newImg.save("test" + str(k) + ".png")
            print "test" + str(k) + ".png created"
        os._exit(1)

    def on_frame(self, ctrl):
        print "Frame gotten"

def main():
    ctrl = Leap.Controller()
    print("POLICY_IMAGES:            " +
          str(ctrl.is_policy_set(Leap.Controller.POLICY_IMAGES)) )
    print("POLICY_BACKGROUND_FRAMES: " +
          str(ctrl.is_policy_set(Leap.Controller.POLICY_BACKGROUND_FRAMES)) )
    print("POLICY_OPTIMIZE_HMD:      " +
          str(ctrl.is_policy_set(Leap.Controller.POLICY_OPTIMIZE_HMD)) )
    ctrl.set_policy(Leap.Controller.POLICY_BACKGROUND_FRAMES)
    ctrl.set_policy(Leap.Controller.POLICY_IMAGES)
    ctrl.set_policy(Leap.Controller.POLICY_OPTIMIZE_HMD)
    print("POLICY_IMAGES:            " +
          str(ctrl.is_policy_set(Leap.Controller.POLICY_IMAGES)) )
    print("POLICY_BACKGROUND_FRAMES: " +
          str(ctrl.is_policy_set(Leap.Controller.POLICY_BACKGROUND_FRAMES)) )
    print("POLICY_OPTIMIZE_HMD:      " +
          str(ctrl.is_policy_set(Leap.Controller.POLICY_OPTIMIZE_HMD)) )
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
