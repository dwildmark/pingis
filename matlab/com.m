function [ a ] = com( port, P, I, D, b, r )
%COM Summary of this function goes here
% port: the COM-port that arduino is connected to.
% P: Proportionality constant for regulation.
% I: Integration constant for regulation.
% D: Derivative constant for regulation.
% b: set value for regulation
% r: rate of execution for regulation task.
%   Detailed explanation goes here
valuearr = importdata('reg4.txt');
a = serial(port,'BaudRate',115200);
set(a, 'Terminator', 10);
fopen(a);
pause(4);
flushinput(a);
flushoutput(a);

fprintf(a, num2str(P * 1000) );

fprintf(a, num2str(I * 1000));

fprintf(a, num2str(D * 1000));

fprintf(a, num2str(b * 1000));

fprintf(a, num2str(r * 1000));

for k = 1:100
    fprintf(a, valuearr(k));
end

%TEST, ta bort när färdig
fgetl(a)
fgetl(a)
fgetl(a)
fgetl(a)
fgetl(a)
%End of test

while(1)
    fgetl(a);
end

end

