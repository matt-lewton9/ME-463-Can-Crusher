% calculate total steps per motor
total_steps = sum(step_command_hist, 2);
if any(total_steps < 0)
    disp("error: total steps < 0")
    exit;
end
% drive motors
steps_driven = [0; 0; 0];
while steps_driven < total_steps
    drive = min(255, total_steps - steps_driven);
    drive_steppers(s, [1 1 1] , drive')
    steps_driven = steps_driven + drive;
    pause(0.5)
end