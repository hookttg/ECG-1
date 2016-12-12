function [Q,S]=findqrs(R,Fs)

%R - wektor probek ann dla ktorych wykryto R
%funkcja zwraca wektory z numeracja probek dla ktorych jest Q i S

qrtime=0.063;
rstime=0.094;

qr=round(Fs*qrtime);
rs=round(rstime*Fs);

Q=zeros(1,length(R));
S=Q;

for i=1:length(R)
    Q(i)=R(i)-qr;
    S(i)=R(i)+rs;
end

end