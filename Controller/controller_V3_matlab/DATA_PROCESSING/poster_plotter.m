function [] = poster_plotter(test_name_in, path_name)

%% Data

load(sprintf("%s/variables.mat", path_name));
ERROR_PCT = 0.1;

data_times = load(sprintf("%s/variables.mat", path_name), "times");
data_times = data_times.times;

SGs = recal_SGs(SGs);

outlier_idx = abs(SGs) > 600;   % outlier threshold
SGs(outlier_idx) = interp1(find(~outlier_idx), SGs(~outlier_idx), find(outlier_idx));

[e1, e2, e3] = strain_predict(PTs(1,:)'.*CYLINDER_AREA, ...
                              PTs(2,:)'.*CYLINDER_AREA, ...
                              PTs(3,:)'.*CYLINDER_AREA);

e1 = e1 .* 1e6;
e2 = e2 .* 1e6;
e3 = e3 .* 1e6;


%% ===== REMOVE FIRST 100 AND LAST 10 POINTS & RESET TIME =====

start_idx = 50;                        % remove first 100
end_idx   = length(data_times) - 10;    % remove last 10

% Trim data
data_times = data_times(start_idx:end_idx);
SGs        = SGs(:, start_idx:end_idx);
e1         = e1(start_idx:end_idx);
e2         = e2(start_idx:end_idx);
e3         = e3(start_idx:end_idx);

% Reset time to start at 0
data_times = data_times - data_times(1);


%% Plotting

figure(randi(1000))

plot(data_times, SGs(1,:), 'Color', "#33C5FF", "LineWidth", 2); 
hold on
% plot(data_times, SGs(2,:), 'Color', "#FFA333"); hold on
% plot(data_times, SGs(3,:), 'Color', "#C233FF"); hold on
plot(data_times, e1, '--', 'Color', "#55CC55", "LineWidth", 2); 
hold on
plot(data_times, e1.*(1+ERROR_PCT), ':', 'Color', "#1F8A3B", "LineWidth", 2); 
hold on
plot(data_times, e1.*(1-ERROR_PCT), ':', 'Color', "#1F8A3B", "LineWidth", 2); 
hold on


% plot(data_times, e2, '--', 'Color', "#FFA333"); hold on
% plot(data_times, e3, '--', 'Color', "#C233FF"); hold on

legend("Strain Gauge Reading", "Strain Gauge Prediction", "Strain Gauge ±10% Error", ...
       'Location', 'northwest')

title(sprintf("%s Strains", test_name_in));
xlabel("Time [s]")
ylabel("Strain [\muin / in] ")
xlim([0 215])
ylim([0 505])
set(gca, 'Position', [0.08 0.08 0.88 0.88]);
end
