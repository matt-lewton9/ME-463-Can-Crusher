function drive_steppers(s, Steps1, Steps2, Steps3)

write(s,"2","uint8"); %poke arduino
read(s,1,"uint8");

write(s, Steps1,"uint8")
write(s, Steps2,"uint8")
write(s, Steps3,"uint8")

end