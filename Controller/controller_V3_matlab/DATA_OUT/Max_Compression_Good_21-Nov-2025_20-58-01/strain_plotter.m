clc;
clear;
close all;

%% Data
load variables.mat
test_name = "Max Compression";
ERROR_PCT = 0.1;

SGs = recal_SGs(SGs);


[e1 e2 e3] = strain_predict(PTs(1,:)'.*CYLINDER_AREA, PTs(2,:)'.*CYLINDER_AREA, PTs(3,:)'.*CYLINDER_AREA);

e1 = e1 .* (10^6);
e2 = e2 .* (10^6);
e3 = e3 .* (10^6);

figure(randi(1000))

plot(times,SGs(1,:));
hold on
plot(times,SGs(2,:));
hold on
plot(times,SGs(3,:));
hold on
% plot(times, e1.*(1+ERROR_PCT), '--')
% hold on
% plot(times, e1.*(1-ERROR_PCT), '--')
plot(times, e1, '--')
hold on
plot(times, e2, '--')
hold on
plot(times, e3, '--')
legend("Strain Guage 1","Strain Guage 2","Strain Guage 3", 'Location', 'southeast')
title(sprintf("%s Strains", test_name));
xlabel("Time [s]")
ylabel("Strain [\muin / in] ")




figure(randi(1000))


plot(times,PTs(1,:).*CYLINDER_AREA);
hold on
plot(times,PTs(2,:).*CYLINDER_AREA);
hold on
plot(times,PTs(3,:).*CYLINDER_AREA);
legend("Actuator 1","Actuator 2","Actuator 3", 'Location', 'southeast')
title(sprintf("%s Forces", test_name));
xlabel("Time [s]")
ylabel("Force [lbf] ")

