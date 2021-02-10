clear; close all; clc;
 
%a1 = -1; a2 = -1; a3 = -1; a4 = -1; w = 2;
%a1 = 1; a2 = 1; a3 = 1; a4 = 1; w = 2;
a1 = 2; a2 = 3; a3 = -9; a4 = 1; w = 2;
ex = 0.01; ey = 0.01; el = 0.01;
 
 
F = @(a, b) a1*a*a + a2*a + a3*b*b + a4*b;
 
grad_a = @(a, l) 2*a1*a + a2 - 2*l*a;
 
grad_b = @(b, l) 2*a3*b + a4 - 2*l*b;
 
grad_l = @(a, b) w*w - a*a - b*b;
 
%main()
    h = 0.01; a(1) = 10; b(1) = 7; l(1) = 10;
   
    i = 1;
    while abs(grad_l(a(i), b(i))) > el
        
        l(i+1) = max(0, l(i) - h*grad_l(a(i), b(i)));
 
        a(i+1) = max(0, a(i) + h*grad_a(a(i), l(i)));
        
        b(i+1) = max(0, b(i) + h*grad_b(b(i), l(i)));
 
        if(i > 1000)
            break;
        end
        
        i = i + 1;
    end
 
    i
    a(end)
    b(end)
    F(a(end), b(end))
 
x = 0 : .2 : 10;
[X, Y] = meshgrid(x);
Z = a1*X.^2 + a2*X + a3*Y.^2 + a4*Y;
 
figure();
hold on
grid on
title('max F');
C = contour(X, Y, Z);
clabel(C);
 
th = 0 : pi/50 : pi/2;
r = w;
x = r*cos(th);
y = r*sin(th);
plot(x, y, 'r');
 
plot(a(1), b(1), 'r*'); text(a(1), b(1), 'н.т.');
plot(a, b, '.');
plot(a(end), b(end), 'g*'); text(a(end), b(end), 'к.т.');
 
xlabel('alfa'); ylabel('beta');
