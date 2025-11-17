%% DRV8825 Stepper Control with Arduino Mega
% Make sure Arduino Support Package is installed

% Connect to Arduino
%a = arduino('COM3', 'Mega2560');   % change COM port if needed

% Pin assignments
stepPin1 = 'D53';
dirPin1  = 'D52';
stepPin2 = 'D50';
dirPin2  = 'D51';
stepPin3 = 'D49';
dirPin3  = 'D48';
enPin   = 'D6';   % optional

% Configure pins
configurePin(a, stepPin1, 'DigitalOutput');
configurePin(a, dirPin1,  'DigitalOutput');
configurePin(a, stepPin2, 'DigitalOutput');
configurePin(a, dirPin2,  'DigitalOutput');
configurePin(a, stepPin3, 'DigitalOutput');
configurePin(a, dirPin3,  'DigitalOutput');
configurePin(a, enPin,   'DigitalOutput');

% Enable driver (LOW = enabled on DRV8825)
writeDigitalPin(a, enPin, 0);

% Motion parameters
steps = 1000;        % number of steps to move
stepDelay = 0.001;   % delay between steps (1 ms ≈ 1000 steps/sec)
direction = 1;       % 1 = CW, 0 = CCW

% Set direction
writeDigitalPin(a, dirPin1, direction);
writeDigitalPin(a, dirPin2, direction);
writeDigitalPin(a, dirPin3, direction);


% Generate step pulses
for i = 1:steps
    fprintf("step %d\n", i)
    writeDigitalPin(a, stepPin1, 1);
    writeDigitalPin(a, stepPin1, 0);
    pause(stepDelay);

    writeDigitalPin(a, stepPin2, 1);
    writeDigitalPin(a, stepPin2, 0);
    pause(stepDelay);

    writeDigitalPin(a, stepPin3, 1);
    writeDigitalPin(a, stepPin3, 0);
    pause(stepDelay);

end

% Optional: Disable motor
writeDigitalPin(a, enPin, 1);

disp("Done.");