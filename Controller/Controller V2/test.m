function [a1, a2, a3] = test2(F, M, theta)
    r = 1;
    a1 = 1/3 * (F + 2*M*cos(theta)/r);
    a2 = 1/3 * (F + (sqrt(3)*M*sin(theta) - M*cos(theta))/r);
    a3 = 1/3 * (F + (-sqrt(3)*M*sin(theta) - M*cos(theta))/r);
end
theta = linspace(0,2*pi,100);
[a1,a2,a3] = test2(0,1,theta);
plot(theta*180/pi, a1); hold on; plot(theta*180/pi, a2); plot(theta*180/pi, a3); hold off; legend(["a1","a2","a3"]);