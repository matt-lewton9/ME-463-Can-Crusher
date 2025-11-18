clc;
% clear;

% s = serialport("COM6", 115200);

while(1)
    [PT1 PT2 PT3] = sensors_read(s)
    pause(0.1)
end


