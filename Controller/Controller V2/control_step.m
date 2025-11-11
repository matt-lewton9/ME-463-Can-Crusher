function [motors] = control_step(current_P, target_P)
    deadband = 1;

    % motor 1
    if current_P(1) < target_P(1) - deadband
        M1 = 1;
    elseif current_P(1) > target_P(1) + deadband
        M1 = -1;
    else
        M1 = 0;
    end

    % motor 2
    if current_P(2) < target_P(2) - deadband
        M2 = 1;
    elseif current_P(2) > target_P(2) + deadband
        M2 = -1;
    else
        M2 = 0;
    end

    % motor 3
    if current_P(3) < target_P(3) - deadband
        M3 = 1;
    elseif current_P(3) > target_P(3) + deadband
        M3 = -1;
    else
        M3 = 0;
    end

    % output
    motors = [M1 M2 M3];
end