function [ a, y ] = com( port, P, I, D, b, r )
%COM Summary of this function goes here
% port: the COM-port that arduino is connected to.
% P: Proportionality constant for regulation.
% I: Integration constant for regulation.
% D: Derivative constant for regulation.
% b: set value for regulation
% r: rate of execution for regulation task.
%   Detailed explanation goes here
valuearr = importdata('bana4.txt');
a = serial(port,'BaudRate',115200);
set(a, 'Terminator', 10);
fopen(a);
pause(4);
flushinput(a);
flushoutput(a);

fprintf(a, num2str(P * 1000) );

fprintf(a, num2str(I * 1000));

fprintf(a, num2str(D * 1000));

fprintf(a, num2str(b));

fprintf(a, num2str(r));

for k = 1:100
    fprintf(a, num2str(valuearr(k)));
end
tempval = zeros(r,3);
setpoint = b.*ones(r*60, 1);
plotval = zeros(r*60,4);
plotval(:,4) = setpoint;
%Confirmation of variables sent
disp(str2double(fgetl(a))/1000);
disp(str2double(fgetl(a))/1000);
disp(str2double(fgetl(a))/1000);
disp(str2double(fgetl(a))/1000);
disp(str2double(fgetl(a))/1000);
%End of test


plot1 = plot(1:r*60, plotval);

while ishandle(plot1)
    for i = 1 : r
        tempval = circshift(tempval, 1);
        tempval(1,1) = str2double(fgetl(a));
        tempval(1,2) = str2double(fgetl(a));
        tempval(1,3) = str2double(fgetl(a));
    end
    plotval = circshift(plotval, r);
    plotval(1:r,1:3) = tempval;
    plot1 = plot(1:r*60,plotval);
    legend('Felvärde', 'Utvärde', 'Avstånd', 'Börvärde')
    pause(0.5)
 
end
y = plotval;
plot(1:r*60,y);
end

