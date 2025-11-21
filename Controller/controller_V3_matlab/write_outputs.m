% writes outputs from fsm_main to .csv files
%% input name for test
test_name = input("Name for test: ", "s");


%% get current time for labels
time = datetime("now");
time.Format = "dd-MMM-yyyy_HH-mm-ss";
time_str=string(time);

%% create new folder
mkdir("DATA_OUT", test_name + "_" + time_str)
dir_str = "DATA_OUT/" + test_name + "_" + time_str;

%% PT readings
%PTs = [0 1 2 3 4; 0 2 4 6 8; 0 3 9 12 15];
PTs_table = array2table(PTs');
PTs_table.Properties.VariableNames = {'PT1 [Psi]', 'PT2 [Psi]', 'PT3 [Psi]'};
writetable(PTs_table, dir_str + "/PT_readings.csv")

%% SG readings
%SGs = [0 1 2 3 4; 0 2 4 6 8; 0 3 9 12 15];
SGs_table = array2table(SGs');
SGs_table.Properties.VariableNames = {'SG1 [strain]', 'SG2 [strain]', 'SG3 [strain]'};
writetable(SGs_table, dir_str + "/SG_readings.csv")

%% Commanded Force
%F_command_hist = [0 1 2 3 4; 0 2 4 6 8; 0 3 9 12 15];
F_command_hist_table = array2table(F_command_hist');
F_command_hist_table.Properties.VariableNames = {'F1 [lbf]', 'F2 [lbf]', 'F3 [lbf]'};
writetable(F_command_hist_table, dir_str + "/Force_commanded.csv")

%% Commanded Stepts
%step_command_hist = [0 1 2 3 4; 0 2 4 6 8; 0 3 9 12 15];
step_command_hist_table = array2table(step_command_hist');
step_command_hist_table.Properties.VariableNames = {'M1 steps [steps]', 'M2 steps [steps]', 'M3 steps [steps]'};
writetable(step_command_hist_table, dir_str + "/Steps_commanded.csv")

%% Straing Gauges
%step_command_hist = [0 1 2 3 4; 0 2 4 6 8; 0 3 9 12 15];
sg_hist_table = array2table(SGs');
sg_hist_table.Properties.VariableNames = {'SG1 [microstrain]', 'SG2 [microstrain]', 'SG3 [microstrain]'};
writetable(sg_hist_table, dir_str + "/Steps_commanded.csv")