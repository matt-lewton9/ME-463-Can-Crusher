clc;
close all;
clear;

%% Load Customer Inputs
cust_inputs = readmatrix("customer_inputs.xlsx"); % import customer data
cust_inputs = cust_inputs(:,2:end); % trim 1st col

steps = cust_inputs(1,:);
compress_steps = cust_inputs(2,:);
bending_steps = cust_inputs(3,:);
bending_angle_steps = cust_inputs(4,:);
ramp_steps = cust_inputs(5,:);
hold_steps = cust_inputs(6,:);


%% CONTROLLER INPUTS
CONT_FREQ = rateControl(10); % hz, desired controller frequency
TGT_LIM = 0.05; % +/- 5% within target value "reached target"
TGT_STEP = 0.05; % pct to step up target load
ABT_LIM = 1.20; % 20% Deviation above commanded press to trigger abort
GAIN = 10; %Gain for porportional controller
MAX_STEPS = 10; %Max steps for controller to command
CYLIDNER_AREA = 3.776;
COM_PORT = "COM6";
BAUD_RATE = 115200;

%% Set Up State Machine
STATE_0 = 100; % START STATE
STATE_1 = 101; % MOVE TO TGT LOAD STATE
STATE_2 = 102; % COMMANDED HOLD STATE
STATE_3 = 103; % SAFETY STOP STATE

% Input Variables
TP = 0; % OUTSIDE TARGET PRESSURE?
SP = 0; % OUTSIDE SAFE PRESSURE?
AHD = 0; % AUTO HOLD COMMANDED?
MHD = 0; % MANUAL HOLD COMMANDED?
ST = 0; % START COMMAND

HD = max(AHD,MHD); % HOLD Var for holds in general

% Output Variables
MV = 0; % MOVE TO TARGET PRESSURE
CY = 0; % CYCLE TO NEXT STEP

state = STATE_0; % init to start state
step_ind = 1; % Step index variable
tgt_pct = 0; %running pct of commanded load

% Zero regulators
% stepper(1)
% stepper(2)
% stepper(3)
% pause(30)

load_ramp_timer = tic; % start timer for beginning of program
load_ramp_start = toc(load_ramp_timer);

%% Init arduino connection
s = serialport(COM_PORT, 115200);

%% Initiate plotting
plot_timer = tic;
times = [0];
PTs = [0;0;0];
SGs = [0;0;0];
AHD_timer = plot_timer;
AHD_start = 0;
F_command = [0 0 0];

fig = figure(1);

left = uipanel(fig, 'Position', [0 0 0.75 1]); % Left panel for plots
right = uipanel(fig, 'Position', [0.75 0 0.25 1]); % Right panel for buttons
sgtitle("Can Crusher Data Read Out")

num_subplots = 2;
% PT Traces
s1 = subplot(num_subplots,1,1, 'Parent', left);
    PT1_plot = plot(times, PTs(1,:), 'Color',"#33C5FF");
        hold on
    PT2_plot = plot(times, PTs(2,:), 'Color',"#FFA333");
        hold on
    PT3_plot = plot(times, PTs(3,:), 'Color',"#C233FF");
        hold on
    % PT1_tgt_plot = plot(times, F_command(1).*tgt_pct./CYLIDNER_AREA,'--', 'Color',"#33C5FF");
    %     hold on
    % PT2_tgt_plot = plot(times, F_command(2).*tgt_pct./CYLIDNER_AREA,'--', 'Color',"#FFA333");
    %     hold on
    % PT3_tgt_plot = plot(times, F_command(3).*tgt_pct./CYLIDNER_AREA,'--', 'Color',"#C233FF");
        hold on
    ylabel("Pressure [psi]")
        
    yyaxis right
    F1_plot = plot(times, max(PTs,[],1).*CYLIDNER_AREA,'LineStyle','none');
    xlabel("Time [s]")
    ylabel("Force [lbf]")
    legend("PT 1","PT 2","PT 3", 'Location','northwest')
    title(s1,"PT Data / Force Data")


% Strains
s2 =subplot(num_subplots,1,2, 'Parent', left);
        SG1_plot = plot(times, SGs(1,:), 'Color',"#33C5FF");
        hold on
        SG2_plot = plot(times, SGs(2,:), 'Color',"#FFA333");
        hold on
        SG3_plot = plot(times, SGs(3,:), 'Color',"#C233FF");
        xlabel("Time [s]")
        ylabel("Strain")
        legend("SG 1","SG 1","SG 1", 'Location','northwest')
        title(s2, "Strain Data")

%Buttons

g = uigridlayout(right, [4 1]);

ST_button = uibutton(g,"state", 'Text',"START", "BackgroundColor","#51ff5b");
HD_button = uibutton(g,"state", 'Text',"HOLD", "BackgroundColor","#f9ff51");
SP_button = uibutton(g,"state", 'Text',"STOP", "BackgroundColor","#ff5151");

ST_button.Layout.Row = 1;
HD_button.Layout.Row = 2;
SP_button.Layout.Row = 3;
gui_text = uilabel(g,"Text","");%,sprintf("Current Test Step: %d\nState: %d\nRamp Pct: %d %\n",steps(step_ind), state, tgt_pct.*100));
lbl1.Text = "Text";

%% LOOP
while(step_ind <= numel(steps))
    waitfor(CONT_FREQ); % set loop frequency

