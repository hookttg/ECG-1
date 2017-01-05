function [klasyfikacja]=lda_classify(training1, training2, test)

c1_number=length(training1);
c2_number=length(training2);

N=c1_number+c2_number; %wszystkie probki

pic1=c1_number/N; %prawdopodobienstwo wyst?pienia anej klasy - w prezentacji to jest pi
pic2=c2_number/N;

%%

% tutaj licz? mu oraz sigm? wg wzorow z prezi
uk1=mean(training1);
uk2=mean(training2);

p=size(training1);
feature_number=p(2); %liczba cech 

E=zeros(feature_number,feature_number);
sigma=zeros(feature_number,feature_number);

for k=1:2
    if k==1
        training=training1;
        l=c1_number;
        u=uk1;
    end
    if k==2
        training=training2;
        l=c2_number;
        u=uk2;
    end
    
    for i=1:l
        t=((training(i,:)-u)'*(training(i,:)-u))/(N-2);
        E=E+t;
    end
    sigma=sigma+E;
end
%% tutaj jest wyliczenie tego prawdopodobienstwa
% co ciekawe, z niego sie w ogole nie tworzy tej funkcji klasyfikujacej
%wiec fajnie ze to jest ale i tak tego nie wykorzystujemy
% 
% x=training2; %x=y to zbior uczacy, znowu bezmyslnie zmieniam nazwe :D
% 
% % w poni?szych forach szukam dla jakiego x warto?? P jest maksymalna
% % tutaj szczerze nie wiem, co by nam to dawalo i jest to liczone wszystkie
% % klasyfikatory na raz. to s? te wzory z prezentacji z delt? i
% % przyrownywaniem
% 
% max=0;
% for i=1:kN
%     Pn(i)=(x(i,:))*(sigma^(-1))*uk2' - uk2*(sigma^(-1))*uk2'/2+log(pic2);
%     if Pn(i)>max
%         max=Pn(i);
%         GN=i;
%     end
% end
% 
% y=training1;
% max2=0;
% for i=1:kVE
%     Pv(i)=(y(i,:))*(sigma^(-1))*uk1' - uk1*(sigma^(-1))*uk1'/2+log(pic1);
%     if Pv(i)>max2
%         max2=Pv(i);
%         GVE=i;
%     end
% end

%% obliczanie wspolczynnikow funkcji klasyfikujacej
u=uk2-uk1;
a=(sigma^(-1))*u'; %tu sa kolejne wspolczynniki - tyle ile cech
a0=log(pic2/pic1)-(uk2+uk1)*(sigma^(-1))*(uk2-uk1)'/2;

%% klasyfikacja stricte

klasyfikacja=zeros(length(test),1);


for i=1:length(test)
    
    for j=1:feature_number
        if j==1
            f=a0;
        end
        f=f+test(i,j)*a(j);
    end
    
    
    if f<=0
       klasyfikacja(i)=1; %N - ta klasa ktora wchodzi jako training1
    else
        klasyfikacja(i)=2; %VE         
    end
    
end

end

