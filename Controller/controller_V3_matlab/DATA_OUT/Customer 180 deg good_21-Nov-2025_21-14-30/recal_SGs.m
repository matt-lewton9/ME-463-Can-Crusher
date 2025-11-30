function SGs = recal_SGs(SGs)

C_old = [.809 .802 .795];
C_new = [.820 .813 .802];


SGs(1,:) = SGs(1,:) .* C_new(1) ./ C_old(1);
SGs(2,:) = SGs(2,:) .* C_new(2) ./ C_old(2);
SGs(3,:) = SGs(3,:) .* C_new(3) ./ C_old(3);

end