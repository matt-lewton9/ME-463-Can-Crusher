%% DRV8825 Stepper Control with Arduino Mega
% Make sure Arduino Support Package is installed

% Connect to Arduino
%a = arduino('COM3', 'Mega2560');   % change COM port if needed

% Pin assignments
stepPin = 'D53';
dirPin  = 'D52';
enPin   = 'D6';   % optional

% Configure pins
configurePin(a, stepPin, 'DigitalOutput');
configurePin(a, dirPin,  'DigitalOutput');
configurePin(a, enPin,   'DigitalOutput');

% Enable driver (LOW = enabled on DRV8825)
writeDigitalPin(a, enPin, 0);

% Motion parameters
steps = 1000;        % number of steps to move
stepDelay = 0.01;   % delay between steps (1 ms ≈ 1000 steps/sec)
direction = 1;       % 1 = CW, 0 = CCW

% Set direction
writeDigitalPin(a, dirPin, direction);

% Generate step pulses
for i = 1:steps
    writeDigitalPin(a, stepPin, 1);
    pause(stepDelay);
    writeDigitalPin(a, stepPin, 0);
    pause(stepDelay);
end

% Optional: Disable motor
writeDigitalPin(a, enPin, 1);

disp("Done.");