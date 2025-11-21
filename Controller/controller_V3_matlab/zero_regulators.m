% calculate total steps per motor
total_steps = sum(step_command_hist, 2)';
if any(total_steps < 0)
    disp("error: total steps < 0")
    exit;
end
% drive motors
while total_steps ~= [0; 0; 0;]

    drive_steppers(s, [1 1 1] )

end