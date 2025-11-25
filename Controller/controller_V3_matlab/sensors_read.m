 function [PT1, PT2, PT3, SG1, SG2, SG3] = sensors_read(s)

write(s,"1","uint8"); % poke arduino
read(s,1,"uint8");

% read raw PTs
PT1_raw = str2num(s.readline());
PT2_raw = str2num(s.readline());
PT3_raw = str2num(s.readline());

% convert to psi
PT1 = PT1_raw / 4 / 6894.7572932;
PT2 = PT2_raw / 4 / 6894.7572932;
PT3 = PT3_raw / 4 / 6894.7572932;

% read raw SG
SG1_raw = str2num(s.readline());
SG2_raw = str2num(s.readline());
SG3_raw = str2num(s.readline());

% calibration factors
SG2_C = .802;
SG2_VE = 4.206;
SG1_C = .809; 
SG1_VE = 4.262;
SG3_C = .795;
SG3_VE = 4.171;

% convert to microstrain
SG1 = (SG1_raw * 0.02 * SG1_C / 8388607) * 4 / (2.1 * SG1_VE) * 10^6;
SG2 = (SG2_raw * 0.02 * SG2_C / 8388607) * 4 / (2.1 * SG2_VE) * 10^6;
SG3 = (SG3_raw * 0.02 * SG3_C / 8388607) * 4 / (2.1 * SG3_VE) * 10^6;
end