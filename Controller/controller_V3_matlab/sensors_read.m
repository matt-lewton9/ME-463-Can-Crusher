function [PT1, PT2, PT3, SG1, SG2, SG3] = sensors_read(s)

write(s,"1","uint8"); %poke arduino
read(s,1,"uint8");

% read PTs
PT1 = str2num(s.readline());
PT2 = str2num(s.readline());
PT3 = str2num(s.readline());

% read raw SG
SG1_raw = str2num(s.readline());
SG2_raw = str2num(s.readline());
SG3_raw = str2num(s.readline());

% float v0 = (data*.02*(C)) / (8388607); //Digital to Volts
% float del_e = ((4*del_v)/(2.1*ve));
% calibration factors
SG2_C = .802;
SG2_VE = 4.206;
SG1_C = .809; 
SG1_VE = 4.262;
SG3_C = .795;
SG3_VE = 4.171;

SG1 = (SG1_raw * 0.02 * SG1_C / 8388607) * 4 / (2.1 * SG1_VE) * 10^6;
SG2 = (SG2_raw * 0.02 * SG2_C / 8388607) * 4 / (2.1 * SG2_VE) * 10^6;
SG3 = (SG3_raw * 0.02 * SG3_C / 8388607) * 4 / (2.1 * SG3_VE) * 10^6;
end