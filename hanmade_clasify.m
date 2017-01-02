N_train = floor(0.7*size(Nclass,1));
VE_train = floor(0.7*size(VEclass,1));
SV_train = floor(0.7*size(SVclass,1));

Training_samples = cat(1, VEclass(1:VE_train,1:4), Nclass(1:N_train,1:4));
Test_samples = cat(1, VEclass(VE_train+1:end,1:4), Nclass(N_train+1:end,1:4));
group = cat(1, VEclass(1:VE_train,7), Nclass(1:N_train,7));

kVE=VE_train; %liczba probek VE
kN=N_train; %liczba probek N

N=kVE+kN; %wszystkie probki

pive=kVE/N; %prawdopodobienstwo wyst?pienia anej klasy - w prezentacji to jest pi
pin=kN/N;

%%
%tu sobie zmienilam po prostu nazwy zbiorow uczacych
VEtr=VEclass(1:VE_train,1:4);
Ntr=Nclass(1:N_train,1:4);


% tutaj licz? mu oraz sigm? wg wzorow z prezi
ukv=mean(VEtr);
ukn=mean(Ntr);

E=zeros(4,4);
sigma=zeros(4,4);

for k=1:2
    if k==1
        class=Ntr;
        l=kN;
        u=ukn;
    end
    if k==2
        class=VEtr;
        l=kVE;
        u=ukv;
    end
    
    for i=1:l
        t=((class(i,:)-u)'*(class(i,:)-u))/(N-2);
        E=E+t;
    end
    sigma=sigma+E;
end
%% tutaj jest wyliczenie tego prawdopodobienstwa
% co ciekawe, z niego sie w ogole nie tworzy tej funkcji klasyfikujacej

x=Ntr; %x=y to zbior uczacy, znowu bezmyslnie zmieniam nazwe :D

% w poni?szych forach szukam dla jakiego x warto?? P jest maksymalna
% tutaj szczerze nie wiem, co by nam to dawalo i jest to liczone wszystkie
% klasyfikatory na raz. to s? te wzory z prezentacji z delt? i
% przyrownywaniem

max=0;
for i=1:kN
    Pn(i)=(x(i,:))*(sigma^(-1))*ukn' - ukn*(sigma^(-1))*ukn'/2+log(pin);
    if Pn(i)>max
        max=Pn(i);
        GN=i;
    end
end

y=VEtr;
max2=0;
for i=1:kVE
    Pv(i)=(y(i,:))*(sigma^(-1))*ukv' - ukv*(sigma^(-1))*ukv'/2+log(pive);
    if Pv(i)>max2
        max2=Pv(i);
        GVE=i;
    end
end

%% obliczanie wspolczynnikow funkcji klasyfikujacej
u=ukn-ukv;
a=(sigma^(-1))*u';
a0=log(pin/pive)-(ukn+ukv)*(sigma^(-1))*(ukn-ukv)'/2;

%%
d=Test_samples;
klasyfikacja=zeros(length(d),1);
for i=1:length(d)
    if (a0+d(i,1)*a(1)+d(i,2)*a(2)+d(i,3)*a(3)+d(i,4)*a(4))>=0
        klasyfikacja(i)=1; %N
    else
        klasyfikacja(i)=2; %VE
    end
end
%%
p=0;
for i=1:length(d);
    if klasyfikacja(i)~=test(i)
        p=p+1;
    end
end
      