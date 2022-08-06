import hid

vid = 0x239A
pid = 0x8111

with hid.Device(vid, pid) as dev:
    while True:
        print(dev.read(64).decode())
