function [PT1 PT2 PT3 SG1 SG2 SG3] = sensors_read(s)

write(s,0x01,"char") %poke arduino
timer = tic;

while((read(s,1,"char") ~= 0x01) && toc(timer) <0.001)
end

PT1 = str2num(s.readline());
PT2 = str2num(s.readline());
PT3 = str2num(s.readline());
SG1 = str2num(s.readline());
SG2 = str2num(s.readline());
SG3 = str2num(s.readline());

end