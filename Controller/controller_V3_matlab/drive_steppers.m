function drive_steppers(s, m1_dir, m1_steps, m2_dir, m2_steps, m3_dir, m3_steps)
% commands stepper motors to move 

write(s,"2","uint8"); %poke arduino
read(s,1,"uint8");

% write stepper commands
% clip direction to [0 1]
% clipper steps to [0 255]
write(s, clip(m1_dir, 0, 1), "uint8")
write(s, clip(m1_steps, 0, 255), "uint8")
write(s, clip(m2_dir, 0, 1), "uint8")
write(s, clip(m2_steps, 0, 255), "uint8")
write(s, clip(m3_dir, 0, 1), "uint8")
write(s, clip(m3_steps, 0, 255), "uint8")

end