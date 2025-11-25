function [] = strain_plotter(test_name_in, path_name)

%% Data

load(sprintf("%s/variables.mat", path_name));
ERROR_PCT = 0.1;

data_times = load(sprintf("%s/variables.mat", path_name), "times");
data_times = data_times.times;

SGs = recal_SGs(SGs);

outlier_idx = abs(SGs) > 600;   % outlier threshold
SGs(outlier_idx) = interp1(find(~outlier_idx), SGs(~outlier_idx), find(outlier_idx));

[e1 e2 e3] = strain_predict(PTs(1,:)'.*CYLINDER_AREA, PTs(2,:)'.*CYLINDER_AREA, PTs(3,:)'.*CYLINDER_AREA);

e1 = e1 .* (10^6);
e2 = e2 .* (10^6);
e3 = e3 .* (10^6);

figure(randi(1000))

plot(data_times ,SGs(1,:), 'Color',"#33C5FF");
hold on
plot(data_times,SGs(2,:), 'Color',"#FFA333");
hold on
plot(data_times,SGs(3,:), 'Color',"#C233FF");
hold on
% plot(data_times, e1.*(1+ERROR_PCT), '--', 'Color',"#33C5FF")
hold on
% plot(data_times, e1.*(1-ERROR_PCT), '--', 'Color',"#33C5FF")
plot(data_times, e1, '--', 'Color',"#33C5FF")
hold on
plot(data_times, e2, '--', 'Color',"#FFA333")
hold on
plot(data_times, e3, '--', 'Color',"#C233FF")
legend("Strain Guage 1","Strain Guage 2","Strain Guage 3", "SG1 Prediction", "SG2 Prediction", "SG3 Prediction", 'Location', 'northwest')
title(sprintf("%s Strains", test_name_in));
xlabel("Time [s]")
ylabel("Strain [\muin / in] ")



% figure(randi(1000))
% 
% 
% plot(data_times,PTs(1,:).*CYLINDER_AREA);
% hold on
% plot(data_times,PTs(2,:).*CYLINDER_AREA);
% hold on
% plot(data_times,PTs(3,:).*CYLINDER_AREA);
% legend("Actuator 1","Actuator 2","Actuator 3", 'Location', 'southeast')
% title(sprintf("%s Forces", test_name));
% xlabel("Time [s]")
% ylabel("Force [lbf] ")

clear;
end

