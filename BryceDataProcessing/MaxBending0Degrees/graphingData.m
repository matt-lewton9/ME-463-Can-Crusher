PTReading = readmatrix("PT_readings.csv");
SG_Data = readmatrix("SG_readings.csv");

Piston_A =(3.776^2)*pi / 4;
I = 9.96;
A = 2.31;
d=6;
r=d/2;
YoungMod = 9900000;

strut1 = [10, 0, 0];
strut2 = [-10*cosd(30), -10*sind(30), 0];
strut3 = [10*cosd(30), -10*sind(30), 0];

F1 = -PTReading(:, 1).*Piston_A;
F2 = -PTReading(:,2).*Piston_A;
F3 = -PTReading(:,3).*Piston_A;

F1vec = [zeros(size(F1)) zeros(size(F1)) F1];
F2vec = [zeros(size(F2)) zeros(size(F2)) F2];
F3vec = [zeros(size(F3)) zeros(size(F3)) F3];

M1 = cross(repmat(strut1, size(F1,1), 1), F1vec, 2);

M = cross(repmat(strut1, size(F1,1), 1), F1vec, 2) + ...
    cross(repmat(strut2, size(F2,1), 1), F2vec, 2) + ...
    cross(repmat(strut3, size(F3,1), 1), F3vec, 2);

SigmaM = M(:, 1)+M(:, 2);
sigmaF = 2*(F1+F2+F3);
stress = -(sigmaF)/A + SigmaM.*r./I;

e = (stress/YoungMod) * 10^6;

figure;
plot(e(:,1), '-', LineWidth =2);
hold on
plot(SG_Data(:,1), 'r-',LineWidth = 2);
legend("Theoretical(PT Readings)", "Experimental", "Location", "northwest")
xlabel('Time (s)');
ylabel('Strain');
title('Stress vs Time: Max Bending')
grid on;
