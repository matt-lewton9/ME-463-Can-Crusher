% writes outputs from fsm_main to .csv files
%% get current time for labels
time = datetime("now");
time.Format = "dd-MMM-yyyy_HH-mm-ss";

%% create new folder
mkdir(".\DATA_OUT\" + time)

%% PT readings
PTs = [0 1 2 3 4; 0 2 4 6 8; 0 3 9 12 15];
PTs_table = array2table(PTs');
PTs_table.Properties.VariableNames = {"PT1 [Psi]", "PT2 [Psi]", "PT3 [Psi]"};
writetable(PTs_table, "./Data_OutPT_dat")