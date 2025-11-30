clc;
clear;
close all;

%% Data
load variables.mat
test_name = "Max Bending 0 Deg";
ERROR_PCT = 0.1;

SGs = recal_SGs(SGs);

% SGs = filloutliers(SGs, 'linear', 'mean', 'ThresholdFactor', 2);

[e1 e2 e3] = strain_predict(PTs(1,:)'.*CYLINDER_AREA, PTs(2,:)'.*CYLINDER_AREA, PTs(3,:)'.*CYLINDER_AREA);

e1 = e1 .* (10^6);
e2 = e2 .* (10^6);
e3 = e3 .* (10^6);

figure(randi(1000))

plot(times,SGs(1,:), 'Color',"#33C5FF");
hold on
plot(times,SGs(2,:), 'Color',"#FFA333");
hold on
plot(times,SGs(3,:), 'Color',"#C233FF");
hold on
% plot(times, e1.*(1+ERROR_PCT), '--', 'Color',"#33C5FF")
hold on
% plot(times, e1.*(1-ERROR_PCT), '--', 'Color',"#33C5FF")
plot(times, e1, '--', 'Color',"#33C5FF")
hold on
plot(times, e2, '--', 'Color',"#FFA333")
hold on
plot(times, e3, '--', 'Color',"#C233FF")
legend("Strain Guage 1","Strain Guage 2","Strain Guage 3", "SG1 Prediction", "SG2 Prediction", "SG3 Prediction", 'Location', 'northwest')
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

