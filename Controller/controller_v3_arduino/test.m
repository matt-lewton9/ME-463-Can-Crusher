if ~exist("s", "var")
    s = serialport("/dev/tty.usbmodem14101", 115200);
    return
end

for i = 1:1

write(s,"2","char");
read(s,1,"char")

write(s,1,"uint8");
write(s,100,"uint8");
write(s,1,"uint8");
write(s,100,"uint8");
write(s,1,"uint8");
write(s,100,"uint8");

pause(.5)

write(s,"2","char");
read(s,1,"char")
write(s,0,"uint8");
write(s,100,"uint8");
write(s,0,"uint8");
write(s,100,"uint8");
write(s,0,"uint8");
write(s,100,"uint8");

pause(.5)

end
