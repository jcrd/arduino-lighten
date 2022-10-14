import time

import hid

vid = 0x239A
pid = 0x8111

with hid.Device(vid, pid) as dev:
    while True:
        print("Getting input report...")
        d = dev.get_input_report(0, 16)
        # Exclude report ID in first byte.
        print(d[1:].decode())
        time.sleep(1)
