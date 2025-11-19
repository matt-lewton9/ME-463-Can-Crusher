function drive_steppers(s, step_dir, steps_commanded)
% commands stepper motors to move 

write(s,"2","uint8"); %poke arduino
read(s,1,"uint8");

m1_dir = step_dir(1);
m1_steps = steps_commanded(1);
m2_dir = step_dir(2);
m2_steps = steps_commanded(2);
m3_dir = step_dir(3);
m3_steps = steps_commanded(3);

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