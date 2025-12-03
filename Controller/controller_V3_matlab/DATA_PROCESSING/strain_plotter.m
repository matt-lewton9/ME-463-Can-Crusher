function [] = strain_plotter(test_name_in, path_name, de)

%% Data

load(sprintf("%s/variables.mat", path_name));
ERROR_PCT = 0.1;

data_times = load(sprintf("%s/variables.mat", path_name), "times");
data_times = data_times.times;

% SGs = recal_SGs(SGs);
% 
% outlier_idx = abs(SGs) > 1000;   % outlier threshold
% SGs(outlier_idx) = interp1(find(~outlier_idx), SGs(~outlier_idx), find(outlier_idx));

SGs(1,:) = filloutliers(SGs(1,:), 'linear',"movmedian",10);
SGs(2,:) = filloutliers(SGs(2,:),'linear',"movmedian",10);
SGs(3,:) = filloutliers(SGs(3,:),'linear',"movmedian",10);


SGs(1,:) = SGs(1,:) + de(2) ;
SGs(2,:) = SGs(2,:) + de(1);
SGs(3,:) = SGs(3,:) + de(3);


[e1, e2, e3] = strain_predict(PTs(1,:)'.*CYLINDER_AREA, PTs(2,:)'.*CYLINDER_AREA, PTs(3,:)'.*CYLINDER_AREA);

e1 = e1 .* (10^6);
e2 = e2 .* (10^6);
e3 = e3 .* (10^6);

figure(randi(1000))

plot(data_times ,SGs(2,:), 'Color',"#33C5FF"); % SG 1 and 2 are crossed somewhere,check wiring
hold on
plot(data_times,SGs(1,:), 'Color',"#FFA333");
hold on
plot(data_times,SGs(3,:), 'Color',"#C233FF");
hold on

%error bars
% plot(data_times, e1.*1.1, '--', 'Color',"#33C5FF")
% % hold on
% plot(data_times, e1.*.9, '--', 'Color',"#33C5FF")
% hold on
% plot(data_times, e2.*1.1, '--', 'Color',"#FFA333")
% hold on
% plot(data_times, e2.*.9, '--', 'Color',"#FFA333")
% hold on
% plot(data_times, e3.*1.1, '--', 'Color',"#C233FF")
% hold on
% plot(data_times, e3.*.9, '--', 'Color',"#C233FF")

% tgt lines
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
% plot(data_times,PTs(1,:).*CYLINDER_AREA);
% hold on
% plot(data_times,PTs(2,:).*CYLINDER_AREA);
% hold on
% plot(data_times,PTs(3,:).*CYLINDER_AREA);
% legend("Actuator 1","Actuator 2","Actuator 3", 'Location', 'southeast')
% title(sprintf("%s Forces", test_name_in));
% xlabel("Time [s]")
% ylabel("Force [lbf] ")


figure(randi(1000))


plot(data_times ,(SGs(2,:)'-e1)./e1.*100, 'Color',"#33C5FF"); % SG 1 and 2 are crossed somewhere,check wiring
hold on
plot(data_times,(SGs(1,:)'-e2)./e2.*100, 'Color',"#FFA333");
hold on
plot(data_times,(SGs(3,:)'-e3)./e3.*100, 'Color',"#C233FF");
hold on
plot([0, max(data_times)], [10 10], 'r--')
hold on
plot([0, max(data_times)], [-10 -10], 'r--')
plot([0, max(data_times)], [0 0], 'g--')
legend("SG 1","SG 2","SG 3", 'Location', 'northwest')
title(sprintf("%s Percent Error", test_name_in));
xlabel("Time [s]")
ylabel("Percent Error [%] ")
ylim([-20 20])

clear;
end

