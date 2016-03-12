function [ a ] = com( port, P, I, D, b, r )
%COM Summary of this function goes here
%   Detailed explanation goes here
a = serial(port,'BaudRate',115200);
set(a, 'Terminator', 10);
fopen(a);
pause(2);
flushinput(a);
flushoutput(a);

fprintf(a, num2str(P * 1000));

fprintf(a, num2str(I * 1000));

fprintf(a, num2str(D * 1000));

fprintf(a, num2str(b * 1000));

fprintf(a, num2str(r * 1000));

fgetl(a)
fgetl(a)
fgetl(a)
fgetl(a)
fgetl(a)

fprintf(a, 'hej');
fprintf(a, '\n');
fgetl(a)

end

