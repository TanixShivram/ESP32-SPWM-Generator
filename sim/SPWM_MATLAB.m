fs = 40000;              % sample rate
t = 0:1/fs:0.1;         % 0.1 seconds of samples
freqSine = 50;
freqSaw  = 2000;

% Generate waves normalized between 0 and 1
sineWave     = (sin(2*pi*freqSine*t) + 1) / 2;
sawtoothWave = (sawtooth(2*pi*freqSaw*t, 0) + 1) / 2; 

sinAmplitude = 1;
sineWave = sineWave * sinAmplitude;

% Generate SPWM logic
spwm = double(sineWave >= sawtoothWave);

% Plotting and saving the line handles
figure;
p1 = plot(t, spwm, 'LineWidth', 1.5); 
hold on;
p2 = plot(t, sineWave, 'r--', 'LineWidth', 1.5); 
p3 = plot(t, sawtoothWave, 'g:', 'LineWidth', 1); 

xlabel('Time (seconds)');
ylabel('Amplitude');
title('SPWM Generation (Click Legend to Toggle Lines)');
grid on;
xlim([0, 0.02]); 

% Create the legend
lgd = legend([p1, p2, p3], 'SPWM Output', 'Sine Reference', 'Sawtooth Carrier');

% Enable the interactive click-to-toggle feature
lgd.ItemHitFcn = @cbToggleVisible;

% This helper function runs every time you click an item in the legend
function cbToggleVisible(~, event)
    if strcmp(event.Peer.Visible, 'on')
        event.Peer.Visible = 'off';
    else
        event.Peer.Visible = 'on';
    end
end