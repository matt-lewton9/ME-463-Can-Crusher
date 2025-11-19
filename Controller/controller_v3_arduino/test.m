if ~exist("s", "var")
    s = serialport("/dev/tty.usbmodem14101", 115200);
end
write(s,"2","char");
read(s,1,"char")
write(s,50,"uint8");
write(s,255,"uint8");
write(s,100,"uint8");