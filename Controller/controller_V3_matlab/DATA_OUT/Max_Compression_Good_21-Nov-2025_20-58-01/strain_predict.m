function [e1, e2, e3] = strain_predict(F1, F2, F3)

F_compress = 2.*(F1 + F2 + F3);

A = pi*(6^2 - (5.75)^2)/4;
I = pi*(6^4 - (5.75)^4)/4;
R = 10;
E = 10*(10^6); % psi

R1 = R.*[1 0 0];
R2 = (R-.125)*[cos(2*pi/3) sin(2*pi/3) 0];
R3 = R.*[cos(4*pi/3) sin(4*pi/3) 0];

M1 = [];
M2 = [];
M3 = [];

for i = 1:numel(F1)

    M1 = [M1; cross([0 0 F1(i)], R1)];
    M2 = [M2; cross([0 0 F2(i)], R2)];
    M3 = [M3; cross([0 0 F3(i)], R3)];

end

M = M1 + M2 + M3;

M_Rs = R.* (M(:,1:2)) ./ sqrt(M(:,1).^2 + M(:,2).^2);

M_Rs(isnan(M_Rs)) = 0;

rs = [];
M_Mag = [];
e_bend = [];

for i = 1:numel(F1)

    rs = [rs; dot([-M_Rs(i,2) M_Rs(i,1)], R1(1:2))/norm(R1) dot([-M_Rs(i,2) M_Rs(i,1)], R2(1:2))/norm(R2) dot([-M_Rs(i,2) M_Rs(i,1)], R3(1:2))/norm(R3)];
    M_Mag = [M_Mag; sqrt(M(i,1).^2 + M(i,2).^2 + M(i,3).^2)];
    e_bend = [e_bend; M_Mag(i) .* rs(i,:) ./I./E];

end


e_comp = F_compress./A./E;


e1 = e_comp + e_bend(:,1);
e2 = e_comp + e_bend(:,2);
e3 = e_comp + e_bend(:,3);

end