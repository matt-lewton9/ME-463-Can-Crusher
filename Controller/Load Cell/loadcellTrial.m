%% loadcell_mega_manual.m
% Works on Arduino MEGA 2560
% HX711 bit-banged reading (no library needed)

clear; clc; close all;

%% ================= USER SETTINGS =================
port = "/dev/tty.usbmodem14201";     % <-- Change to your Arduino port
board = "Mega2560";                  % Arduino MEGA

dout_pin = "D27";                    % HX711 DOUT
sck_pin  = "D23";                    % HX711 SCK

CAL_FACTOR = -23000;                % Replace after calibration
N = 100;                            % Number of samples
%% ==================================================

%% -------- CONNECT TO ARDUINO ----------------------
disp("Connecting to Arduino MEGA...");
a = arduino(port, board);   % No libraries required
disp("Connected. Acquiring data...");
pause(0.5);

%% -------- PREPARE PINS ----------------------------
configurePin(a, dout_pin, "digitalInput");
configurePin(a, sck_pin,  "digitalOutput");
writeDigitalPin(a, sck_pin, 0);  % Ensure clock starts low

%% -------- READ SAMPLES -----------------------------
raw = zeros(N,1);

for i = 1:N
    
    value = 0;
    for b = 1:24
        writeDigitalPin(a, sck_pin, 1);
        value = bitshift(value, 1) + readDigitalPin(a, dout_pin);
        writeDigitalPin(a, sck_pin, 0);
    end
    
    % 25th pulse to set gain = 128
    writeDigitalPin(a, sck_pin, 1);
    writeDigitalPin(a, sck_pin, 0);

    % Convert 24-bit signed number
    if value > 2^23
        value = value - 2^24;
    end
    
    
    raw(i) = value * CAL_FACTOR;
    disp(value)
end

%% -------- CONVERT TO FORCE -------------------------
force = raw ./ CAL_FACTOR;

%% -------- PLOT RESULTS -----------------------------
figure;

subplot(2,1,1);
plot(raw, "LineWidth", 1.2);
title("HX711 Raw Output");
ylabel("ADC Counts");
grid on;

subplot(2,1,2);
plot(force, "LineWidth", 1.2);
title("Force");
ylabel("Force Units");
xlabel("Sample");
grid on;

disp("Done.");
