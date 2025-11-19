function [PT1, PT2, PT3] = sensors_read(s)

write(s,"1","uint8"); %poke arduino
read(s,1,"uint8");

PT1 = str2num(s.readline());
PT2 = str2num(s.readline());
PT3 = str2num(s.readline());
% SG1 = str2num(s.readline());
% SG2 = str2num(s.readline());
% SG3 = str2num(s.readline());

end