%% INPUTS
% Get inputs   

    [PT1 PT2 PT3] = sensors_read(s);
        
    % [SG1 SG2 SG3]
     SGs = [0 0 0];

    PT_Reading = [PT1; PT2; PT3] ./8./6894.7572932 ;% read from serial, PA to psi/8
    SG_Reading = SGs;%[SG1; SG2; SG3] ;% read from serial
    

    ST = ST_button.Value; %GET FROM GUI INPUT;
    MHD = HD_button.Value; % Manual Hold
    SP = SP_button.Value; % STOP

    F_command = act_loads(compress_steps(step_ind), bending_steps(step_ind), bending_angle_steps(step_ind));
    F_meas = PT_Reading .* CYLIDNER_AREA; %Force = press * bore area
    F_pct = F_meas./F_command; %pct of total press

% Set Input Variables    
    %if all at Target pressure
    if allbetween(F_pct, 1-TGT_LIM, 1+TGT_LIM) 
        TP = 0;
    else
        TP = 1;
    end
    
    %if any at abort pressure above limit, abort
    if any(F_pct>ABT_LIM) 
        SP = 1;
    end
    
if(AHD) %if auto hold on    
    if ((toc(AHD_timer)-AHD_start) >= hold_steps(step_ind)) % if auto hold over
        AHD = 0; % turn off hold
        tgt_pct = 0; %Reset target percent
        step_ind = step_ind+1; % step to next index

    end
end

HD = max(AHD,MHD); % HOLD Var for all holds


%% Case Switch
switch(state)
    
    case STATE_0 %START STATE
        % State conditionals    
        if(SP == 1) % if unsafe press
            state = STATE_3;
        elseif(ST == 0) % else if test is not started
            state = STATE_0; 
        elseif(TP == 1 && HD == 0) % If outside TP and no man hold
            state = STATE_1;
        else
            state = STATE_2;
        end
        % State outputs    
        MV = 0;
    
    case STATE_1 % MOVE STATE
        % State conditionals    
        if(SP == 1) % if unsafe press
            state = STATE_3;
        elseif(TP == 1 && HD == 0) % else if outside TP and NO Hold
            state = STATE_1;
        else
            if(MHD == 0) % if not a manual hold
                AHD = 1; % start auto hold
                AHD_timer = tic;
                AHD_start = toc(AHD_timer);
            end
            state = STATE_2; %else, go to hold
        end
        % State outputs    
        MV = 1;
       

    case STATE_2 % HOLD STATE
        % State conditionals    
        if(SP == 1) % if unsafe press
            state = STATE_3;
        elseif(HD == 0) % else if NO Hold, go back to Move state
            state = STATE_1;
        else
            state = STATE_2; %else, stay in hold
        end
        % State outputs    
        MV = 0;
     

    case STATE_3 % % STOP STATE
        % State conditionals    
        state = STATE_3; %STAY IN ABORT FOREVER

        % State outputs    
        MV = 0;
end

%% OUTPUTS

    if (MV == 1) %if MV, move steppers in desired direction
        % adjust the target load rate
        load_rate_target = ramp_steps(step_ind) * TGT_STEP; %  5% load / s
        if ((toc(load_ramp_timer)-load_ramp_start) >= load_rate_target)
            % if (tgt_pct < 1)
                tgt_pct = tgt_pct + TGT_STEP;
            % end
            load_ramp_timer = tic;
            load_ramp_start = toc(load_ramp_timer);
        end      
        
        steps_commanded = round(F_pct .* GAIN);
        idx = steps_commanded>MAX_STEPS; % cap max steps
        steps_commanded(idx) = MAX_STEPS;

        step_dir = sign((F_command.*F_pct) - F_meas);
    
       
    % stepper(1)
    % stepper(2)
    % stepper(3)


    end

    %Update plots
    times = [times toc(plot_timer)]; %Update time array
    PTs = [PTs PT_Reading]; % Update Press array
    SGs = [SGs SG_Reading]; % Update Strain array
    % force_targets = [force_targets (F_command.*F_pct)];
    
    PT1_plot.XData = times;
    PT1_plot.YData = PTs(1,:);
    PT2_plot.XData = times;
    PT2_plot.YData = PTs(2,:);
    PT3_plot.XData = times;
    PT3_plot.YData = PTs(3,:);
    
    % PT1_tgt_plot.XData = times;
    % PT1_tgt_plot.YData = F_command(1).*tgt_pct./CYLIDNER_AREA;
    % PT2_tgt_plot.XData = times;
    % PT2_tgt_plot.YData = F_command(2).*tgt_pct./CYLIDNER_AREA;
    % PT3_tgt_plot.XData = times;
    % PT3_tgt_plot.YData = F_command(3).*tgt_pct./CYLIDNER_AREA;

    F1_plot.XData = times;
    F1_plot.YData = max(PTs,[],1).*CYLIDNER_AREA;

    gui_text.Text = sprintf("Current Test Step: %d\nState: %d\nRamp Pct: %.0f\nAuto Hold Timer: %.1f\n\nForce Targets:\nF1: %.0f lbf\nF2: %.0f lbf\nF3: %.0f lbf",steps(step_ind), state, tgt_pct.*100, toc(AHD_timer)-AHD_start,F_command(1),F_command(2),F_command(3));

    drawnow; % push update to screen
    
    
end 