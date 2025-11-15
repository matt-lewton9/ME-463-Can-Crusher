% run this before running code
%ard = arduino("/dev/tty.usbmodem14101", "Mega2560", Libraries="I2C");
%sensor = device(ard, I2CAddress="0x6D")

while 1

% write trigger bytes
writeRegister(sensor, "0x30", hex2dec("0x0A"), "uint8");

pause(0.050);

% Read
p_raw = readRegister(sensor, "0x06", 3, 'uint8');
p_H = p_raw(1);
p_M = p_raw(2);
p_L = p_raw(3);

% calculations
PMIN = 0;
PMAX = 1000*1000;

% p_adc = 2^16*p_H + 2^8*p_M + p_L;

sum = 2^16*p_H + 2^8*p_M + p_L;
if sum < 8388608
    debug = "less";
    p = sum/2^22*(PMAX-PMIN) + PMIN;
elseif sum >= 8388608
    debug = "greater";
    p = (sum-2^24)/2^22*(PMAX-PMIN) + PMIN;
end

%% Display
fprintf("---\n")
fprintf("%d %d %d\n", p_raw)

fprintf("%0.1f\n", p*0.0001450377)

pause(0.1)
end